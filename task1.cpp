#include <string>

class Regex{
public:
	virtual int match(char const *) = 0;
};

class CharClass : public Regex{
public:
	std::string contents;
	CharClass(std::string c) : contents(c){
		this->contents = c;
	};
};

class Star : public Regex{
public:
	operand //<-- någon typ av pekare
	Star() : ;	//<--
};

//------------------

int CharClass::match(char const *text){
	return contents.find(*text) == std::string::npos ? -1 : 1;
}

int Star::match(char const *text){
	int n, consumed = 0;
	while((n = operand->match(text)) > 0){
		consumed += n;
		text += n;
	}
	return consumed;
}