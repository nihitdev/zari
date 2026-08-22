#include "zari/external.hpp"
#include <algorithm>
#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

namespace zari {
bool command_available(std::string_view command){
 if(command.empty()||command.find('/')!=std::string_view::npos)return false;
 const char* raw=std::getenv("PATH");if(!raw)return false;std::string path(raw);std::size_t start=0;
 while(start<=path.size()){auto end=path.find(':',start);auto directory=path.substr(start,end==std::string::npos?std::string::npos:end-start);if(directory.empty())directory=".";auto candidate=std::filesystem::path(directory)/command;if(::access(candidate.c_str(),X_OK)==0)return true;if(end==std::string::npos)break;start=end+1;}
 return false;
}
CommandResult run_command(const std::vector<std::string>& arguments,std::size_t max_output){
 CommandResult result;if(arguments.empty()){result.error="empty command";return result;}int output_pipe[2];if(::pipe(output_pipe)!=0){result.error=std::strerror(errno);return result;}pid_t pid=::fork();if(pid<0){result.error=std::strerror(errno);::close(output_pipe[0]);::close(output_pipe[1]);return result;}
 if(pid==0){::close(output_pipe[0]);::dup2(output_pipe[1],STDOUT_FILENO);::close(output_pipe[1]);int null_fd=::open("/dev/null",O_WRONLY);if(null_fd>=0){::dup2(null_fd,STDERR_FILENO);::close(null_fd);}std::vector<char*> argv;argv.reserve(arguments.size()+1);for(const auto&argument:arguments)argv.push_back(const_cast<char*>(argument.c_str()));argv.push_back(nullptr);::execvp(argv[0],argv.data());::_exit(127);}
 result.launched=true;::close(output_pipe[1]);char buffer[8192];for(;;){auto count=::read(output_pipe[0],buffer,sizeof buffer);if(count<0&&errno==EINTR)continue;if(count<=0)break;if(result.output.size()<max_output){auto keep=std::min<std::size_t>(static_cast<std::size_t>(count),max_output-result.output.size());result.output.append(buffer,keep);}}
 ::close(output_pipe[0]);int status=0;while(::waitpid(pid,&status,0)<0){if(errno==EINTR)continue;result.error=std::strerror(errno);return result;}if(WIFEXITED(status))result.exit_code=WEXITSTATUS(status);else result.error="command terminated abnormally";return result;
}
CommandResult run_filter(const std::vector<std::string>& arguments,std::string_view input,std::size_t max_output){
 CommandResult result;if(arguments.empty()){result.error="empty command";return result;}int input_pipe[2],output_pipe[2];if(::pipe(input_pipe)!=0){result.error=std::strerror(errno);return result;}if(::pipe(output_pipe)!=0){result.error=std::strerror(errno);::close(input_pipe[0]);::close(input_pipe[1]);return result;}pid_t pid=::fork();if(pid<0){result.error=std::strerror(errno);::close(input_pipe[0]);::close(input_pipe[1]);::close(output_pipe[0]);::close(output_pipe[1]);return result;}
 if(pid==0){::close(input_pipe[1]);::close(output_pipe[0]);::dup2(input_pipe[0],STDIN_FILENO);::dup2(output_pipe[1],STDOUT_FILENO);::close(input_pipe[0]);::close(output_pipe[1]);std::vector<char*> argv;argv.reserve(arguments.size()+1);for(const auto&argument:arguments)argv.push_back(const_cast<char*>(argument.c_str()));argv.push_back(nullptr);::execvp(argv[0],argv.data());::_exit(127);}
 result.launched=true;::close(input_pipe[0]);::close(output_pipe[1]);std::thread writer([fd=input_pipe[1],input]{sigset_t blocked;::sigemptyset(&blocked);::sigaddset(&blocked,SIGPIPE);::pthread_sigmask(SIG_BLOCK,&blocked,nullptr);std::size_t sent=0;while(sent<input.size()){auto count=::write(fd,input.data()+sent,input.size()-sent);if(count<0&&errno==EINTR)continue;if(count<=0)break;sent+=static_cast<std::size_t>(count);}::close(fd);});char buffer[4096];for(;;){auto count=::read(output_pipe[0],buffer,sizeof buffer);if(count<0&&errno==EINTR)continue;if(count<=0)break;if(result.output.size()<max_output){auto keep=std::min<std::size_t>(static_cast<std::size_t>(count),max_output-result.output.size());result.output.append(buffer,keep);}}::close(output_pipe[0]);writer.join();int status=0;while(::waitpid(pid,&status,0)<0){if(errno==EINTR)continue;result.error=std::strerror(errno);return result;}if(WIFEXITED(status))result.exit_code=WEXITSTATUS(status);else result.error="command terminated abnormally";return result;
}
bool copy_to_clipboard(std::string_view text,std::string& error){
 std::vector<std::string> command;if(std::getenv("WAYLAND_DISPLAY")&&command_available("wl-copy"))command={"wl-copy"};else if(command_available("xclip"))command={"xclip","-selection","clipboard"};else if(command_available("xsel"))command={"xsel","--clipboard","--input"};else if(command_available("wl-copy"))command={"wl-copy"};else{error="clipboard support requires wl-clipboard, xclip, or xsel";return false;}auto result=run_filter(command,text,0);if(result.exit_code!=0){error="clipboard helper failed";return false;}return true;
}
}
