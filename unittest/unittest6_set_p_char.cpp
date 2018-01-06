#include "stdafx.h"
#include "base64.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// all quotes belong to their respective authors

namespace Base64UnitTest
{
	TEST_CLASS(UnitTest6_set_p_char)
	{
	public:

		Base64 testb64;

		// test encode_str with different padding character
		TEST_METHOD(test_set_p_char_different_padding_char_encode_str)
		{
			testb64.set_p_char("*");

			const std::string encodedstr = "SSBzaGFsbCBub3Qgd2FzdGUgbXkgZGF5cyBpbiB0cnlpbmcgdG8gcHJvbG9uZyB0aGVtLg" + testb64.get_p_char() + testb64.get_p_char();
			Assert::AreEqual(encodedstr, testb64.encode_str("I shall not waste my days in trying to prolong them."), L"2pchar_s_padding_char", LINE_INFO());
		}

		// test decode_str with different padding character
		TEST_METHOD(test_set_p_char_different_padding_char_decode_str)
		{
			testb64.set_p_char("*");

			const std::string encodedstring = "I shall not waste my days in trying to prolong them.";
			Assert::AreEqual(encodedstring, testb64.decode_str("SSBzaGFsbCBub3Qgd2FzdGUgbXkgZGF5cyBpbiB0cnlpbmcgdG8gcHJvbG9uZyB0aGVtLg" + testb64.get_p_char() + testb64.get_p_char()), L"2pchar_s_padding_char", LINE_INFO());
		}

		// test set_p_char with more than one padding char (size>1)
		// such scenario should throw an exception type exception
		TEST_METHOD(test_set_p_char_invalid_exception_isthrown_when_length_isnot_correct)
		{
			auto set_p_char_throw_exception = [this]() -> void
			{
				testb64.set_p_char("==");
			};

			Assert::ExpectException<std::exception>(set_p_char_throw_exception);
		}

		// test set_p_char with no setting of a padding character
		// such scenario should throw an exception type exception
		TEST_METHOD(test_set_p_char_invalid_exception_isthrown_when_empty)
		{
			auto set_p_char_throw_exception = [this]() -> void
			{
				testb64.set_p_char("");
			};

			Assert::ExpectException<std::exception>(set_p_char_throw_exception);
		}
	}; // UnitTest5_set_s_table
}