#pragma once
#include "zari/config.hpp"
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace zari {
enum class FileKind { regular, directory, symlink, broken_symlink, executable, socket, fifo, block, character, other };
struct FileEntry { fs::path path; std::string name; FileKind kind=FileKind::other; std::uintmax_t size=0; fs::perms permissions=fs::perms::unknown; fs::file_time_type modified{}; bool hidden=false; std::optional<fs::path> symlink_target; };
struct DirectoryResult { std::vector<FileEntry> entries; std::string error; };
DirectoryResult list_directory(const fs::path& path, const ManagerConfig& config);
std::string natural_key(std::string_view text, bool case_sensitive=false);
std::string human_size(std::uintmax_t bytes);
std::string permission_string(fs::perms p);
bool copy_path(const fs::path& from, const fs::path& to, std::string& error);
bool move_path(const fs::path& from, const fs::path& to, std::string& error);
bool remove_path(const fs::path& path, std::string& error);
bool trash_path(const fs::path& path, std::string& error);
fs::path collision_free(const fs::path& desired);
}
