#pragma once

#include <string>
#include <any>
#include <utility>
#include "TokenType.hpp"

class Token {

public:
	Token(
		TokenType type,
		std::string lexeme,
		std::any literal,
		int line) : 
		type{ type }, lexeme{ std::move(lexeme) }, 
		literal{ std::move(literal) }, line{line}
	{};

	std::string toString() const {
		/**/
		std::string lt;

		switch (type) {
		case (IDENTIFIER):
			lt = lexeme;
			break;
		case (STRING):
			lt = std::any_cast<std::string>(literal);
			break;
		case(NUMBER):
			lt = std::to_string(std::any_cast<double>(literal));
			break;
		case(TRUE):
			lt = "true";
			break;
		case(FALSE):
			lt = "true";
			break;
		default:
			lt = "nil";
		}

		return tokenTypeToString(type) + " " + lexeme + " " + lt;

	}
	
public:
	TokenType getTokenType() const { return type; };

private:
	const TokenType type;
	const std::string lexeme;
	const std::any literal;
	const int line;
};