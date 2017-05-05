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
		
RIGHT_HAND : NUMBER | identifier | """ string """ | hex | TABLE

OPERATIONS : LEFT_HAND "=" RIGHT_HAND
*/
//--------------------------
#include "regexMatcher.cpp"
#include "tree.cpp"

bool TERM(Tree **result, char lit);
bool TABLE(Tree **result);
bool TABLE2(Tree **result);
bool TABLE3(Tree **result);
bool FIELD(Tree **result);
bool NUMBER(Tree **result);
bool SEPERATOR(Tree **result);
bool LEFT_HAND(Tree **result);
bool RIGHT_HAND(Tree **result);
bool OPERATIONS(Tree **result);

bool TERM(Tree **result, char lit){
	int start = input;

    if(globalLine[input] != lit){
    	return false;
    }
	input++;
	*result = new Tree("TERM", start, input);

	return true;
}

bool TABLE(Tree **result){
	Tree *child1;
	Tree *child2;
	Tree *child3;
	int start = input;

	if(TERM(&child1, '{') && TABLE2(&child2) && TERM(&child3,'}')){
		*result = new Tree("TABLE", start, input);
  		(*result)->children.push_back(child1);
  		(*result)->children.push_back(child2);
  		(*result)->children.push_back(child3);
		return true;
	}
	return false;
}

bool TABLE2(Tree **result){
	Tree *child1;
	Tree *child2;
	int start = input;

	if(FIELD(&child1) && TABLE3(&child2)){
		*result = new Tree("TABLE2", start, input);
  		(*result)->children.push_back(child1);
  		(*result)->children.push_back(child2);
		return true;
	}

	input = start;
	*result = new Tree("TABLE2", start, input);
	return true;
}

bool TABLE3(Tree **result){
	Tree *child1;
	Tree *child2;
	int start = input;

	if(SEPERATOR(&child1) && TABLE2(&child2)){
		*result = new Tree("TABLE3", start, input);
  		(*result)->children.push_back(child1);
  		(*result)->children.push_back(child2);
		return true;
	}

	input = start;
	*result = new Tree("TABLE3", start, input);

	return true;
}

bool FIELD(Tree **result){
	Tree *child;
	int start = input;

	if(OPERATIONS(&child) || RIGHT_HAND(&child)){
		*result = new Tree("FIELD", start, input);
  		(*result)->children.push_back(child);
		return true;
	}
	return false;
}

bool NUMBER(Tree **result){
	int start = input;

	if(nonDecimal.match(&globalLine[input]) || decimal.match(&globalLine[input])){
		*result = new Tree("NUMBER", start, input);
		return true;
	}

	return false;
}

bool SEPERATOR(Tree **result){
	Tree *child;
	int start = input;

	if(TERM(&child, ',') || TERM(&child, ';')){
		*result = new Tree("SEPERATOR", start, input);
  		(*result)->children.push_back(child);
		return true;
	}

	return false;
}

bool LEFT_HAND(Tree **result){
	Tree *child1;
	Tree *child2;
	Tree *child3;
	int start = input;

	if(TERM(&child1, '[') && RIGHT_HAND(&child2) && TERM(&child3, ']')){
		*result = new Tree("LEFT_HAND", start, input);
  		(*result)->children.push_back(child1);
  		(*result)->children.push_back(child2);
  		(*result)->children.push_back(child3);
		return true;
	}
	else if(identifier.match(&globalLine[input])){
		*result = new Tree("LEFT_HAND", start, input);
		return true;
	}

	return false;
}

bool RIGHT_HAND(Tree **result){
	Tree *child1;
	Tree *child2;
	int start = input;

	if(identifier.match(&globalLine[input])){
		*result = new Tree("RIGHT_HAND", start, input);
		return true;
	}
	else if(TERM(&child1, '\"') && (string.match(&globalLine[input])) && TERM(&child2, '\"')){
		*result = new Tree("RIGHT_HAND", start, input);
  		(*result)->children.push_back(child1);
  		(*result)->children.push_back(child2);
		return true;
	}
	
	else if(hex.match(&globalLine[input])){
		*result = new Tree("RIGHT_HAND", start, input);
		return true;
	}

	else if(TABLE(&child1)){
		*result = new Tree("RIGHT_HAND", start, input);
  		(*result)->children.push_back(child1);
		return true;
	}
	else if(NUMBER(&child1)){
		*result = new Tree("RIGHT_HAND", start, input);
  		(*result)->children.push_back(child1);
		return true;
	}
	
	return false;
}

bool OPERATIONS(Tree **result){
	Tree *child1;
	Tree *child2;
	Tree *child3;
	int start = input;

	if(LEFT_HAND(&child1) && TERM(&child2, '=') && RIGHT_HAND(&child3)){
		*result = new Tree("OPERATIONS", start, input);
  		(*result)->children.push_back(child1);
  		(*result)->children.push_back(child2);
  		(*result)->children.push_back(child3);
		return true;
	}

	return false;
}
