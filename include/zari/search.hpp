#pragma once
#include "zari/types.hpp"
#include <string_view>
#include <vector>
namespace zari { bool fuzzy_match(std::string_view text, std::string_view query, bool case_sensitive=false); std::vector<fs::path> filename_search(const fs::path&, std::string_view, std::size_t limit, std::string& error); }
