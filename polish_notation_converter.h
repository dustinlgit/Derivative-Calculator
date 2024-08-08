
#ifndef POLISH_NOTATION_CONVERTER_H
#define POLISH_NOTATION_CONVERTER_H

#include <string>
#include <vector>
#include <algorithm>
#include <stack>

#include "math_definitions.h"

class PolishNotationConverter {
public:
	PolishNotationConverter() {} //Only constructor needed

	std::vector<Token> ParseString(std::string str) {
		std::vector<Token> infix;

		bool lastCharNumber = false; //Used to determine whether - means subtraction or negative

		while(int(str.length()) > 0) {
			//Clear out whitespace at the beginning of str, stop if the string is now empty
			if(clearLeadingWhitespace(str)) {
				break;
			}

			bool found = false;

			//Check if we're reading in a negative number/number
			bool isNegative = !lastCharNumber && checkIfNegative(str);
			bool isNumber = isNegative || isdigit(str[0]);
			found = found || isNumber;

			//Check if it's a constant
			bool isConstant = false;
			std::string whichConstant = "";
			if(!found) {
				isConstant = checkIfConstant(str, whichConstant);
			}
			found = found || isConstant;

			//Check if it's a parentheses
			bool isBracket = false;
			bool isLeftBracket = false;
			std::string whichBracket = "";
			if(!found) {
				isBracket = checkIfBracket(str, whichBracket, isLeftBracket);
			}
			found = found || isBracket;

			//Check if it's an operator
			bool isOperator = false;
			std::string whichOperator = "";
			if(!found) {
				isOperator = checkIfOperator(str, whichOperator);
			}
			found = found || isOperator;

			//Check if it's the parameter
			bool isVar = false;
			if(!found) {
				isVar = checkIfVariable(str);
			}
			found = found || isVar;

			if(!found) {
				std::cout << "Invalid input" << std::endl;
			}
			assert(found); //Better find it!

			lastCharNumber = isNumber || isConstant || isVar;

			//Now, we have the following booleans to help us determine what to do:
			//isNegative, isNumber, isConstant, isBracket, isVar, isOperator
			if(isNumber) {
				std::string number = "";
				if(isNegative) {
					number += "-";
					str.erase(str.begin());
				}
				while(str.length() > 0 && isdigit(str[0])) {
					number += str[0];
					str.erase(str.begin());
				}
				infix.push_back(number);
			}
			else if(isConstant) {
				str.erase(str.begin(), str.begin()+int(whichConstant.size()));
				infix.push_back(whichConstant);
			}
			else if(isBracket) {
				str.erase(str.begin(), str.begin()+int(whichBracket.size()));
				if(isLeftBracket) {
					infix.push_back("(");
				}
				else {
					infix.push_back(")");
				}
			}
			else if(isVar) {
				str.erase(str.begin());
				infix.push_back(varName);
			}
			else if(isOperator) {
				str.erase(str.begin(), str.begin()+int(whichOperator.size()));
				infix.push_back(whichOperator);
			}
		}

		return infix;
	}
	std::vector<Token> InfixToPrefix(std::vector<Token> infix) {
		//The shunting yard algorithm
		std::vector<Token> prefix;
		std::stack<Token> operatorStack;
		Token stackLast;
		std::string unusedString;

		std::reverse(infix.begin(), infix.end());
		// std::cout << "REVERSED" << std::endl;
		// for(int i=0; i<int(infix.size()); ++i) {
		// 	std::cout << infix[i] << std::endl;
		// }
		for(int i=0; i<int(infix.size()); ++i) {
			if(checkIfConstant(infix[i], unusedString) ||
			   checkIfNegative(infix[i]) ||
			   isdigit(infix[i][0]) ||
			   infix[i] == varName) {
				//If it's a number
				prefix.push_back(infix[i]);
			}
			else if(infix[i] == ")") { //So it was originally (
				operatorStack.push(infix[i]);
			}
			else if(infix[i] == "(") { //So it was originally )
				assert(operatorStack.size() > 0);
				stackLast = operatorStack.top();
				operatorStack.pop();
				while(stackLast != ")") { //So it was originally (
					prefix.push_back(stackLast);
					if(stackLast != ")") {
						assert(operatorStack.size() > 0);
						stackLast = operatorStack.top();
						operatorStack.pop();
					}
				}
			}
			else if(checkIfOperator(infix[i], unusedString)) {
				if(int(operatorStack.size()) == 0 || operatorStack.top() == ")") {
					//So it was originally (
					operatorStack.push(infix[i]);
				}
				else if(operatorPrecedence.find(infix[i])->second > operatorPrecedence.find(operatorStack.top())->second) {
					operatorStack.push(infix[i]);
				}
				else if(operatorPrecedence.find(infix[i])->second == operatorPrecedence.find(operatorStack.top())->second &&
					!(associatesLeft.find(infix[i])->second)) {
					operatorStack.push(infix[i]);
				}
				else {
					prefix.push_back(operatorStack.top());
					operatorStack.pop();
					operatorStack.push(infix[i]);
				}
			}
		}

		while(int(operatorStack.size()) > 0) {
			prefix.push_back(operatorStack.top());
			operatorStack.pop();
		}
		for(int i=0; i<int(prefix.size()); ++i) {
			if(prefix[i] == ")") { //So it was originally (
				assert(false); //Mismatched parentheses!
			}
		}

		std::reverse(prefix.begin(), prefix.end());

		return prefix;
	}
	std::vector<Token> PrefixToInfix(std::vector<Token> prefix, int parentPrecedence, bool parentAssociatesLeft) {
		std::vector<Token> infix;
		std::string dummyString;
		bool addBrackets = !parentAssociatesLeft;
		if(checkIfOperand(prefix[0])) {
			if(addBrackets) { infix.push_back("("); }
			infix.push_back(prefix[0]);
			if(addBrackets) { infix.push_back(")"); }
			return infix;
		}
		else {
			std::string op = prefix[0];
			addBrackets = addBrackets || (operatorPrecedence.find(op)->second <= parentPrecedence);
			// std::cout << "OP: " << op << "\tBrackets: " << addBrackets << std::endl;
			if(operatorArguments.find(op)->second == 1) {
				if(addBrackets) { infix.push_back("("); }
				infix.push_back(prefix[0]);
				std::vector<Token> prefix_(prefix.begin()+1, prefix.end());
				std::vector<Token> infix_ = PrefixToInfix(prefix_, operatorPrecedence.find(op)->second, false);
				infix.insert(infix.end(), infix_.begin(), infix_.end());
				if(addBrackets) { infix.push_back(")"); }
				return infix;
			}
			else if(operatorArguments.find(op)->second == 2) {
				std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(prefix);
				std::vector<Token> infix1 = PrefixToInfix(args.first, operatorPrecedence.find(op)->second, true);
				std::vector<Token> infix2 = PrefixToInfix(args.second, operatorPrecedence.find(op)->second, true);
				if(addBrackets) { infix.push_back("("); }
				infix.insert(infix.end(), infix1.begin(), infix1.end());
				infix.push_back(prefix[0]);
				infix.insert(infix.end(), infix2.begin(), infix2.end());
				if(addBrackets) { infix.push_back(")"); }
				return infix;
			}
		}
		return infix;
	}
	std::string OutputString(std::vector<Token> infix) {
		std::string output;
		for(auto iter = infix.begin(); iter != infix.end(); ++iter) {
			output += *iter;
		}
		return output;
	}

private:
	//Checks if the string token is contained starting from the first
	//character of str
	bool strBeginMatch(const std::string & str, const std::string & token) {
		if(token.size() > str.size()) {
			return false;
		}
		bool match = true;
		for(int i=0; i<int(token.size()); ++i) {
			if(token[i] != str[i]) {
				match = false;
				break;
			}
		}
		return match;
	}
	//Clears any leading whitespace in str, and returns whether or not
	//str is now empty
	bool clearLeadingWhitespace(std::string &str) {
		while(int(str.length())>0 && str[0] == ' ') {
			str.erase(str.begin());
		}
		return int(str.length()) == 0;
	}
	//Check if str starts with a negative number
	bool checkIfNegative(const std::string &str) {
		if(str[0] == '-') {
			if(int(str.size()) >= 2) {
				return isdigit(str[1]); //Note: this will always be true
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	//Check if str starts with a constant name, and if so, stores that constant
	//into whichConstant
	bool checkIfConstant(const std::string &str, std::string &whichConstant) {
		bool isConstant = false;
		for(int i=0; i<int(mathConstants.size()); ++i) {
			if(strBeginMatch(str, mathConstants[i])) {
				isConstant = true;
				whichConstant = mathConstants[i];
				break;
			}
		}
		return isConstant;
	}
	//Check if str starts with a bracket, and if so, stores that bracket
	//into whichBracket
	bool checkIfBracket(const std::string &str, std::string &whichBracket, bool &isLeftBracket) {
		bool isBracket = false;
		for(int i=0; i<int(mathBrackets.size()); ++i) {
			if(strBeginMatch(str, mathBrackets[i])) {
				isBracket = true;
				whichBracket = mathBrackets[i];
				break;
			}
		}
		if(isBracket) {
			for(int i=0; i<int(mathLeftBrackets.size()); ++i) {
				if(strBeginMatch(str, mathLeftBrackets[i])) {
					isLeftBracket = true;
					break;
				}
			}
		}
		return isBracket;
	}
	//Check if str starts with an operator, and if so, stores that operator
	//into whichOperator
	bool checkIfOperator(const std::string &str, std::string &whichOperator) {
		bool isOperator = false;
		for(int i=0; i<int(mathOperators.size()); ++i) {
			if(strBeginMatch(str, mathOperators[i])) {
				isOperator = true;
				whichOperator = mathOperators[i];
				break;
			}
		}
		return isOperator;
	}
	//Check if str starts with the variable
	bool checkIfVariable(const std::string &str) {
		//Only doing this to keep it uniform
		return strBeginMatch(str, varName);
	}
	//Check if str starts with an operand
	bool checkIfOperand(const std::string &str) {
		std::string dummyString;
		return checkIfNegative(str) ||
		       isdigit(str[0]) ||
		       checkIfConstant(str, dummyString) ||
		       checkIfVariable(str);
	}
	//Get the two arguments of a prefix array as prefix arrays
	std::pair<std::vector<Token>, std::vector<Token>> getArguments(std::vector<Token> prefix) {
		assert(operatorArguments.find(prefix[0])->second == 2);

		std::pair<std::vector<Token>, std::vector<Token>> args;
		std::string dummyString;
		int numNeeded = 1;
		int i=1;
		while(numNeeded != 0) {
			if(checkIfOperator(prefix[i], dummyString)) {
				numNeeded += operatorArguments.find(prefix[i])->second;
			}
			--numNeeded;
			++i;
		}
		args.first = std::vector<Token>(prefix.begin()+1, prefix.begin()+i);
		int start = i;
		numNeeded = 1;
		while(numNeeded != 0) {
			if(checkIfOperator(prefix[i], dummyString)) {
				numNeeded += operatorArguments.find(prefix[i])->second;
			}
			--numNeeded;
			++i;
		}
		args.second = std::vector<Token>(prefix.begin()+start, prefix.begin()+i);
		return args;
	}
};

#endif