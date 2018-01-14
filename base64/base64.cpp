#include "base64.h"
#include "helper_funcs.h"

// default constructor
Base64::Base64() noexcept(true)
{
	// base64 s-table
	m_s_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	// padding char
	m_pchar = "=";
}

// overloaded constructor
Base64::Base64(const std::string &stable, const std::string &pchar) noexcept(false)
{
	// they too throw tailored exceptions
	set_s_table(stable);
	set_p_char(pchar);
}

// changes default base64 padding character value
// _in_ : padding character as string type
void
Base64::set_p_char(const std::string& pchar) noexcept(false)
{
	if (pchar.size() > 1)
	{
		throw std::exception("padding character is more than one character");
	}
	else if (pchar.empty())
	{
		throw std::exception("padding character is not set");
	}
	else if (m_s_table.find(pchar) != std::string::npos)
	{
		throw std::exception("padding character is not unique. It should be different from any character in the substitution table");
	}
	else
	{
		m_pchar = pchar;
	}
}

// changes default base64 substitution table
// _in_ : substitution table as string type
void
Base64::set_s_table(const std::string& stable) noexcept(false)
{
	if (stable.size() != 64)
	{
		throw std::exception("base64 substitution table size has to be 64 characters");
	}
	else if (stable.empty())
	{
		throw std::exception("base64 substitution table cannot be empty");
	}
	else
	{
		// check if substitution table contains duplicate chars
		std::set<char> is_duplicate(stable.begin(), stable.end());
		
		if (is_duplicate.size() != stable.size())
		{
			throw std::exception("base64 substitution table contains duplicate characters");
		}
		else
		{
			m_s_table = stable;
		}		
	}
}

// _in_ (str)    :  string to be encoded
// _in_ (rounds) :  number of rounds (default = 1)
// _out_         :  base64 decoded string as string/ascii
std::string
Base64::encode_str(const std::string& str, const int32_t rounds) const noexcept(true)
{
	std::string encodedstr = str;

	for (int32_t i = 0; i < std::abs(rounds); ++i)
	{
		encodedstr = encode(string_to_hex(encodedstr));
	}
	return encodedstr;
}

// _in_ (str)    :  base64 encoded string as string
// _in_ (rounds) :  number of rounds (default = 1)
// _out_         :  base64 decoded string as ascii
std::string
Base64::decode_str(const std::string& str, const int32_t rounds) const noexcept(false)
{
	std::string base64decodedstr;
	// lambda function that returns base64 decoded str as ascii
	auto get_decoded_b64_str = [this,&base64decodedstr](decltype(str) str_in) -> void
	{
		const std::vector<std::bitset<8>> b64d_bits_str = decode(str_in);		
		
		base64decodedstr.clear();

		for (const auto &i : b64d_bits_str)
		{			
			base64decodedstr += static_cast<uint8_t>(i.to_ulong());
		}
	};

	get_decoded_b64_str(str);
	// if number of rounds > 1
	for (int32_t i = 0; i < std::abs(rounds-1); ++i)
	{
		get_decoded_b64_str(base64decodedstr);
	}
	return base64decodedstr;
}

// _in_ (str)       : hexadecimal string stream
// _in_ (rounds)    : number of rounds
// _in_ (delimiter) : if (str) stream is delimited, this argument has
//                    to be set accordingly
// _out_            : base64 encoded data as string
std::string
Base64::encode_hex(const std::string& str, const int32_t rounds, const std::string& delimiter) const noexcept(false)
{
	if (delimiter.empty() && str.size() % 2 != 0)
	{
		throw std::exception("Hexadecimal byte stream is not valid.");
	}
	else if (!delimiter.empty() && ((str.size() - 2) % (2 + delimiter.size()) != 0))
	{
		throw std::exception("Hexadecimal byte stream is not valid.");
	}
	else
	{
		std::string encodedstr;

		// skip/"erase" delimiter value from the str hex stream
		for (size_t i = 0; i < str.size(); i += (2 + delimiter.size()))
		{
			encodedstr += str.substr(i, 2);
		}
		encodedstr = encode(encodedstr);

		for (int32_t i = 0; i < std::abs(rounds-1); ++i)
		{

			encodedstr = encode(string_to_hex(encodedstr));
		}
		return encodedstr;
	}
}

