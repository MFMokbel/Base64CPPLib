#include "stdafx.h"
#include "base64.h"
#include "CppUnitTest.h"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// all quotes belong to their respective authors

namespace Base64UnitTest
{
	TEST_CLASS(UnitTest3_decode_str)
	{
	public:

		Base64 testb64;

		// test decode_str that takes zero padding char
		TEST_METHOD(test_decode_str_0pchar)
		{
			const std::string originalstr = "Do, or do not. There is no 'try'.";
			Assert::AreEqual(originalstr, testb64.decode_str("RG8sIG9yIGRvIG5vdC4gVGhlcmUgaXMgbm8gJ3RyeScu"), L"0pchar", LINE_INFO());
		}

		// test decode_str that takes one padding char
		TEST_METHOD(test_decode_str_1pchar)
		{
			const std::string originalstr = "His ignorance is encyclopedic";
			Assert::AreEqual(originalstr, testb64.decode_str("SGlzIGlnbm9yYW5jZSBpcyBlbmN5Y2xvcGVkaWM="), L"1pchar", LINE_INFO());
		}

		// test decode_str that takes two padding chars
		TEST_METHOD(test_decode_str_2pchar)
		{
			const std::string originalstr = "Sanity is a madness put to good uses.";
			Assert::AreEqual(originalstr, testb64.decode_str("U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg=="), L"2pchar", LINE_INFO());
		}

		// test decode_str that should fails if base64 encoded string length is not correct
		// such scenario should throw an exception type exception
		TEST_METHOD(test_decode_str_invalid_exception_isthrown_when_length_isnot_correct)
		{
			 // originalstr = "The best way to predict the future is to invent it.";

			auto decode_str_throw_exception = [this]() -> std::string
			{
				return (testb64.decode_str("U2FuaXR5IGlzIGEgbWFkbmVzcyBwdXQgdG8gZ29vZCB1c2VzLg"));
			};

			Assert::ExpectException<std::exception>(decode_str_throw_exception);
		}

		// test decode_str that should fails since encoded and original strings are totally different
		TEST_METHOD(test_decode_str_no_match)
		{
			const std::string originalstr = "The man who goes alone can start today; but he who travels with another must wait till that other is ready.";
			Assert::AreNotEqual(originalstr, testb64.decode_str("U2lsZW5jZSBpcyBhcmd1bWVudCBjYXJyaWVkIG91dCBieSBvdGhlciBtZWFucy4="), L"no_match", LINE_INFO());
		}

	}; // UnitTest3_decode_str
}