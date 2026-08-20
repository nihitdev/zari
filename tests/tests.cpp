#include "zari/config.hpp"
#include "zari/filesystem.hpp"
#include "zari/keymap.hpp"
#include "zari/search.hpp"
#include "zari/tab.hpp"
#include "zari/theme.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>
namespace fs=std::filesystem;
int failures=0;
#define CHECK(x) do { if(!(x)){std::cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "#x"\n";++failures;} } while(false)
int main(){
 CHECK(zari::natural_key("file2")<zari::natural_key("file10"));CHECK(zari::fuzzy_match("README.md","rdm"));CHECK(!zari::fuzzy_match("abc","acb"));CHECK(zari::human_size(1024)=="1.0K");CHECK(zari::permission_string(fs::perms::owner_read).substr(0,3)=="r--");
 auto root=fs::temp_directory_path()/("zari-tests-"+std::to_string(::getpid()));fs::create_directories(root/"dir");std::ofstream(root/"file 1.txt")<<"hello";std::ofstream(root/"file10.txt")<<"x";std::ofstream(root/".hidden")<<"x";
 zari::ManagerConfig mc;auto listing=zari::list_directory(root,mc);CHECK(listing.error.empty());CHECK(listing.entries.size()==3);mc.show_hidden=true;CHECK(zari::list_directory(root,mc).entries.size()==4);
 std::ofstream(root/"zari.toml")<<"[manager]\nshow_hidden = true\nlayout = [0, 3, 2]\nsort_by = \"size\"\n[preview]\ntab_size = 8\n";auto cfg=zari::load_config(root/"zari.toml");CHECK(cfg.value.manager.show_hidden);CHECK(cfg.value.manager.layout[0]==0);CHECK(cfg.value.preview.tab_size==8);CHECK(cfg.value.manager.sort_by==zari::SortBy::size);
 std::ofstream(root/"bad.toml")<<"[manager]\nshow_hidden = perhaps\nlayout = [0, 0, 0]\n";auto bad=zari::load_config(root/"bad.toml");CHECK(!bad.valid);CHECK(!bad.warnings.empty());CHECK(!bad.value.manager.show_hidden);CHECK(bad.value.manager.layout==zari::ManagerConfig{}.layout);
 std::ofstream(root/"keymap.toml")<<"[[manager.bind]]\nkeys = [\"g\", \"d\"]\naction = \"cd\"\narg = \"~/Downloads\"\n";auto km=zari::Keymap::defaults();std::vector<std::string>w;CHECK(km.overlay(root/"keymap.toml",w));CHECK(km.exact({"g","d"})->action=="cd");CHECK(km.is_prefix({"g"}));
 auto th=zari::builtin_theme("nord");std::ofstream(root/"theme.toml")<<"[manager]\ndirectory = { fg = \"#123456\", bold = true }\n";CHECK(zari::overlay_theme_file(th,root/"theme.toml",w));CHECK(th.get("directory").bold);CHECK(th.get("directory").fg->r==0x12);
 zari::Tab tab(root);std::string e;CHECK(tab.navigate(root,mc,e,false));auto old=tab.entries.size();tab.move(999);CHECK(tab.cursor==old-1);tab.top();CHECK(tab.cursor==0);
 std::string err;CHECK(zari::copy_path(root/"file 1.txt",root/"copy.txt",err));CHECK(fs::exists(root/"copy.txt"));CHECK(zari::move_path(root/"copy.txt",root/"moved.txt",err));CHECK(!fs::exists(root/"copy.txt")&&fs::exists(root/"moved.txt"));CHECK(zari::remove_path(root/"moved.txt",err));
 fs::remove_all(root);if(failures){std::cerr<<failures<<" test(s) failed\n";return 1;}std::cout<<"all tests passed\n";
}
