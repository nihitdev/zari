#pragma once
#include "zari/keymap.hpp"
#include "zari/preview.hpp"
#include "zari/tab.hpp"
#include "zari/task.hpp"
namespace zari {
class Manager {
 public:
  Manager(fs::path start, Config config);
  Tab& tab(); const Tab& tab() const; void refresh();
  bool new_tab(); bool close_tab(); void switch_tab(int delta); void direct_tab(std::size_t index);
  bool paste(std::string&); void set_clipboard(ClipMode); void clear_selection();
  std::vector<fs::path> targets() const;
  Config config; std::vector<Tab> tabs; std::size_t active=0; ClipMode clip_mode=ClipMode::none; std::vector<fs::path> clipboard; TaskQueue tasks;
};
}
