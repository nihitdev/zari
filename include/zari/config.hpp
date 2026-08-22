#pragma once
#include "zari/types.hpp"
#include <array>
#include <optional>
#include <string>
#include <vector>

namespace zari {
struct ManagerConfig { bool show_hidden=false, show_symlink_target=true, sort_reverse=false, directories_first=true, case_sensitive=false; SortBy sort_by=SortBy::natural; std::array<int,3> layout{1,3,2}; };
struct PreviewConfig { bool enabled=true; std::uintmax_t max_file_size=10485760; int tab_size=4; bool wrap=false; bool line_numbers=true; };
struct UiConfig { bool show_status_bar=true, show_tabs=true, show_file_icons=true, nerd_fonts=false, show_permissions=false, show_size=true, show_modified=true; };
struct ConfirmConfig { bool trash=false, remove=true, overwrite=true, quit_with_tasks=true; };
struct OpenRule { std::string mime, extension, command; };
struct Config {
  ManagerConfig manager; PreviewConfig preview; UiConfig ui; ConfirmConfig confirm;
  std::string theme_name="default", opener="xdg-open"; std::vector<OpenRule> open_rules;
};
struct LoadResult { Config value; std::vector<std::string> warnings; bool valid=true; };
struct InitResult { std::vector<fs::path> created; std::vector<fs::path> existing; std::string error; };
fs::path home_directory();
fs::path config_directory();
fs::path state_directory();
InitResult initialize_config(const fs::path& directory);
LoadResult load_config(const fs::path& path, const Config& defaults = {});
std::optional<SortBy> parse_sort(std::string value);
}
