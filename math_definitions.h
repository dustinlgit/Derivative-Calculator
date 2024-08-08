#ifndef MATH_DEFINITIONS_H
#define MATH_DEFINITIONS_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cassert>

const std::string varName = "T";
const std::vector<std::string> mathLeftBrackets = {
	"(",
	"[",
	"{"
};
const std::vector<std::string> mathBrackets = {
	"(",
	")",
	"[",
	"]",
	"{",
	"}"
};
const std::vector<std::string> mathOperators = {
	"+",
	"-",
	"*",
	"/",
	"^",
	"arcsin",
	"arccos",
	"arctan",
	"cos",
	"sin",
	"tan",
	"cot",
	"sec",
	"csc",
	"sqrt",
	"log",
	"ln"
};
const std::vector<std::string> mathConstants = {
	"E",
	"PI"
};
const std::vector<std::string> mathSpecialStrings = {
	"(",
	")",
	"+",
	"-",
	"*",
	"/",
	"^",
	"arcsin",
	"arccos",
	"arctan",
	"cos",
	"sin",
	"tan",
	"cot",
	"sec",
	"csc",
	"sqrt",
	"log",
	"ln",
	"PI",
	"E",
	varName
};
const std::map<std::string, int> operatorPrecedence = {
	{"+", 2},
	{"-", 2},
	{"*", 3},
	{"/", 3},
	{"^", 5},
	{"arcsin", 4},
	{"arccos", 4},
	{"arctan", 4},
	{"cos", 4},
	{"sin", 4},
	{"tan", 4},
	{"cot", 4},
	{"sec", 4},
	{"csc", 4},
	{"sqrt", 4},
	{"log", 4},
	{"ln", 4}
};
const std::map<std::string, bool> associatesLeft = {
	{"+", true},
	{"-", true},
	{"*", true},
	{"/", true},
	{"^", true},
	{"arcsin", false},
	{"arccos", false},
	{"arctan", false},
	{"cos", false},
	{"sin", false},
	{"tan", false},
	{"cot", false},
	{"sec", false},
	{"csc", false},
	{"sqrt", false},
	{"log", false},
	{"ln", false}
};
const std::map<std::string, int> operatorArguments = {
	{"+", 2},
	{"-", 2},
	{"*", 2},
	{"/", 2},
	{"^", 2},
	{"arcsin", 1},
	{"arccos", 1},
	{"arctan", 1},
	{"cos", 1},
	{"sin", 1},
	{"tan", 1},
	{"cot", 1},
	{"sec", 1},
	{"csc", 1},
	{"sqrt", 1},
	{"log", 1},
	{"ln", 1}
};

typedef std::string Token;

#endif