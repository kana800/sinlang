#include "cpplox/Lox.hpp"

int main(int argc, char* argv[]) {

	if (argc > 1) {
		std::cout << "Usage: cpplox [script]";
		exit(64);
	}
	else if (argc == 2) {
		runFile(argv[1]);
	}
	else {
		runPrompt();
	}

	return 0;
}