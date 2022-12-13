cmake_minimum_required (VERSION 3.8)

set(HEADERS 
	"Lox.hpp"
	"Scanner.hpp"
	"Error.hpp"
	"Options.hpp"
	"TokenType.hpp"
	"Parser.hpp"
 "RuntimeError.hpp")

set(SOURCES 
	"Lox.cpp"
)

add_library(cpplox ${SOURCES} ${HEADERS})
