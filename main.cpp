#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//GLOBAL VARIABLES
std::string globalLine;
//char* input = &globalLine[0];
int input = 0;

//#include "regexMatcher.cpp"
#include "parser.cpp"

int main(){
	/*std::string testStrings[13] = {
		"0x1", "0xfed", "0xCBA9", "0x00000000", "12ef", "0y7", "0xG900", "151.43",
		"032.010", "goodVar", "0badVar", "\"test string\"", "bad test string\""
	};

	for(int i = 0; i < 7; i++){
		std::cout << "(hex) " << testStrings[i] << ": " << hex.match(&testStrings[i][0]) << std::endl;
	}

	for(int i = 7; i < 9; i++){
		std::cout << "(deci) " <<  testStrings[i] << ": " << decimal.match(&testStrings[i][0]) << std::endl;
	}

	for(int i = 9; i < 11; i++){
		std::cout << "(ID) " <<  testStrings[i] << ": " << identifier.match(&testStrings[i][0]) << std::endl;
	}
	for(int i = 11; i < 13; i++){
		std::cout << "(str) " <<  testStrings[i] << ": " << string.match(&testStrings[i][0]) << std::endl;
	}*/
	
	std::string testCode[10] = {
		"{}", "{1,2;3}", "{1,2;3,}", "{easyas=\"abc\";2;2,[\"hello\"]=\"world\",[3]=4}", 
		"{{1,2,3},data={0x77}}", "{{}", "{;}", "{1,,}", "{34=7}", "{alpha=beta=gamma}"
	};

	for(int i = 0; i < 10; i++){
		globalLine = testCode[i];
		input = 0;
		std::cout << testCode[i] << "  :  " << TABLE() << std::endl;
	}

	//globalLine = testCode[1];
	//std::cout << TABLE() << std::endl;

	return 1;
}