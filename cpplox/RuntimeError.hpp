#pragma once

#include <stdexcept>
#include <string_view>
#include "Token.hpp"

class RunTimeError : public std::runtime_error {
public:
	const Token& token;
	
	RunTimeError(const Token& token, std::string_view message):
		std::runtime_error{ message.data(), token{token} }
	{}
};