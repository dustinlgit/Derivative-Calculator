#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <string>
#include <vector>
#include <algorithm>

#include "math_definitions.h"

bool isOperator(Token t) {
	//
	return std::find(mathOperators.begin(), mathOperators.end(), t) != mathOperators.end();
}
bool isNumber(Token t) {
	//
	return isdigit(t[0]) || (t[0] == '-' && int(t.size()) > 1 && isdigit(t[1]));
}
bool isConstant(Token t) {
	//
	return std::find(mathConstants.begin(), mathConstants.end(), t) != mathConstants.end();
}

std::pair<std::vector<Token>, std::vector<Token>> getArguments(std::vector<Token> prefix) {
	assert(operatorArguments.find(prefix[0])->second == 2);

	std::pair<std::vector<Token>, std::vector<Token>> args;
	std::string dummyString;
	int numNeeded = 1;
	int i=1;
	while(numNeeded != 0) {
		if(isOperator(prefix[i])) {
			numNeeded += operatorArguments.find(prefix[i])->second;
		}
		--numNeeded;
		++i;
	}
	args.first = std::vector<Token>(prefix.begin()+1, prefix.begin()+i);
	int start = i;
	numNeeded = 1;
	while(numNeeded != 0) {
		if(isOperator(prefix[i])) {
			numNeeded += operatorArguments.find(prefix[i])->second;
		}
		--numNeeded;
		++i;
	}
	args.second = std::vector<Token>(prefix.begin()+start, prefix.begin()+i);
	return args;
}
void append(std::vector<Token> & target, std::vector<Token> & toAdd) {
	target.insert(target.end(), toAdd.begin(), toAdd.end());
	return;
}

std::vector<Token> differentiate(std::vector<Token> function) {
	if(int(function.size()) == 0) {
		return function; //Empty case to make some recursive things nice
	}

	std::vector<Token> derivative;
	if(!isOperator(function[0])) {
		if(function[0] == varName) {
			//f=T -> f'=1
			derivative.push_back("1");
		}
		else {
			//f=C -> f'=0
			derivative.push_back("0");
		}
	}
	else {
		std::string op = function[0];
		std::vector<Token> u;
		std::vector<Token> v;
		if(operatorArguments.find(op)->second == 1) {
			u = std::vector<Token>(function.begin() + 1, function.end());
		}
		else if(operatorArguments.find(op)->second == 2) {
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(function);
			u = args.first;
			v = args.second;
		}
		else {
			assert(false); //More than 2 args not currently supported
		}

		//Now we differentiate, recursive like
		std::vector<Token> du = differentiate(u);
		std::vector<Token> dv = differentiate(v);
		if(op == "+") {
			derivative.push_back("+");
			append(derivative, du);
			append(derivative, dv);
		}
		else if(op == "-") {
			derivative.push_back("-");
			append(derivative, du);
			append(derivative, dv);
		}
		else if(op == "*") {
			derivative.push_back("+");
			derivative.push_back("*");
			append(derivative, u);
			append(derivative, dv);
			derivative.push_back("*");
			append(derivative, du);
			append(derivative, v);
		}
		else if(op == "/") {
			derivative.push_back("/");
			derivative.push_back("-");
			derivative.push_back("*");
			append(derivative, du);
			append(derivative, v);
			derivative.push_back("*");
			append(derivative, u);
			append(derivative, dv);
			derivative.push_back("^");
			append(derivative, v);
			derivative.push_back("2");
		}
		else if(op == "^") {
			if(isNumber(u[0]) || isConstant(u[0])) {
				derivative.push_back("*");
				derivative.push_back("*");
				derivative.push_back("^");
				append(derivative, u);
				append(derivative, v);
				derivative.push_back("ln");
				append(derivative, u);
				append(derivative, dv);
			}
			else if(isNumber(v[0]) || isConstant(v[0])) {
				derivative.push_back("*");
				derivative.push_back("*");
				append(derivative, v);
				derivative.push_back("^");
				append(derivative, u);
				derivative.push_back("-");
				append(derivative, v);
				derivative.push_back("1");
				append(derivative, du);
			}
			else {
				derivative.push_back("*");
				derivative.push_back("^");
				append(derivative, u);
				append(derivative, v);
				derivative.push_back("+");
				derivative.push_back("*");
				append(derivative, dv);
				derivative.push_back("ln");
				append(derivative, u);
				derivative.push_back("*");
				append(derivative, v);
				derivative.push_back("/");
				append(derivative, du);
				append(derivative, u);
			}
		}
		else if(op == "sin") {
			derivative.push_back("*");
			derivative.push_back("cos");
			append(derivative, u);
			append(derivative, du);
		}
		else if(op == "cos") {
			derivative.push_back("*");
			derivative.push_back("-1");
			derivative.push_back("*");
			derivative.push_back("sin");
			append(derivative, u);
			append(derivative, du);
		}
		else if(op == "tan") {
			derivative.push_back("*");
			derivative.push_back("^");
			derivative.push_back("sec");
			append(derivative, u);
			derivative.push_back("2");
			append(derivative, du);
		}
		else if(op == "cot") {
			derivative.push_back("*");
			derivative.push_back("-1");
			derivative.push_back("*");
			derivative.push_back("^");
			derivative.push_back("csc");
			append(derivative, u);
			derivative.push_back("2");
			append(derivative, du);
		}
		else if(op == "sec") {
			derivative.push_back("*");
			derivative.push_back("sec");
			append(derivative, u);
			derivative.push_back("*");
			derivative.push_back("tan");
			append(derivative, u);
			append(derivative, du);
		}
		else if(op == "csc") {
			derivative.push_back("*");
			derivative.push_back("*");
			derivative.push_back("-1");
			derivative.push_back("csc");
			append(derivative, u);
			derivative.push_back("*");
			derivative.push_back("cot");
			append(derivative, u);
			append(derivative, du);
		}
		else if(op == "arcsin") {
			derivative.push_back("/");
			append(derivative, du);
			derivative.push_back("sqrt");
			derivative.push_back("-");
			derivative.push_back("1");
			derivative.push_back("^");
			append(derivative, u);
			derivative.push_back("2");
		}
		else if(op == "arccos") {
			derivative.push_back("/");
			derivative.push_back("*");
			derivative.push_back("-1");
			append(derivative, du);
			derivative.push_back("sqrt");
			derivative.push_back("-");
			derivative.push_back("1");
			derivative.push_back("^");
			append(derivative, u);
			derivative.push_back("2");
		}
		else if(op == "arctan") {
			derivative.push_back("/");
			append(derivative, du);
			derivative.push_back("+");
			derivative.push_back("1");
			derivative.push_back("^");
			append(derivative, u);
			derivative.push_back("2");
		}
		else if(op == "sqrt") {
			derivative.push_back("/");
			append(derivative, du);
			derivative.push_back("*");
			derivative.push_back("2");
			derivative.push_back("sqrt");
			append(derivative, u);
		}
		else if(op == "log") {
			derivative.push_back("/");
			append(derivative, du);
			derivative.push_back("*");
			append(derivative, u);
			derivative.push_back("ln");
			derivative.push_back("10");
		}
		else if(op == "ln") {
			derivative.push_back("*");
			derivative.push_back("^");
			append(derivative, u);
			derivative.push_back("-1");
			append(derivative, du);
		}
		else {
			assert(false); //Unknown function
		}
	}

	//
	return derivative;
}

#endif