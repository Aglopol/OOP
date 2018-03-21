#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "IniParser.h"

int main() {
	std::ifstream fin("lab01_input_correct_09.ini");
	IniParser parser(fin);
	parser.ShowAll();
	std::cout << parser.IsHaveParam("SECTIO", "RaIQType");
	std::getchar();
	return 0;
}