#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//GLOBAL VARIABLES
std::string globalLine;
int input = 0;

#include "regexMatcher.cpp"
#include "parser.cpp"
#include "tree.cpp"

int main(){
	std::string testCode[10] = {
		"{}", "{1,2;3}", "{1,2;3,}", "{easyas=\"abc\";2;2,[\"hello\"]=\"world\",[3]=4}", 
		"{{1,2,3},data={0x77}}", "{{}", "{;}", "{1,,}", "{34=7}", "{alpha=beta=gamma}"
	};

	Tree *rootTree;

	for(int i = 3; i < 4; i++){
		globalLine = testCode[i];
		input = 0;
		std::cout << "test " << i << ": " << (TABLE(&rootTree) ? " successful" : "   failed  ") << "  >>  " << testCode[i] << std::endl;
	}

	std::cout << std::endl;

	rootTree->dump(0);

	return 1;
}