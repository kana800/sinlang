#pragma once

#include <iostream>
#include <string>
#include "Token.hpp"

static bool hadError = false;

static void report(
	int line, std::string_view where,
	std::string_view message) {
	/**/
	std::cerr << "[line "
		<< line << "] Error" 
		<< where << ": " 
		<< message << std::endl;
	hadError = true;
}


void error(
	const Token& token, std::string_view message) {
	if (token.getTokenType() == END_OF_FILE) {
		report(token.getLine(), " at end", message);
	}
	else {
		report(token.getLine(), 
			"at '" + token.getLexeme() + "'", message);
	}
}

void error(int line, std::string_view message) {
	report(line, "", message);
}
