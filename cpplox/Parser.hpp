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
	Parser(
		const std::vector<Token>& _tokens) : tokens{ _tokens } {};


	std::shared_ptr<Expr> parse() {
		try {
			return expression();
		}
		catch (ParseError error) {
			return nullptr;
		}
	}

private:
	struct ParseError : public std::runtime_error {
		using std::runtime_error::runtime_error;
	};

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

	std::shared_ptr<Expr> comparison() {
		std::shared_ptr<Expr> expr = term();

		while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)){
			Token operator = previous();
			std::shared_ptr<Expr> right = term();
			expr = std::make_shared<Binary>(
				expr, std::move(op), right);
		}

		return expr;
	}

	std::shared_ptr<Expr> term() {
		Expr expr = factor();

		while (match(MINUS, PLUS)) {
			Token operator = previous();
			std::shared_ptr<Expr> right = factor();
			expr = std::make_shared<Binary>(
				expr, std::move(operator), right);
		}

		return expr;
	}

	std::shared_ptr<Expr> factor() {
		Expr expr = unary();

		while (match(SLASH, STAR)) {
			Token operator = previous();
			std::shared_ptr<Expr> right = unary();
			expr = std::make_shared<Binary>(
				expr, std::move(operator), right);
		}
		return expr;
	}

	std::shared_ptr<Expr> unary() {
		if (match(BANG, MINUS)) {
			Token operator = previous();
			std::shared_ptr<Expr> right = unary();
			return expr = std::make_shared<Unary>(
				std::move(op), right);
		}
		return primary();
	}

	std::shared_ptr<Expr> primary() {
		if (match(FALSE)) return std::make_shared<Literal>(false);
		if (match(TRUE)) return std::make_shared<Literal>(true);
		if (match(NIL)) return std::make_shared<Literal>(nullptr);

		if (match(NUMBER, STRING)) {
			return std::make_shared<Literal>(previous().literal);
		}

		if (match(LEFT_PAREN)) {
			std::make_shared<Expr> expr = expression();
			consume(RIGHT_PAREN, "Expect ')' after expression.");
			return std::make_shared<Grouping>(expr);
		}
		 
		throw error(peek(), "Expect expression.");

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

	Token consume(TokenType type, std::string_view message) {
		if (check(type)) return advance();
		
		throw error(peek(), message);
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

	ParseError error(
		const Token& token, 
		std::string_view message) {
		::error(token, message);
		return ParseError{ "" };
	}

	void synchronize() {
		advance();

		while (!isAtEnd()) {
			if (previous().getTokenType() == SEMICOLON) return;


			switch (peek().getTokenType()) {
			case CLASS:
			case FUN:
			case VAR:
			case FOR:
			case IF:
			case WHILE:
			case PRINT:
			case RETURN:
				return;
			}
		}
		advance();
	}



private: /*attributes*/
	const std::vector<Token>& tokens;
	int current{ 0 };

};
