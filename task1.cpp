#include <string>

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
	Star(Regex* op){
		this->operand = op;
	};
};

class Seq : public Regex{
public:
	Seq(){

	};
}

//------------------

int CharClass::match(char const *text){
	return contents.find(*text) == std::string::npos ? -1 : 1;
}

int Star::match(char const *text){
	int n, consumed = 0;

	while((n = operand->match(text)) > 0){	//matchar 1 tecken åt gången, n = (1 || -1)
		consumed +=n;
		text += n;		//fel? borde vara (n > 0) ? *text++;
	}

	return consumed;
}

int Seq::match(char const *text){
	int chars, consumed = 0;
	for(auto c:cells){
		if((chars = c->match(text)) < 0) return -1;

		consumed += chars;
		text += chars;		//fel? borde vara *text += chars;
	}
	return consumed;
}