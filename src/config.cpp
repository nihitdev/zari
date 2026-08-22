#include "zari/config.hpp"
#include <algorithm>
#include <cerrno>
#include <charconv>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <string_view>
#include <unistd.h>

namespace zari {
namespace {
std::string trim(std::string s) { auto good=[](unsigned char c){return !std::isspace(c);}; s.erase(s.begin(),std::find_if(s.begin(),s.end(),good)); s.erase(std::find_if(s.rbegin(),s.rend(),good).base(),s.end()); return s; }
std::string unquote(std::string s) { s=trim(s); if(s.size()>=2 && s.front()=='"' && s.back()=='"') return s.substr(1,s.size()-2); return s; }
std::optional<bool> boolean(std::string s) { s=trim(s); if(s=="true") return true; if(s=="false") return false; return {}; }
std::optional<long long> integer(std::string s) { long long v{}; s=trim(s); auto [p,e]=std::from_chars(s.data(),s.data()+s.size(),v); return e==std::errc{}&&p==s.data()+s.size()?std::optional<long long>(v):std::nullopt; }
void warn(std::vector<std::string>& w, int line, std::string m){w.push_back("line "+std::to_string(line)+": "+std::move(m));}
bool write_new_file(const fs::path& path,std::string_view contents,bool& existed,std::string& error){
 int fd=::open(path.c_str(),O_WRONLY|O_CREAT|O_EXCL,0600);
 if(fd<0){if(errno==EEXIST){existed=true;return true;}error="cannot create "+path.string()+": "+std::strerror(errno);return false;}
 std::size_t written=0;
 while(written<contents.size()){auto count=::write(fd,contents.data()+written,contents.size()-written);if(count<0&&errno==EINTR)continue;if(count<=0){error="cannot write "+path.string()+": "+std::strerror(errno);::close(fd);return false;}written+=static_cast<std::size_t>(count);}
 if(::close(fd)!=0){error="cannot close "+path.string()+": "+std::strerror(errno);return false;}return true;
}
}
fs::path home_directory(){ if(const char* p=std::getenv("HOME")) return p; return "."; }
fs::path config_directory(){ if(const char* p=std::getenv("ZARI_CONFIG_HOME")) return p; if(const char* p=std::getenv("XDG_CONFIG_HOME")) return fs::path(p)/"zari"; return home_directory()/".config/zari"; }
fs::path state_directory(){ if(const char* p=std::getenv("XDG_STATE_HOME")) return fs::path(p)/"zari"; return home_directory()/".local/state/zari"; }
InitResult initialize_config(const fs::path& directory){
 InitResult result;std::error_code ec;fs::create_directories(directory,ec);if(ec){result.error="cannot create "+directory.string()+": "+ec.message();return result;}
 const std::array<std::pair<const char*,std::string_view>,3> files{{
  {"zari.toml",R"([manager]
show_hidden = false
show_symlink_target = true
sort_by = "natural"
sort_reverse = false
directories_first = true
case_sensitive = false
layout = [1, 3, 2]

[preview]
enabled = true
max_file_size = 10485760
tab_size = 4
wrap = false
line_numbers = true

[ui]
show_status_bar = true
show_tabs = true
show_file_icons = true
nerd_fonts = false
show_permissions = false
show_size = true
show_modified = true

[confirm]
trash = false
delete = true
overwrite = true
quit_with_tasks = true

[theme]
name = "default"

[open]
default = "xdg-open"
)"},
  {"keymap.toml",R"(# Zari keeps all built-in keybindings active unless you override them here.
# Example bookmark:
# [[manager.bind]]
# keys = ["g", "d"]
# action = "cd"
# arg = "~/Downloads"
# description = "Go to Downloads"
)"},
  {"theme.toml",R"(# Override only the styles you want to change.
# [manager]
# directory = { fg = "#89b4fa", bold = true }
# selected = { fg = "#11111b", bg = "#cba6f7", bold = true }
)"}
 }};
 for(const auto& [name,contents]:files){auto path=directory/name;bool existed=false;if(!write_new_file(path,contents,existed,result.error))return result;(existed?result.existing:result.created).push_back(path);}
 return result;
}
std::optional<SortBy> parse_sort(std::string v){ if(v=="natural")return SortBy::natural;if(v=="alphabetical")return SortBy::alphabetical;if(v=="extension")return SortBy::extension;if(v=="size")return SortBy::size;if(v=="modified")return SortBy::modified;if(v=="created"||v=="birth")return SortBy::created;if(v=="random")return SortBy::random;if(v=="none")return SortBy::none;return{}; }
LoadResult load_config(const fs::path& path,const Config& defaults){ LoadResult out{defaults,{},true}; std::ifstream f(path); if(!f){ if(fs::exists(path)){out.warnings.push_back("cannot read "+path.string());out.valid=false;} return out; } std::string section,line; int no=0; OpenRule* rule=nullptr;
 while(std::getline(f,line)){++no; auto hash=line.find('#'); if(hash!=std::string::npos) line.resize(hash); line=trim(line); if(line.empty())continue; if(line.front()=='['){ if(line.size()<3||line.back()!=']'){warn(out.warnings,no,"malformed table");out.valid=false;continue;} bool array=line.size()>3&&line[1]=='['&&line[line.size()-2]==']'; section=line.substr(array?2:1,line.size()-(array?4:2)); rule=nullptr; if(array&&section=="open.rules"){out.value.open_rules.emplace_back();rule=&out.value.open_rules.back();} continue;} auto eq=line.find('=');if(eq==std::string::npos){warn(out.warnings,no,"expected key = value");out.valid=false;continue;} auto k=trim(line.substr(0,eq)),v=trim(line.substr(eq+1));
 auto setb=[&](bool& dst){auto x=boolean(v);if(x)dst=*x;else{warn(out.warnings,no,"expected boolean for "+k);out.valid=false;}};
 if(section=="manager"){if(k=="show_hidden")setb(out.value.manager.show_hidden);else if(k=="show_symlink_target")setb(out.value.manager.show_symlink_target);else if(k=="sort_reverse")setb(out.value.manager.sort_reverse);else if(k=="directories_first")setb(out.value.manager.directories_first);else if(k=="case_sensitive")setb(out.value.manager.case_sensitive);else if(k=="sort_by"){auto s=parse_sort(unquote(v));if(s)out.value.manager.sort_by=*s;else warn(out.warnings,no,"unknown sort mode");}else if(k=="layout"){if(v.size()<5||v.front()!='['||v.back()!=']'){warn(out.warnings,no,"layout must be an array");continue;}std::stringstream ss(v.substr(1,v.size()-2));std::string x;int i=0;while(std::getline(ss,x,',')&&i<3){auto n=integer(x);if(n&&*n>=0&&*n<=20)out.value.manager.layout[i++]=static_cast<int>(*n);}if(i!=3||out.value.manager.layout[0]+out.value.manager.layout[1]+out.value.manager.layout[2]==0){warn(out.warnings,no,"layout requires three non-negative ratios with a positive total");out.value.manager.layout=defaults.manager.layout;}}}
 else if(section=="preview"){if(k=="enabled")setb(out.value.preview.enabled);else if(k=="wrap")setb(out.value.preview.wrap);else if(k=="line_numbers")setb(out.value.preview.line_numbers);else if(k=="max_file_size"){auto n=integer(v);if(n&&*n>=0)out.value.preview.max_file_size=static_cast<std::uintmax_t>(*n);else warn(out.warnings,no,"invalid max_file_size");}else if(k=="tab_size"){auto n=integer(v);if(n&&*n>=1&&*n<=16)out.value.preview.tab_size=static_cast<int>(*n);else warn(out.warnings,no,"tab_size must be 1..16");}}
 else if(section=="ui"){if(k=="show_status_bar")setb(out.value.ui.show_status_bar);else if(k=="show_tabs")setb(out.value.ui.show_tabs);else if(k=="show_file_icons")setb(out.value.ui.show_file_icons);else if(k=="nerd_fonts")setb(out.value.ui.nerd_fonts);else if(k=="show_permissions")setb(out.value.ui.show_permissions);else if(k=="show_size")setb(out.value.ui.show_size);else if(k=="show_modified")setb(out.value.ui.show_modified);}
 else if(section=="confirm"){if(k=="trash")setb(out.value.confirm.trash);else if(k=="delete")setb(out.value.confirm.remove);else if(k=="overwrite")setb(out.value.confirm.overwrite);else if(k=="quit_with_tasks")setb(out.value.confirm.quit_with_tasks);}
 else if(section=="theme"&&k=="name")out.value.theme_name=unquote(v); else if(section=="open"&&k=="default")out.value.opener=unquote(v); else if(section=="open.rules"&&rule){if(k=="mime")rule->mime=unquote(v);else if(k=="extension")rule->extension=unquote(v);else if(k=="command")rule->command=unquote(v);}
 }
 return out; }
}
