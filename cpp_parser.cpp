#include <iostream>
#include "antlr4-runtime/antlr4-runtime.h"
#include "DissolveLexer.h"
#include "DissolveParser.h"
#include "Visitor.h"
// #include "ImageVisitor.h"

using namespace std;
using namespace antlr4;
int main(int argc, const char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    std::ifstream stream;
    std::cout << "Loading " << argv[i] << std::endl;
    stream.open(argv[i]);

    ANTLRInputStream input(stream);
    DissolveLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    DissolveParser parser(&tokens);
    DissolveParser::ProgramContext* tree = parser.program();
    // std::cout << tree->toStringTree(&parser) << std::endl;

    MyVisitor visitor;
    visitor.visit(tree);
    std::cout << "********************************************************************************" << std::endl;
  }
  return 0;
}
