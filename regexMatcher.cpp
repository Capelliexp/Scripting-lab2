#ifndef REGEXMATCHER_CPP
#define REGEXMATCHER_CPP 

#include <string>
#include <iostream>
#include <list>
#include <initializer_list>

class Regex{
public:
	virtual int match(char const *) = 0;
};

class CharClass : public Regex{
public:
	std::string contents;

	int match(char const *text);
	CharClass(std::string c){
		this->contents = c;
	};
};

class Star : public Regex{
public:
	Regex* operand;

	int match(char const *text);
	Star(Regex* op){
		this->operand = op;
	};
};

class Seq : public Regex{
public:
	std::list<Regex*> cells;

	int match(char const *text);
	Seq(std::initializer_list<Regex*> c){
		this->cells = c;
	};
};

//------------------

int CharClass::match(char const *text){
	//std::cout << "CharClass::match jämför " << this->contents << " med " << text << std::endl;
	if(contents.find(*text) == std::string::npos){
		//std::cout << "CharClass returnerar -1" << std::endl;
		return -1;
	}
	//std::cout << "CharClass returnerar 1" << std::endl;
	return 1;
}

int Star::match(char const *text){
	int n, consumed = 0;
	//std::cout << "Star::match *text: " << text << std::endl;

	while((n = operand->match(text)) > 0){	//matchar 1 tecken åt gången, n = (1 || -1)
		consumed +=n;
		//text += n;	//ersatt denna med if-satsen under
		if(n > 0)
			text++;
	}
	//std::cout << "Star:match consumed:" << consumed << std::endl;
	return consumed;
}

int Seq::match(char const *text){
	int i = 0;
	int chars, consumed = 0;
	for(auto c:cells){
		if((chars = c->match(text)) < 0) return 0;
		//std::cout << "Seq:match " << text << std::endl;
		consumed += chars;
		text += chars;		//fel? borde vara *text += chars;
		i++;
		//std::cout << i << std::endl;
	}
	//std::cout << "Seq::match äter " << consumed << " platser" << std::endl;
	if(consumed > 0) input += consumed;
	return consumed;
}

CharClass digit("0123456789");
CharClass nonzero("123456789");
CharClass hexDigits("0123456789abcdefABCDEF");
CharClass dot(".");
CharClass zero("0");
CharClass x("x");
CharClass lettersSmall("abcdefghijklmnopqrstuvwxyz");
CharClass lettersSmallAndBig("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
CharClass lettersAndDigits("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
CharClass lettersAndDigitsAndSymbols("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#¤&/()=?`'][€$£@^~*-_.:,<>§ ");

Seq hex({&zero, &x,&hexDigits, new Star(&hexDigits)}); //[0][x][a-zA-Z0-9]*
Seq decimal({&nonzero, new Star(&digit), &dot, new Star(&digit)});	//[1-9][0-9]*.[0-9]*
Seq nonDecimal({&nonzero, new Star(&digit)});	//[1-9][0-9]*
Seq identifier({&lettersSmallAndBig, new Star(&lettersAndDigits)});	//[a-zA-Z][a-zA-Z0-9]
Seq string({new Star(&lettersAndDigitsAndSymbols)});	//"[a-zA-Z0-9!-§]*"

#endif