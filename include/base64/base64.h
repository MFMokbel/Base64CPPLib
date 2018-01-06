#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stdexcept>
#include "helper_funcs.h"

class Base64: public HFuncs
{
public:

	Base64() noexcept(true);
	Base64(const std::string &stable, const std::string &pchar) noexcept(false);

	~Base64() {};
	
	std::string encode_str(const std::string & str, const int32_t rounds = 1) const noexcept(true);	

	std::string encode_hex(const std::string & str, const int32_t rounds, const std::string& delimiter) const noexcept(false);
	std::string encode_hex(const std::string & str, const std::string& delimiter) const noexcept(false);
	std::string encode_hex(const std::string & str, const int32_t rounds) const noexcept(false);
	std::string encode_hex(const std::string & str) const noexcept(false);


	std::string decode_str(const std::string& str, const int32_t rounds = 1) const noexcept(false);

	std::string decode_hex(const std::string& str, const int32_t rounds, const std::string& delimiter) const noexcept(false);
	std::string decode_hex(const std::string& str, const std::string& delimiter) const noexcept(false);
	std::string decode_hex(const std::string& str, const int32_t rounds) const noexcept(false);
	std::string decode_hex(const std::string& str) const noexcept(false);

	std::string get_s_table() const noexcept(true);
	void set_s_table(const std::string & stable) noexcept(false);

	std::string get_p_char() const noexcept(true);
	void set_p_char(const std::string & pchar) noexcept(false);

private:

	std::string encode(const std::string & str) const noexcept(true);
	std::vector<std::bitset<8>> decode(const std::string & str) const noexcept(false);
	
	std::string m_s_table;
	std::string m_pchar;
};