#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include <string>
#include <sstream>
#include <algorithm>

#include "derivative.h" //For getArguments
//#include "polish_notation_converter.h" // REMOVE THIS WHEN NOT DEBUGGING

//Helpers
bool isNumeral(std::string str) {
	//
	return isdigit(str[0]) || (int(str.size() > 1 && isdigit(str[1])));
}

//Simplify rules:
bool timesOne(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "*") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "1") {
				os << "Times 1 in arg 1!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i, function.begin()+i+2);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
			else if(args.second[0] == "1") {
				os << "Times 1 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool divOne(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "/") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.second[0] == "1") {
				os << "Div 1 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool expOne(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "^") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "1") {
				std::cout << "Exp 1 in arg 1!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
			else if(args.second[0] == "1") {
				os << "Exp 1 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool addZero(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "+") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "0") {
				os << "Add 0 in arg 1!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i, function.begin()+i+2);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
			else if(args.second[0] == "0") {
				os << "Add 0 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool subZero(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "-") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "0") {
				os << "Sub 0 in arg 1!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				std::replace(function.begin()+i, function.begin()+i+1, std::string("-"), std::string("*"));
				std::replace(function.begin()+i+1, function.begin()+i+2, std::string("0"), std::string("-1"));
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
			else if(args.second[0] == "0") {
				os << "Sub 0 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool timesZero(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "*") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "0") {
				std::cout << "Times 0 in arg 1!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
			else if(args.second[0] == "0") {
				os << "Times 0 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i, function.begin()+i+1+int(args.first.size()));
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool divZero(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "/") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			os << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "0") {
				std::cout << "Div 0 in arg 1!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()), function.begin()+i+1+int(args.first.size())+int(args.second.size()));
				function.erase(function.begin()+i);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
			else if(args.second[0] == "0") {
				std::cout << "Div 0 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					std::cout << function[i] << " ";
				}
				std::cout << std::endl;
				std::cout << "ERROR DIVIDE BY ZERO" << std::endl;
				assert(false);
			}
		}
	}
	return false;
}
bool expZero(std::vector<Token> & function, std::ostream & os) {
	return false;
}
bool evalAddSub(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "+" || function[i] == "-") {
			if(isNumeral(function[i+1]) && isNumeral(function[i+2])) {
				os << "Add/sub arithmetic!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				if(function[i] == "+") {
					function[i] = std::to_string(stod(function[i+1])+stod(function[i+2]));
				}
				else {
					function[i] = std::to_string(stod(function[i+1])-stod(function[i+2]));
				}
				function.erase(function.begin()+i+1, function.begin()+i+3);
				os << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					os << function[i] << " ";
				}
				os << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool evalMultDiv(std::vector<Token> & function, std::ostream & os) {
	return false;
}
bool evalExp(std::vector<Token> & function, std::ostream & os) {
	return false;
}
bool evalSqrt(std::vector<Token> & function, std::ostream & os) {
	return false;
}
bool lnEIdentity(std::vector<Token> & function, std::ostream & os) {
	return false;
}
bool trigPiIdentities(std::vector<Token> & function, std::ostream & os) {
	return false;
}
bool trimTrailingZeros(std::vector<Token> & function, std::ostream & os) {
	for(int i=0; i<int(function.size()); ++i) {
		if(isNumeral(function[i])) {
			if(function[i].find('.') != std::string::npos) {
				if(function[i].back() == '0') {
					os << "Trimming trailing zeros..." << std::endl;
					for(int i=0; i<int(function.size()); ++i) {
						os << function[i] << " ";
					}
					os << std::endl;
					while(function[i].back() == '0') {
						function[i].pop_back();
					}
					if(function[i].back() == '.') {
						function[i].pop_back(); //If it ends with an unnecessary decimal point, clear that out too
					}
					os << "Now it's" << std::endl;
					for(int i=0; i<int(function.size()); ++i) {
						os << function[i] << " ";
					}
					os << std::endl;
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<bool(*)(std::vector<Token>&, std::ostream&)> simplifyFunctions = {
	timesOne,
	divOne,
	expOne,
	addZero,
	subZero,
	timesZero,
	divZero,
	expZero,
	evalAddSub,
	evalMultDiv,
	evalExp,
	evalSqrt,
	lnEIdentity,
	trigPiIdentities,
	trimTrailingZeros
};

//Call this to actually do the thing
void simplify(std::vector<Token> & function, bool detail) {
	std::stringstream dummy;
	if(detail) {
		std::cout << "Simplifying..." << std::endl;
	}
	bool madeAChange = true;
	while(madeAChange) {
		madeAChange = false;
		for(int i=0; i<int(simplifyFunctions.size()); ++i) {
			if(detail) {
				if(simplifyFunctions[i](function, std::cout)) {
					madeAChange = true;
					break;
				}
			}
			else {
				if(simplifyFunctions[i](function, dummy)) {
					madeAChange = true;
					break;
				}
			}
			// EMERGENCY DEBUGGING CODE
			// PolishNotationConverter pol;
			// for(int i=0; i<int(function.size()); ++i) {
			// 	std::cout << function[i] << " ";
			// }
			// std::cout << std::endl;
			// std::vector<Token> inf = pol.PrefixToInfix(function, 0, true);
			// for(int i=0; i<int(inf.size()); ++i) {
			// 	std::cout << inf[i] << " ";
			// }
			// std::cout << std::endl << std::endl;
		}
	}
	std::cout << std::endl;
}

#endif