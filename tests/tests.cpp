#include "zari/config.hpp"
#include "zari/external.hpp"
#include "zari/filesystem.hpp"
#include "zari/keymap.hpp"
#include "zari/preview.hpp"
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
 CHECK(zari::command_available("printf"));auto command=zari::run_command({"printf","%s","zari"});CHECK(command.exit_code==0);CHECK(command.output=="zari");auto filtered=zari::run_filter({"cat"},"zari\n");CHECK(filtered.exit_code==0);CHECK(filtered.output=="zari\n");std::string large_input(200000,'x');auto capped=zari::run_filter({"cat"},large_input,16);CHECK(capped.exit_code==0);CHECK(capped.output.size()==16);auto closed=zari::run_filter({"true"},large_input);CHECK(closed.exit_code==0);
 CHECK(zari::natural_key("file2")<zari::natural_key("file10"));CHECK(zari::fuzzy_match("README.md","rdm"));CHECK(!zari::fuzzy_match("abc","acb"));CHECK(zari::human_size(1024)=="1.0K");CHECK(zari::permission_string(fs::perms::owner_read).substr(0,3)=="r--");
 auto root=fs::temp_directory_path()/("zari-tests-"+std::to_string(::getpid()));fs::create_directories(root/"dir");std::ofstream(root/"file 1.txt")<<"hello";std::ofstream(root/"file10.txt")<<"x";std::ofstream(root/".hidden")<<"x";std::ofstream(root/"-data.json")<<"{\"zari\":true}";
 zari::ManagerConfig mc;auto listing=zari::list_directory(root,mc);CHECK(listing.error.empty());CHECK(listing.entries.size()==4);mc.show_hidden=true;CHECK(zari::list_directory(root,mc).entries.size()==5);
 std::string search_error;auto names=zari::filename_search(root,"file",20,search_error);CHECK(search_error.empty());CHECK(names.size()>=2);if(zari::command_available("rg")){auto contents=zari::content_search(root,"hello",20,search_error);CHECK(search_error.empty());CHECK(!contents.empty());}if(zari::command_available("jq")){zari::FileEntry json;json.path=root/"-data.json";json.name="-data.json";json.kind=zari::FileKind::regular;json.size=13;auto preview=zari::make_preview(json,zari::PreviewConfig{},80,20);CHECK(preview.title.find("jq")!=std::string::npos);CHECK(!preview.lines.empty());}
 std::ofstream(root/"zari.toml")<<"[manager]\nshow_hidden = true\nlayout = [0, 3, 2]\nsort_by = \"size\"\n[preview]\ntab_size = 8\n";auto cfg=zari::load_config(root/"zari.toml");CHECK(cfg.value.manager.show_hidden);CHECK(cfg.value.manager.layout[0]==0);CHECK(cfg.value.preview.tab_size==8);CHECK(cfg.value.manager.sort_by==zari::SortBy::size);
 std::ofstream(root/"bad.toml")<<"[manager]\nshow_hidden = perhaps\nlayout = [0, 0, 0]\n";auto bad=zari::load_config(root/"bad.toml");CHECK(!bad.valid);CHECK(!bad.warnings.empty());CHECK(!bad.value.manager.show_hidden);CHECK(bad.value.manager.layout==zari::ManagerConfig{}.layout);
 auto initialized=zari::initialize_config(root/"config");CHECK(initialized.error.empty());CHECK(initialized.created.size()==3);CHECK(fs::exists(root/"config/zari.toml"));CHECK(zari::load_config(root/"config/zari.toml").valid);std::ofstream(root/"config/keymap.toml",std::ios::app)<<"# preserved\n";auto initialized_again=zari::initialize_config(root/"config");CHECK(initialized_again.error.empty());CHECK(initialized_again.created.empty());CHECK(initialized_again.existing.size()==3);std::ifstream preserved(root/"config/keymap.toml");CHECK(std::string((std::istreambuf_iterator<char>(preserved)),{}).find("# preserved")!=std::string::npos);
 std::ofstream(root/"keymap.toml")<<"[[manager.bind]]\nkeys = [\"g\", \"d\"]\naction = \"cd\"\narg = \"~/Downloads\"\n";auto km=zari::Keymap::defaults();CHECK(km.exact({"c","p"})->action=="copy_paths");CHECK(km.exact({"z"})->action=="subtree");std::vector<std::string>w;CHECK(km.overlay(root/"keymap.toml",w));CHECK(km.exact({"g","d"})->action=="cd");CHECK(km.is_prefix({"g"}));
 auto th=zari::builtin_theme("nord");std::ofstream(root/"theme.toml")<<"[manager]\ndirectory = { fg = \"#123456\", bold = true }\n";CHECK(zari::overlay_theme_file(th,root/"theme.toml",w));CHECK(th.get("directory").bold);CHECK(th.get("directory").fg->r==0x12);
 zari::Tab tab(root);std::string e;CHECK(tab.navigate(root,mc,e,false));auto old=tab.entries.size();tab.move(999);CHECK(tab.cursor==old-1);tab.top();CHECK(tab.cursor==0);
 std::string err;CHECK(zari::copy_path(root/"file 1.txt",root/"copy.txt",err));CHECK(fs::exists(root/"copy.txt"));CHECK(zari::move_path(root/"copy.txt",root/"moved.txt",err));CHECK(!fs::exists(root/"copy.txt")&&fs::exists(root/"moved.txt"));CHECK(zari::remove_path(root/"moved.txt",err));
 fs::remove_all(root);if(failures){std::cerr<<failures<<" test(s) failed\n";return 1;}std::cout<<"all tests passed\n";
}
