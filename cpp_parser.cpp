#include <iostream>
#include "antlr4-runtime/antlr4-runtime.h"
#include "DissolveLexer.h"
#include "DissolveParser.h"
#include "Visitor.h"
// #include "ImageVisitor.h"

using namespace std;
using namespace antlr4;
int main(int argc, const char* argv[]) {
  std::ifstream stream;
  stream.open(argv[1]);

  ANTLRInputStream input(stream);
  DissolveLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  DissolveParser parser(&tokens);
  DissolveParser::ProgramContext* tree = parser.program();
  // std::cout << tree->toStringTree(&parser) << std::endl;

  MyVisitor visitor;
  visitor.visit(tree);
  return 0;
}
