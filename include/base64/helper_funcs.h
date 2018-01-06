#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

// this class's methods could be used independently of the base64 class
class HFuncs
{
public:

	HFuncs() noexcept(true) {}
	~HFuncs() {}

	std::string string_to_hex(const std::string & str, const std::string& delimiter = "") const noexcept(true);
	std::string hex_to_string(const std::string & str, const std::string& delimiter = "") const noexcept(false);
	std::string char_to_hex(uint8_t cchar) const noexcept(false);

	void remove_sstr(std::string& str, const std::string& str_to_rm) const noexcept(true);

	std::string open_file_binay(const std::string& filename) const noexcept(false);
	std::string open_file_text(const std::string& filename) const noexcept(false);

	bool save_file_binary(const std::string& filename, const std::string& data_out) const noexcept(false);
	bool save_file_text(const std::string& filename, const std::string& data_out) const noexcept(false);

	uint64_t get_file_size(const std::string& filename) const noexcept(false);
};
