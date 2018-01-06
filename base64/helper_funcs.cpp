#include "helper_funcs.h"

// helper function that converts a string to a hex string stream
// _in_ (str)       : string to be converted to hexadecimal
// _in_ (delimiter) : a string value for delimiting returned hexadecimal 
//                    stream of bytes (default is set to no delimiter) 
// _out_ : string as hexadecimal stream (not space separated)
std::string
HFuncs::string_to_hex(const std::string& str, const std::string& delimiter) const noexcept(true)
{
	std::string strtohex;

	for (size_t x = 0; str.length() > x; ++x)
	{
		strtohex += delimiter + char_to_hex(static_cast<uint8_t>(str.at(x)));
	}
	// erase first delimiter since it gets added to the beginning of the stream
	if (!delimiter.empty() && str.size() > 1)
	{
		return strtohex.erase(0, delimiter.size());
	}
	else
	{
		return strtohex;
	}
}

// helper function that converts a hex string stream to string/ascii
// _in_ (str)       : hexadecimal string stream
// _in_ (delimiter) : if the stream is delimited, delimiter arg has to be set
// _out_ : converted hexadecimal stream into ascii
std::string 
HFuncs::hex_to_string(const std::string& str, const std::string& delimiter) const noexcept(false)
{
	if (delimiter.empty() && str.size() % 2 != 0)
	{
		throw std::exception("Hexadecimal byte stream is not valid.");
	}
	else if (!delimiter.empty() && (((str.size() - 2) % (2 + delimiter.size())) != 0))
	{
		throw std::exception("Hexadecimal byte stream is not valid.");
	}
	else
	{
		std::string hextostr;

		for (size_t i = 0; i < str.size(); i += (2 + delimiter.size()))
		{
			hextostr.push_back(static_cast<uint8_t>(strtol(str.substr(i, 2).c_str(), nullptr, 16)));				
		}
		return hextostr;
	}
}

// helper function that writes to a file on disk (in binary mode)
// _in_ (filename)  : file name to open/(write to)
// _in_ (data_out)  : data
// _out_ : true if writing to (filename) was successful, otherwise, false
bool
HFuncs::save_file_binary(const std::string& filename, const std::string& data_out) const noexcept(false)
{
	std::ofstream file_out;	
	file_out.open(filename, std::ios::out | std::ios::binary);

	if (!file_out)
	{
		throw std::exception("file could not be opened");
	}
	else
	{
		for (size_t i = 0; i < data_out.size(); i+=2)
		{
			file_out << static_cast<uint8_t>(strtol(data_out.substr(i, 2).data(), nullptr, 16) & 0xff);
		}

		file_out.close();		
		return (!file_out);
	}
}

// helper function that writes to a file on disk (in text mode)
// _in_ (filename)  : file name to open/(write to)
// _in_ (data_out)  : data
// _out_ : true if writing to (filename) was successful, otherwise, false
bool
HFuncs::save_file_text(const std::string& filename, const std::string& data_out) const noexcept(false)
{
	std::ofstream file_out;
	file_out.open(filename, std::ios::out);

	if (!file_out)
	{
		throw std::exception("file could not be opened");
	}
	else
	{
		file_out.write(data_out.c_str(), data_out.size());
		file_out.close();

		return (!file_out);
	}
}

// helper function that opens a file on disk (in binary mode)
// _in_  : file name to open
// _out_ : a string object holding the content of the file
std::string
HFuncs::open_file_binay(const std::string& filename) const noexcept(false)
{
	std::ifstream file_in;

	file_in.open(filename, std::ios::in | std::ios::binary);

	if (!file_in.is_open())
	{
		throw std::exception("file could not be opened");
	}
	else
	{
		uint64_t fsize = get_file_size(filename);

		auto file_buff = std::make_unique<unsigned char[]>(fsize);

		file_in.seekg(0, std::ios::beg);
		file_in.read((char*)file_buff.get(), fsize);			
		file_in.close();

		std::string file_buff_hex_stream;
		file_buff_hex_stream.reserve(fsize);

		for (uint64_t i = 0; i < fsize; ++i)
		{
			file_buff_hex_stream += char_to_hex(static_cast<uint8_t>(file_buff[i]));
		}
		return file_buff_hex_stream;
	}
}

// helper function that opens a file on disk (in text mode)
// _in_  : file name to open
// _out_ : a string object holding the content of the file
std::string
HFuncs::open_file_text(const std::string& filename) const noexcept(false)
{
	std::ifstream file_in;
	std::stringstream file_in_strstream;

	file_in.open(filename, std::ios::in | std::ios::binary);

	if (!file_in.is_open())
	{
		throw std::exception("file could not be opened");
	}
	else
	{
		file_in_strstream << file_in.rdbuf();
		file_in.close();
	}
	return file_in_strstream.str();
}
	
// helper function that converts an unsigned char to hex
// this is faster than using the std::stringstream object
// _in_  : unsigned char character
// _out_ : hex value stored in a string object
inline std::string
HFuncs::char_to_hex(const uint8_t cchar) const noexcept(false)
{
	std::string hexchar;
	hexchar.reserve(2);
		
	uint8_t uchar = cchar >> 4;
	uint8_t lchar = cchar & 0b1111;

	hexchar += (uchar < 10) ? char('0' + uchar) : char('A' + uchar - 10);
	hexchar += (lchar & 0b1111) < 10 ? char('0' + lchar) : char('A' + lchar - 10);
		
	return hexchar;
}

// helper function that retrieves the file size
// _in_  : file name
// _out_ : size of file as uint64_t
uint64_t
HFuncs::get_file_size(const std::string & filename) const noexcept(false)
{
	std::ifstream file_bin;

	file_bin.open(filename, std::ios::in | std::ifstream::binary | std::ios::ate);

	if (!file_bin.is_open())
	{
		throw std::exception("file could not be opened");
	}
	else
	{
		uint64_t fsize = file_bin.tellg();
		file_bin.close();
		return fsize;
	}
}

// helper function that removes all occurrences of a substring in a string 
// _in_ (str)       : referenced string
// _in_ (str_to_rm) : a substring to remove from str
// _out_            : no return value. passed string is modified by reference
void
HFuncs::remove_sstr(std::string& str, const std::string& str_to_rm) const noexcept(true)
{
	for (auto i = str.find(str_to_rm); i != std::string::npos; i = str.find(str_to_rm))
	{
		str.erase(i, str_to_rm.size());
	}
}