#include "parser.cpp"

class Tree
{
public:
  std::string       lexeme, tag;
  std::list<Tree*> children;
  Tree(std::string t, char *l, int size)
    : tag(t), lexeme(l,size) {}
  void dump(int depth=0)
  {
    for(int i=0; i<depth; i++)
      std::cout << "  ";
    // Recurse over the children
  }
};