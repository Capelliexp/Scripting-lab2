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
  //std::cout << "dump START (" << tag << ") with " << children.size() << " children" << std::endl;

  for(int i=0; i < depth; i++)
    std::cout << "  ";
  std::cout << tag << ": " << lexeme << std::endl;

  while((children.size()) > 0){
    //std::cout << "(while) size(): " << children.size() << " " << tag << std::endl;
    children.front()->dump(depth+1);
    children.pop_front();
  }

  //std::cout << "dump END " << tag << std::endl;
}
#endif