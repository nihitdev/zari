#include "zari/search.hpp"
#include "zari/external.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
namespace zari {
bool fuzzy_match(std::string_view t,std::string_view q,bool cs){std::size_t j=0;for(unsigned char c:t){if(j<q.size()&&(cs?c==static_cast<unsigned char>(q[j]):std::tolower(c)==std::tolower(static_cast<unsigned char>(q[j]))))++j;}return j==q.size();}
std::vector<fs::path> filename_search(const fs::path&root,std::string_view q,std::size_t limit,std::string&error){std::vector<fs::path> out;if(command_available("fd")){auto result=run_command({"fd","--absolute-path","--color","never","--hidden","--fixed-strings","--max-results",std::to_string(limit),"--",std::string(q),root.string()});if(result.exit_code==0){std::istringstream lines(result.output);std::string line;while(std::getline(lines,line)&&out.size()<limit)if(!line.empty())out.emplace_back(line);return out;}}std::error_code ec;fs::recursive_directory_iterator it(root,fs::directory_options::skip_permission_denied,ec),end;if(ec){error=ec.message();return out;}for(;it!=end&&out.size()<limit;it.increment(ec)){if(ec){ec.clear();continue;}if(fuzzy_match(it->path().filename().string(),q))out.push_back(it->path());}return out;}
std::vector<std::string> content_search(const fs::path&root,std::string_view query,std::size_t limit,std::string&error){std::vector<std::string> matches;if(!command_available("rg")){error="content search requires rg (ripgrep)";return matches;}auto result=run_command({"rg","--color","never","--line-number","--column","--no-heading","--smart-case","--max-count",std::to_string(limit),"--",std::string(query),root.string()});if(result.exit_code!=0&&result.exit_code!=1){error="rg content search failed";return matches;}std::istringstream lines(result.output);std::string line;while(std::getline(lines,line)&&matches.size()<limit)if(!line.empty())matches.push_back(std::move(line));return matches;}
}
