#include "zari/preview.hpp"
#include "zari/external.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <optional>
#include <sstream>

namespace zari {
namespace {
std::string extension(const fs::path& path){auto value=path.extension().string();std::transform(value.begin(),value.end(),value.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});return value;}
bool one_of(const std::string& value,std::initializer_list<std::string_view> choices){return std::any_of(choices.begin(),choices.end(),[&](auto choice){return value==choice;});}
std::vector<std::string> visible_lines(std::string output,int width,int height){std::vector<std::string> lines;std::istringstream stream(std::move(output));std::string line;while(std::getline(stream,line)&&static_cast<int>(lines.size())<height){if(width>0&&static_cast<int>(line.size())>width)line.resize(static_cast<std::size_t>(width));lines.push_back(std::move(line));}return lines;}
std::optional<Preview> tool_preview(const FileEntry& entry,int width,int height){
 const auto ext=extension(entry.path);std::vector<std::string> command;std::string label;
 if(ext==".json"&&command_available("jq")){command={"jq",".","--",entry.path.string()};label="JSON · jq";}
 else if(ext==".pdf"&&command_available("pdftotext")){command={"pdftotext","-f","1","-l","3","-layout",entry.path.string(),"-"};label="PDF text · poppler";}
 else if(one_of(ext,{".7z",".zip",".rar",".tar",".gz",".bz2",".xz",".zst"})&&command_available("7z")){command={"7z","l","-ba","--",entry.path.string()};label="Archive · 7-Zip";}
 else if(one_of(ext,{".mp4",".mkv",".webm",".mov",".avi",".mp3",".flac",".ogg",".wav"})&&command_available("ffprobe")){command={"ffprobe","-v","error","-show_entries","format=format_name,duration,size,bit_rate:stream=codec_name,width,height","-of","default=noprint_wrappers=1",entry.path.string()};label="Media metadata · FFmpeg";}
 else if(one_of(ext,{".png",".jpg",".jpeg",".gif",".webp",".heic",".heif",".jxl",".svg",".ttf",".otf",".woff",".woff2"})&&command_available("magick")){command={"magick","identify",entry.path.string()};label="Image/font metadata · ImageMagick";}
 else return std::nullopt;
 auto result=run_command(command,262144);if(result.exit_code!=0)return std::nullopt;Preview preview;preview.title=entry.name+"  ["+label+"]";preview.lines=visible_lines(std::move(result.output),width,height);if(ext==".svg"&&command_available("resvg"))preview.lines.insert(preview.lines.begin(),"resvg available for SVG rendering");return preview;
}
}
Preview make_preview(const FileEntry&e,const PreviewConfig&c,int width,int height){
 Preview p;p.title=e.name;if(height<=0)return p;
 if(e.kind==FileKind::directory){ManagerConfig mc;mc.show_hidden=true;auto r=list_directory(e.path,mc);std::size_t dirs=0,files=0;std::uintmax_t size=0;for(const auto&x:r.entries){if(x.kind==FileKind::directory)++dirs;else{++files;size+=x.size;}}p.lines={std::to_string(dirs)+" directories, "+std::to_string(files)+" files", "Approximate visible size: "+human_size(size),""};for(const auto&x:r.entries){if(static_cast<int>(p.lines.size())>=height)break;p.lines.push_back((x.kind==FileKind::directory?"d ":"  ")+x.name);}return p;}
 if(e.kind!=FileKind::regular&&e.kind!=FileKind::executable){p.lines={"Type: special file","Path: "+e.path.string(),"Permissions: "+permission_string(e.permissions)};if(e.symlink_target)p.lines.push_back("Target: "+e.symlink_target->string());return p;}
 if(e.size>c.max_file_size){p.lines={"File is too large to preview",human_size(e.size)};return p;}
 if(auto external=tool_preview(e,width,height))return *external;
 std::ifstream f(e.path,std::ios::binary);if(!f){p.lines={"Cannot read file"};return p;}std::string sample(4096,'\0');f.read(sample.data(),sample.size());sample.resize(static_cast<std::size_t>(f.gcount()));if(sample.find('\0')!=std::string::npos){p.lines={"Binary file",human_size(e.size),"Path: "+e.path.string()};return p;}f.clear();f.seekg(0);std::string line;int n=1;while(std::getline(f,line)&&static_cast<int>(p.lines.size())<height){std::string expanded;for(char ch:line){if(ch=='\t')expanded+=std::string(c.tab_size-(expanded.size()%c.tab_size),' ');else expanded+=ch;}if(c.line_numbers)expanded=std::to_string(n)+"  "+expanded;if(width>0&&static_cast<int>(expanded.size())>width)expanded.resize(static_cast<std::size_t>(width));p.lines.push_back(std::move(expanded));++n;}return p;
}
}
