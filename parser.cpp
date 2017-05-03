/*
hex : [0][x][a-zA-Z0-9]*
decimal : [1-9][0-9]*.[0-9]*
nonDecimal : [1-9][0-9]*
identifier : [a-zA-Z][a-zA-Z0-9]
string : "[a-zA-Z0-9!-§]*"

TABLE : "{" TABLE2 "}"
	TABLE2 : empty | FIELD TABLE3
		TABLE3 : empty | SEPARATOR TABLE2

FIELD : OPERATIONS | RIGHT_HAND

NUMBER : decimal | nonDecimal

SEPARATOR : "," | ";"

LEFT_HAND : identifier | "[" RIGHT_HAND "]" 
		
RIGHT_HAND : NUMBER | identifier | string | hex | TABLE

OPERATIONS : LEFT_HAND "=" RIGHT_HAND
*/
//--------------------------
#include "regexMatcher.cpp"

bool TABLE();
bool TABLE2();
bool TABLE3();
bool FIELD();
bool NUMBER();
bool SEPERATOR();
bool LEFT_HAND();
bool RIGHT_HAND();
bool OPERATIONS();

bool TERM(char lit){
	//std::cout << "TERM ska nu ta bort " << lit << " från " << globalLine[input] << std::endl;

    if(globalLine[input] != lit){
    	return false;
    }
  
	input++;
	//std::cout << "TERM < " << input << std::endl;;
	return true;
}

bool TABLE(){
	if(TERM('{') && TABLE2() && TERM('}')){
		//std::cout << "TABLE < " << input << std::endl;;
		return true;
	}
	return false;
}

bool TABLE2(){
	//char *start = input;
	int start = input;

	if(FIELD() && TABLE3()){
		//std::cout << "TABLE2 < " << input << std::endl;;
		return true;
	}

	input = start;
	//std::cout << "TABLE2 (out) ";
	return true;
}

bool TABLE3(){
	//char *start = input;
	int start = input;

	if(SEPERATOR() && TABLE2()){
		//std::cout << "TABLE3 < " << input << std::endl;;
		return true;
	}

	input = start;
	//std::cout << "TABLE3 (out) ";
	return true;
}

bool FIELD(){
	if(OPERATIONS() || RIGHT_HAND()){
		//std::cout << "FIELD < " << input << std::endl;;
		return true;
	}
	return false;
}

bool NUMBER(){
	if(nonDecimal.match(&globalLine[input]) || decimal.match(&globalLine[input])){
		//std::cout << "NUMBER < " << input << std::endl;;
		return true;
	}

	return false;
}

bool SEPERATOR(){
	if(TERM(',') || TERM(';')){
		//std::cout << "SEPERATOR < " << input << std::endl;;
		return true;
	}

	return false;
}

bool LEFT_HAND(){

	if((identifier.match(&globalLine[input])) || (TERM('[') && RIGHT_HAND() && TERM(']'))){
		//std::cout << "LEFT_HAND < " << input << std::endl;;
		return true;
	}
	return false;
}

bool RIGHT_HAND(){
	if(identifier.match(&globalLine[input])){
		//std::cout << "RIGHT_HAND (identifier) < " << input << std::endl;;
		return true;
	}
	if(TERM('\"') && (string.match(&globalLine[input])) && TERM('\"')){
		//std::cout << "RIGHT_HAND (string) < " << input << std::endl;;
		return true;
	}
	
	if(hex.match(&globalLine[input])){
		//std::cout << "RIGHT_HAND (hex) < " << input << std::endl;;
		return true;
	}

	if(TABLE()){
		//std::cout << "RIGHT_HAND (TABLE) < " << input << std::endl;;
		return true;
	}
	if(NUMBER()){
		//std::cout << "RIGHT_HAND (NUMBER) < " << input << std::endl;;
		return true;
	}
	
	return false;
}

bool OPERATIONS(){
	if(LEFT_HAND() && TERM('=') && RIGHT_HAND()){
		//std::cout << "OPERATIONS < " << input << std::endl;;
		return true;
	}

	return false;
}