// overloaded function
// _in_ (str)       : hexadecimal string stream
// _in_ (delimiter) : if (str) stream is delimited, this argument has
//                    to be set accordingly
// _out_            : base64 encoded data as string
std::string 
Base64::encode_hex(const std::string & str, const std::string & delimiter) const noexcept(false)
{
	return encode_hex(str, 1, delimiter);
}

// overloaded function
// _in_ (str)       : hexadecimal string stream
// _in_ (rounds)    : number of rounds
// _out_            : base64 encoded data as string
std::string 
Base64::encode_hex(const std::string & str, const int32_t rounds) const noexcept(false)
{
	return encode_hex(str, rounds, "");
}

// overloaded function
// _in_ (str)       : hexadecimal string stream
// _out_            : base64 encoded data as string
std::string 
Base64::encode_hex(const std::string & str) const noexcept(false)
{
	return encode_hex(str, 1, "");
}

// _in_ (str)       : base64 encoded string as string
// _in_ (rounds)    : number of rounds
// _in_ (delimiter) : a string value for delimiting returned hexadecimal 
//                    stream of bytes
// _out_            : base64 decoded string as hexadecimal stream (lowercase)
std::string
Base64::decode_hex(const std::string& str, const int32_t rounds, const std::string& delimiter) const noexcept(false)
{
	std::vector<std::bitset<8>> b64d_bits_str;

	if (rounds > 1)
	{
		b64d_bits_str = decode(decode_str(str, (std::abs(rounds) - 1)));
	}
	else
	{
		b64d_bits_str = decode(str);
	}
	std::string base64decodedstr;

	for (const auto &i : b64d_bits_str)
	{
		base64decodedstr += delimiter + char_to_hex(i.to_ulong());
	}

	if (!delimiter.empty() && str.size() > 1)
	{
		return base64decodedstr.erase(0, delimiter.size());
	}
	else
	{
		return base64decodedstr;
	}
	return base64decodedstr;
}

// overloaded function
// _in_ (str)       : base64 encoded string as string
// _in_ (delimiter) : a string value for delimiting returned hexadecimal 
//                    stream of bytes
// _out_            : base64 decoded string as hexadecimal stream (lowercase)
std::string 
Base64::decode_hex(const std::string & str, const std::string & delimiter) const noexcept(false)
{
	return decode_hex(str,1,delimiter);
}

// overloaded function
// _in_ (str)       : base64 encoded string as string
// _in_ (rounds)    : number of rounds
// _out_            : base64 decoded string as hexadecimal stream (lowercase)
std::string 
Base64::decode_hex(const std::string & str, const int32_t rounds) const noexcept(false)
{
	return decode_hex(str, rounds, "");
}

// overloaded function
// _in_ (str)       : base64 encoded string as string
// _out_            : base64 decoded string as hexadecimal stream (lowercase)
std::string 
Base64::decode_hex(const std::string & str) const noexcept(false)
{
	return decode_hex(str, 1, "");
}

// private method
// main encoding algorithm
// _in_  :  string to be encoded
// _out_ :  base64 encoded string as string
std::string
Base64::encode(const std::string& str) const noexcept(true)
{
	std::vector<std::bitset<8>> strbits;

	// convert each hex byte to bits and store it in a vector object
	for (size_t i = 0; i < str.size(); i += 2)
	{
		strbits.push_back(strtol(str.substr(i,2).c_str(),nullptr,16));
	}

	bool pchar_1 = false;
	bool pchar_2 = false;

	std::vector<std::bitset<6>> strbits6;

	for (size_t x = 0; x < strbits.size();)
	{
		// 2 chars case (2 padding chars are needed)
		if ((strbits.size() - x) == 1)
		{
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x).to_string().substr(0, 6)));
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x).to_string().substr(6, 2) + "0000"));
			pchar_2 = true;
			++x;
		}
		// 3 chars case (1 padding char is needed)
		else if ((strbits.size() - x) == 2)
		{
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x).to_string().substr(0, 6)));
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x).to_string().substr(6, 2) + strbits.at(x + 1).to_string().substr(0, 4)));
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x + 1).to_string().substr(4, 4) + "00"));
			pchar_1 = true;
			x += 2;
		}
		// 4 chars case (no padding char is needed)
		else
		{
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x).to_string().substr(0, 6)));
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x).to_string().substr(6, 2) + strbits.at(x + 1).to_string().substr(0, 4)));
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x + 1).to_string().substr(4, 4) + strbits.at(x + 2).to_string().substr(0, 2)));
			strbits6.push_back(static_cast<std::bitset<6>>(strbits.at(x + 2).to_string().substr(2, 6)));
			x += 3;
		}
	}
	std::string base64encodedstr;

	for (size_t j = 0; j < strbits6.size(); ++j)
	{
		base64encodedstr += m_s_table.at(strbits6.at(j).to_ulong());
	}

	// accounts for padding char
	if (pchar_2) // (strbits.size() % 3) == 1
	{
		base64encodedstr += m_pchar;
		base64encodedstr += m_pchar;
		return base64encodedstr;
	}
	else if (pchar_1) // (strbits.size() % 3) == 2
	{
		base64encodedstr += m_pchar;
		return base64encodedstr;
	}
	else
	{
		return base64encodedstr;
	}
}

