#pragma once
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace zari {
struct CommandResult { int exit_code=-1; std::string output; std::string error; bool launched=false; };
bool command_available(std::string_view command);
CommandResult run_command(const std::vector<std::string>& arguments, std::size_t max_output=1048576);
CommandResult run_filter(const std::vector<std::string>& arguments, std::string_view input, std::size_t max_output=65536);
bool copy_to_clipboard(std::string_view text, std::string& error);
}
