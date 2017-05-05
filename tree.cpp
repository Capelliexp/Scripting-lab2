#ifndef TREE_CPP
#define TREE_CPP 

class Tree {
public:
  std::string lexeme, tag;
  std::list<Tree*> children;

  Tree(std::string t, int start, int end);
  void dump(int depth=0);
};

Tree::Tree(std::string t, int start, int end){
  this->tag = t;
  this->lexeme = globalLine.substr(start, (end-start));
}

void Tree::dump(int depth){

  for(int i=0; i < depth; i++)
    std::cout << "  ";
  std::cout << tag << ": " << lexeme << std::endl;

  while((children.size()) > 0){
    children.front()->dump(depth+1);
    children.pop_front();
  }
}
#endif