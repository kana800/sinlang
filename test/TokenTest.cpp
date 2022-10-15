#include "gtest/gtest.h"
#include <iostream>
#include "../cpplox/Lox.hpp"


TEST(TokenTest, ValidToken) {
	std::string_view line_1("// this is a comment");
	std::string_view line_2("!*+-/=<> <= == // operators");
	std::string_view line_3("(( )){} // grouping stuff");

	std::vector<Token> line_1_prog = run(line_1);
	std::vector<Token> line_2_prog = run(line_2);
	std::vector<Token> line_3_prog = run(line_3);

	/*Expected Tokens*/
	std::vector<Token> line_1_test;
	std::vector<Token> line_2_test;
	std::vector<Token> line_3_test;

	/*expected: END_OF_FILE NIL*/
	line_1_test.emplace_back(
		TokenType::END_OF_FILE, "", nullptr, 1);

	/*expected: 
	BANG ! nil
	STAR * nil
	PLUS + nil
	MINUS - nil
	SLASH / nil
	EQUAL = nil
	LESS < nil
	GREATER > nil
	LESS_EQUAL <= nil
	EQUAL_EQUAL == nil
	*/
	line_2_test.emplace_back(TokenType::BANG, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::STAR, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::PLUS, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::MINUS, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::SLASH, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::EQUAL, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::LESS, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::GREATER, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::LESS_EQUAL, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::EQUAL_EQUAL, "", nullptr, 1);
	line_2_test.emplace_back(TokenType::END_OF_FILE, "", nullptr, 1);

	/* expected: 
	LEFT_PAREN ( nil
	LEFT_PAREN ( nil
	RIGHT_PAREN ) nil
	RIGHT_PAREN ) nil
	LEFT_BRACE { nil
	RIGHT_BRACE } nil*/
	line_3_test.emplace_back(
		TokenType::LEFT_PAREN, "", nullptr, 1);
	line_3_test.emplace_back(
		TokenType::LEFT_PAREN, "", nullptr, 1);
	line_3_test.emplace_back(
		TokenType::RIGHT_PAREN, "", nullptr, 1);
	line_3_test.emplace_back(
		TokenType::RIGHT_PAREN, "", nullptr, 1);
	line_3_test.emplace_back(
		TokenType::LEFT_BRACE, "", nullptr, 1);
	line_3_test.emplace_back(
		TokenType::RIGHT_BRACE, "", nullptr, 1);
	line_3_test.emplace_back(
		TokenType::END_OF_FILE, "", nullptr, 1);


	EXPECT_EQ(line_1_test.size(), line_1_prog.size());
	// Iterate through the tokens of string 1
	for (int i = 0; i < line_1_test.size(); ++i) {
		EXPECT_EQ(TokenType::END_OF_FILE,
			line_1_prog[i].getTokenType());
	}

	EXPECT_EQ(line_2_test.size(), line_2_prog.size());
	// Iterate through the tokens of string 1
	for (int i = 0; i < line_2_test.size(); ++i) {
		EXPECT_EQ(line_2_test[i].getTokenType(),
			line_2_prog[i].getTokenType());
	}

	EXPECT_EQ(line_3_test.size(), line_3_prog.size());
	// Iterate through the tokens of string 2
	for (int i = 0; i < line_3_test.size(); ++i) {
		EXPECT_EQ(line_3_test[i].getTokenType(),
			line_3_prog[i].getTokenType());
	}

}
