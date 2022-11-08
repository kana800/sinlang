#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <string_view>

#include "Error.hpp"
#include "Expr.h"
#include "Token.hpp"
#include "TokenType.hpp"


class Parser {


public:
	Parser(const std::vector<Token>& _tokens) : tokens{ _tokens } {};


private: /*methods*/
	std::shared_ptr<Expr> expression() {
		return equality();
	}

	std::shared_ptr<Expr> equality() {
		std::shared_ptr<Expr> expr = comparison();

		while (match(BANG_EQUAL, EQUAL_EQUAL)) {
			Token operator = previous();
			std::shared_ptr<Expr> right = comparison();
			expr = std::make_shared<Binary>(expr, std::move(op), right);
		}
		return expr;
	}

	/*templated class: variadic template?*/
	template <class... T>
	bool match(T... type) {
		assert((... && std::is_same_v<T, TokenType>));

		if ((... || check(type))) {
			advance();
			return true;
		}
		return false;

	}


	bool check(TokenType type) {
		if (isAtEnd()) return false;
		return peek().type == type;
	}

	Token advance() {
		if (!isAtEnd()) ++current;
		return previous();
	}

	bool isAtEnd() {
		return peek().type 
			== END_OF_FILE;
	}

	Token peek() {
		return tokens.at(current);
	}

	Token previous() {
		return tokens.at(current - 1);
	}



private: /*attributes*/
	const std::vector<Token>& tokens;
	int current{ 0 };

};
