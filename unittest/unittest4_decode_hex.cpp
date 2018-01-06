#include "stdafx.h"
#include "base64.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// all quotes belong to their respective authors

namespace Base64UnitTest
{
	TEST_CLASS(UnitTest4_decode_hex)
	{
	public:

		Base64 testb64;

		// test encode_hex that generates zero padding char
		TEST_METHOD(test_decode_hex_0pchar)
		{
			const std::string encodedstr = "446F2C206F7220646F206E6F742E205468657265206973206E6F2027747279272E";
			Assert::AreEqual(encodedstr, testb64.decode_hex("RG8sIG9yIGRvIG5vdC4gVGhlcmUgaXMgbm8gJ3RyeScu",1,""), L"0pchar", LINE_INFO());
		}

		// test encode_hex that generates one padding char
		TEST_METHOD(test_decode_hex_1pchar)
		{
			const std::string encodedstr = "4869732069676E6F72616E636520697320656E6379636C6F7065646963";
			Assert::AreEqual(encodedstr, testb64.decode_hex("SGlzIGlnbm9yYW5jZSBpcyBlbmN5Y2xvcGVkaWM=",1,""), L"1pchar", LINE_INFO());
		}

		// test encode_hex that generates two padding chars
		TEST_METHOD(test_decode_hex_2pchar)
		{
			const std::string encodedstr = "53616E6974792069732061206D61646E6573732070757420746F20676F6F6420757365732E";
			Assert::AreEqual(encodedstr, testb64.decode_hex("U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg==",1,""), L"2pchar", LINE_INFO());
		}

		// test decode_hex that should fails if base64 encoded string length is not correct
		// such scenario should throw an std::exception type exception
		TEST_METHOD(test_decode_hex_invalid_exception_isthrown_when_length_isnot_correct)
		{
			// originalstr = "The best way to predict the future is to invent it.";

			auto decode_str_throw_exception = [this]() -> std::string
			{
				return (testb64.decode_hex("U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg",1,""));
			};

			Assert::ExpectException<std::exception>(decode_str_throw_exception);
		}

		// test encode_hex that should fails since encoded and original strings are totally different
		TEST_METHOD(test_decode_hex_no_match)
		{
			const std::string encodedstr = "546865206d616e2077686f20676f657320616c6f6e652063616e20737461727420746f6461793b206275742068652077686f2074726176656c73207769746820616e6f74686572206d75737420776169742074696c6c2074686174206f746865722069732072656164792e";
			Assert::AreNotEqual(encodedstr, testb64.decode_hex("U2lsZW5jZSBpcyBhcmd1bWVudCBjYXJyaWVkIG91dCBieSBvdGhlciBtZWFucy4=",1,""), L"no_match", LINE_INFO());
		}
	}; // UnitTest1_encode_hex
}