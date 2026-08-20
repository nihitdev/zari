#include "zari/search.hpp"
#include <algorithm>
#include <cctype>
namespace zari {
bool fuzzy_match(std::string_view t,std::string_view q,bool cs){std::size_t j=0;for(unsigned char c:t){if(j<q.size()&&(cs?c==static_cast<unsigned char>(q[j]):std::tolower(c)==std::tolower(static_cast<unsigned char>(q[j]))))++j;}return j==q.size();}
std::vector<fs::path> filename_search(const fs::path&root,std::string_view q,std::size_t limit,std::string&error){std::vector<fs::path> out;std::error_code ec;fs::recursive_directory_iterator it(root,fs::directory_options::skip_permission_denied,ec),end;if(ec){error=ec.message();return out;}for(;it!=end&&out.size()<limit;it.increment(ec)){if(ec){ec.clear();continue;}if(fuzzy_match(it->path().filename().string(),q))out.push_back(it->path());}return out;}
}
