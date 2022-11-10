#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Scanner.hpp"
#include "Parser.hpp"
#include "AstPrinter.hpp"



std::string readFile(std::string_view& path) {
	/**/
	/*difference between {} ()*/
	std::ifstream file(path.data(),
		std::ios::in, std::ios::binary | std::ios::ate);

	if (!file) {
		std::cerr <<
			"Cannot Open File " << path << std::endl;
		std::exit(74);
	}

	std::string contents;
	contents.resize(file.tellg());

	file.seekg(0, std::ios::beg);
	file.read(contents.data(),
		contents.size());

	return contents;
}

std::vector<Token> run(std::string_view source) {
	/**/
	Scanner scanner{ source };
	std::vector<Token> tokens = scanner.scanTokens();
	for (const Token& token : tokens) {
		std::cout << token.toString() << "\n";
	}
	Parser parser{ tokens };
	std::shared_ptr<Expr> expr = parser.parse();

	std::cout << AstPrinter{}.print(expr) << std::endl;


	if (hadError) exit(-1);

	/*
	for (const Token& token : tokens) {
		std::cout << token.toString() << "\n";
	}
	*/

	return tokens;
}

void runFile(std::string_view path) {
	/**/
	std::string contents = readFile(path);
	run(contents);
}

void runPrompt(){
	/**/
	for (;;) {
		std::cout << "> ";
		std::string line;
		if (!std::getline(std::cin, line)) break;
		run(line);
	}
}