// private method
// main decoding algorithm
// _in_  :  string to be encoded
// _out_ :  base64 decoded string in bits (bitset<8>) stored in a vector object
std::vector<std::bitset<8>>
Base64::decode(const std::string & str) const noexcept(false)
{
	if (((str.size() % 4) != 0) || str.empty())
	{
		throw std::exception("base64 encoded data length is not correct");
	}

	std::vector<std::bitset<6>> istrbit6;
	size_t i_s_found = 0;
	// gets a char's respective index value in the substitution table (m_s_table)
	for (const auto &i: str)
	{
		i_s_found = m_s_table.find(i);

		if ((i_s_found != std::string::npos) || (i == m_pchar.at(0)))
		{
			istrbit6.push_back(i_s_found);
		}
		else
		{
			throw std::exception("a base64 encoded character does not exist in the substitution table");
		}
	}
	std::vector<std::bitset<8>> strbit8;

	size_t p_istrbit6_size = istrbit6.size();

	bool pchar_1 = false;
	bool pchar_2 = false;

	// check if last two chars are padding chars
	if ((str.back() == m_pchar.at(0)) && str.end()[-2] == m_pchar.at(0))
	{
		p_istrbit6_size -= 2;
		pchar_2 = true;
	}
	// check if last char is a padding char
	if ((str.back() == m_pchar.at(0)) && str.end()[-2] != m_pchar.at(0))
	{
		p_istrbit6_size -= 1;
		pchar_1 = true;
	}

	for (size_t x = 0; x < p_istrbit6_size;)
	{
		if (pchar_2 && ((p_istrbit6_size - x) == 2))
		{
			strbit8.push_back(static_cast<std::bitset<8>>(istrbit6.at(x).to_string() + istrbit6.at(x + 1).to_string().substr(0, 2)));
			x += 2;
		}
		else if (pchar_1 && ((p_istrbit6_size - x) == 3))
		{
			strbit8.push_back(static_cast<std::bitset<8>>(istrbit6.at(x).to_string() + istrbit6.at(x + 1).to_string().substr(0, 2)));
			strbit8.push_back(static_cast<std::bitset<8>>(istrbit6.at(x + 1).to_string().substr(2, 4) + istrbit6.at(x + 2).to_string().substr(0, 4)));
			x += 3;
		}
		else
		{
			strbit8.push_back(static_cast<std::bitset<8>>(istrbit6.at(x).to_string() + istrbit6.at(x + 1).to_string().substr(0, 2)));
			strbit8.push_back(static_cast<std::bitset<8>>(istrbit6.at(x + 1).to_string().substr(2, 4) + istrbit6.at(x + 2).to_string().substr(0, 4)));
			strbit8.push_back(static_cast<std::bitset<8>>(istrbit6.at(x + 2).to_string().substr(4, 2) + istrbit6.at(x + 3).to_string()));
			x += 4;
		}
	}
	return strbit8;
}

// access method
// returns currently set padding character value
// _out_: string
std::string
Base64::get_p_char() const noexcept(true)
{
	return m_pchar;
}

// access method
// returns currently set substitution table value
// _out_: string
std::string
Base64::get_s_table() const noexcept(true)
{
	return m_s_table;
}
