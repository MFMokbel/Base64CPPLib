#include "stdafx.h"
#include "base64.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// all quotes belong to their respective authors

namespace Base64UnitTest
{
	TEST_CLASS(UnitTest2_encode_hex)
	{
	public:
		
		Base64 testb64;

		// test encode_hex that generates zero padding char
		TEST_METHOD(test_encode_hex_0pchar)
		{
			const std::string encodedstr = "RG8sIG9yIGRvIG5vdC4gVGhlcmUgaXMgbm8gJ3RyeScu";
			Assert::AreEqual(encodedstr, testb64.encode_hex("446F2C206F7220646F206E6F742E205468657265206973206E6F2027747279272E",""), L"0pchar", LINE_INFO());
		}

		// test encode_hex that generates one padding char
		TEST_METHOD(test_encode_hex_1pchar)
		{
			const std::string encodedstr = "SGlzIGlnbm9yYW5jZSBpcyBlbmN5Y2xvcGVkaWM=";
			Assert::AreEqual(encodedstr, testb64.encode_hex("4869732069676E6F72616E636520697320656E6379636C6F7065646963",""), L"1pchar", LINE_INFO());
		}

		// test encode_hex that generates two padding chars
		TEST_METHOD(test_encode_hex_2pchar)
		{
			const std::string encodedstr = "U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg==";
			Assert::AreEqual(encodedstr, testb64.encode_hex("53616E6974792069732061206D61646E6573732070757420746F20676F6F6420757365732E",""), L"2pchar", LINE_INFO());
		}

		// test encode_hex that should fails if two padding chars are needed by only one is present
		TEST_METHOD(test_encode_hex_missing_pchar)
		{
			const std::string encodedstr = "U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg=";
			Assert::AreNotEqual(encodedstr, testb64.encode_hex("54686520626573742077617920746F2070726564696374207468652066757475726520697320746F20696E76656E742069742E",""), L"missing_pchar", LINE_INFO());
		}

		// test encode_hex that should fails since encoded and original strings are totally different
		TEST_METHOD(test_encode_hex_no_match)
		{
			const std::string encodedstr = "U2lsZW5jZSBpcyBhcmd1bWVudCBjYXJyaWVkIG91dCBieSBvdGhlciBtZWFucy4=";
			Assert::AreNotEqual(encodedstr, testb64.encode_hex("546865206D616E2077686F20676F657320616C6F6E652063616E20737461727420746F6461793B206275742068652077686F2074726176656C73207769746820616E6F74686572206D75737420776169742074696C6C2074686174206F746865722069732072656164792E",""), L"no_match", LINE_INFO());
		}
	}; // UnitTest2_encode_hex
}