#include "zari/tab.hpp"
#include <algorithm>
namespace zari {
Tab::Tab(fs::path p):directory(std::move(p)){}
bool Tab::navigate(const fs::path&p,const ManagerConfig&c,std::string&e,bool hist){std::error_code ec;auto resolved=fs::weakly_canonical(p,ec);if(ec||!fs::is_directory(resolved,ec)){e=ec?ec.message():"not a directory";return false;}auto r=list_directory(resolved,c);if(!r.error.empty()){e=r.error;return false;}if(hist){back_.push_back({directory,cursor});forward_.clear();}directory=resolved;entries=std::move(r.entries);cursor=scroll=0;selected.clear();return true;}
bool Tab::back(const ManagerConfig&c,std::string&e){if(back_.empty()){e="no back history";return false;}auto p=back_.back();back_.pop_back();forward_.push_back({directory,cursor});if(!navigate(p.path,c,e,false))return false;cursor=std::min(p.cursor,entries.empty()?0UL:entries.size()-1);return true;}
bool Tab::forward(const ManagerConfig&c,std::string&e){if(forward_.empty()){e="no forward history";return false;}auto p=forward_.back();forward_.pop_back();back_.push_back({directory,cursor});if(!navigate(p.path,c,e,false))return false;cursor=std::min(p.cursor,entries.empty()?0UL:entries.size()-1);return true;}
void Tab::refresh(const ManagerConfig&c){auto old=current()?current()->path:fs::path{};auto r=list_directory(directory,c);if(!r.error.empty())return;entries=std::move(r.entries);auto it=std::find_if(entries.begin(),entries.end(),[&](const auto&e){return e.path==old;});cursor=it==entries.end()?std::min(cursor,entries.empty()?0UL:entries.size()-1):static_cast<std::size_t>(it-entries.begin());}
const FileEntry*Tab::current()const{return cursor<entries.size()?&entries[cursor]:nullptr;}void Tab::move(int d){if(entries.empty())return;auto n=static_cast<long long>(cursor)+d;cursor=static_cast<std::size_t>(std::clamp<long long>(n,0,entries.size()-1));}void Tab::top(){cursor=0;}void Tab::bottom(){if(!entries.empty())cursor=entries.size()-1;}
}
