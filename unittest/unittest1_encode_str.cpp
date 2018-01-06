#include "stdafx.h"
#include "base64.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// all quotes belong to their respective authors

namespace Base64UnitTest
{		
	TEST_CLASS(UnitTest1_encode_str)
	{
	public:
		
		Base64 testb64;

		// test encode_str that generates zero padding char
		TEST_METHOD(test_encode_str_0pchar)
		{
			const std::string encodedstr = "RG8sIG9yIGRvIG5vdC4gVGhlcmUgaXMgbm8gJ3RyeScu";
			Assert::AreEqual(encodedstr, testb64.encode_str("Do, or do not. There is no 'try'."), L"0pchar", LINE_INFO());
		}

		// test encode_str that generates one padding char
		TEST_METHOD(test_encode_str_1pchar)
		{
			const std::string encodedstr = "SGlzIGlnbm9yYW5jZSBpcyBlbmN5Y2xvcGVkaWM=";
			Assert::AreEqual(encodedstr, testb64.encode_str("His ignorance is encyclopedic"), L"1pchar", LINE_INFO());
		}

		// test encode_str that generates two padding chars
		TEST_METHOD(test_encode_str_2pchar)
		{
			const std::string encodedstr = "U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg==";
			Assert::AreEqual(encodedstr, testb64.encode_str("Sanity is a madness put to good uses."), L"2pchar", LINE_INFO());
		}

		// test encode_str that should fails if two padding chars are needed by only one is present
		TEST_METHOD(test_encode_str_missing_pchar)
		{
			const std::string encodedstr = "U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg=";
			Assert::AreNotEqual(encodedstr, testb64.encode_str("The best way to predict the future is to invent it."), L"missing_pchar", LINE_INFO());
		}

		// test encode_str that should fails since encoded and original strings are totally different
		TEST_METHOD(test_encode_str_no_match)
		{
			const std::string encodedstr = "U2lsZW5jZSBpcyBhcmd1bWVudCBjYXJyaWVkIG91dCBieSBvdGhlciBtZWFucy4=";
			Assert::AreNotEqual(encodedstr, testb64.encode_str("The man who goes alone can start today; but he who travels with another must wait till that other is ready."), L"no_match", LINE_INFO());
		}

	}; // UnitTest1_encode_str
}
