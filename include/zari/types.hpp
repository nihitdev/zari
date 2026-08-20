#pragma once
#include <cstdint>
#include <filesystem>
#include <string>

namespace zari {
namespace fs = std::filesystem;
enum class Mode { normal, select, visual, search, input, help };
enum class SortBy { natural, alphabetical, extension, size, modified, created, random, none };
enum class ClipMode { none, copy, cut };
std::string mode_name(Mode mode);
}
