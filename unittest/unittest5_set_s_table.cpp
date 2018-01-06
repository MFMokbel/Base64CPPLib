#include "stdafx.h"
#include "base64.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// all quotes belong to their respective authors

namespace Base64UnitTest
{
	TEST_CLASS(UnitTest5_set_s_table)
	{
	public:

		Base64 testb64;

		// test encode_str with different substitution table
		TEST_METHOD(test_set_s_table_different_substitution_table_encode_str)
		{
			auto set_s_table_throw_exception = [this]() -> void
			{
				testb64.set_s_table("The only difference between me and a madman is that I'm not mad.");
				const std::string encodedstr = "clmi lat lct loteenneldmmabnnwfn amnd ct em ";
				testb64.encode_str("Do, or do not. There is no 'try'.");
			};

			Assert::ExpectException<std::exception>(set_s_table_throw_exception);
		}

		// test decode_str with non conformant (not unique chars) substitution table
		TEST_METHOD(test_set_s_table_with_non_conformant_substitution_table_decode_str)
		{

			auto set_s_table_throw_exception = [this]() -> void
			{
				testb64.set_s_table("The only difference between me and a madman is that I'm not mad.");
				const std::string originalstring = "Do, or do not. There is no 'try'.";
				testb64.decode_str("clmi lat lct loteenneldmmabnnwfn amnd ct em ");
			};

			Assert::ExpectException<std::exception>(set_s_table_throw_exception);
		}

		// test set_s_table with wrong substitution table size (!64)
		// such scenario should throw an exception type exception
		TEST_METHOD(test_set_s_table_invalid_exception_isthrown_when_length_isnot_correct)
		{
			auto set_s_table_throw_exception = [this]() -> void
			{
				testb64.set_s_table("ABCDEFGHI");
			};

			Assert::ExpectException<std::exception>(set_s_table_throw_exception);
		}
	}; // UnitTest5_set_s_table
}