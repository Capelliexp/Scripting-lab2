#include "regexMatcher.cpp"

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	CharClass digit("01234567");
	CharClass nonzero("1234567");
	CharClass dot(".");

	//std::string testString = "123";
	//std::cout << digit.match(&testString[0]) << std::endl;

	Seq number({&nonzero, new Star(digit), &dot, digit, new Star(digit) });	//lost på vad dessa ska innehålla...

	return 1;
}