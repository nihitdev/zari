#pragma once
#include "zari/filesystem.hpp"
#include <map>
#include <set>

namespace zari {
class Tab {
 public:
  explicit Tab(fs::path path);
  bool navigate(const fs::path& path, const ManagerConfig& config, std::string& error, bool history=true);
  bool back(const ManagerConfig&, std::string&); bool forward(const ManagerConfig&, std::string&);
  void refresh(const ManagerConfig& config);
  const FileEntry* current() const;
  void move(int delta); void top(); void bottom();
  fs::path directory; std::vector<FileEntry> entries; std::size_t cursor=0, scroll=0;
  std::set<fs::path> selected; std::string filter;
 private:
  struct Point { fs::path path; std::size_t cursor; };
  std::vector<Point> back_, forward_;
};
}
