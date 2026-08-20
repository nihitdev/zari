#pragma once
#include "zari/filesystem.hpp"
#include <string>
#include <vector>
namespace zari { struct Preview { std::string title; std::vector<std::string> lines; }; Preview make_preview(const FileEntry&, const PreviewConfig&, int width, int height); }
