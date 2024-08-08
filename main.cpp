#include <iostream>
#include <string>

#include "math_definitions.h"
#include "polish_notation_converter.h"
#include "derivative.h"
#include "simplify.h"

int main(int argc, char** argv) {
	bool debug = false;

	if(argc == 2) {
		std::string str = argv[1];
		if(str == "--debug") {
			debug = true;
		}
	}

	PolishNotationConverter converter;
	std::string input;

	while(true) {
		std::cout << "Equation to differentiate, or q to quit: ";
		std::cin >> input;
		if(input == "q") {
			break;
		}
		std::cout << std::endl;
		std::vector<Token> infix = converter.ParseString(input);
		if(debug) {
			std::cout << "Tokenized:" << std::endl;
			for(int i=0; i<int(infix.size()); ++i) {
				std::cout << infix[i] << " ";
			}
			std::cout << std::endl << std::endl;
		}

		std::vector<Token> prefix = converter.InfixToPrefix(infix);
		if(debug) {
			std::cout << "Prefix:" << std::endl;
			for(int i=0; i<int(prefix.size()); ++i) {
				std::cout << prefix[i] << " ";
			}
			std::cout << std::endl << std::endl;
		}

		std::vector<Token> derivative = differentiate(prefix);
		if(debug) {
			std::cout << "Derivative:" << std::endl;
			for(int i=0; i<int(derivative.size()); ++i) {
				std::cout << derivative[i] << " ";
			}
			std::cout << std::endl << std::endl;
		}

		std::vector<Token> infix2 = converter.PrefixToInfix(derivative, 0, true);
		if(debug) {
			std::cout << "Infix:" << std::endl;
			for(int i=0; i<int(infix2.size()); ++i) {
				std::cout << infix2[i] << " ";
			}
			std::cout << std::endl << std::endl;
		}

		simplify(derivative, debug);

		std::vector<Token> infix3 = converter.PrefixToInfix(derivative, 0, true);
		if(debug) {
			std::cout << "Simplified infix:" << std::endl;
			for(int i=0; i<int(infix3.size()); ++i) {
				std::cout << infix3[i] << " ";
			}
			std::cout << std::endl << std::endl;
		}

		std::string output = converter.OutputString(infix3);

		std::cout << "Result:" << std::endl;
		std::cout << output << std::endl << std::endl;
	}

	return 0;
}