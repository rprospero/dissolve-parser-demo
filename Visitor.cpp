#include "Visitor.h"
#include "types.h"
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

antlrcpp::Any MyVisitor::visitBoolean(DissolveParser::BooleanContext *context) {
  return context->truthy() != nullptr;
}

antlrcpp::Any MyVisitor::visitStr(DissolveParser::StrContext *context) {
  if (context->QUOTE()) {

    return context->QUOTE()->getText().substr(
	1, context->QUOTE()->getText().length() - 2);
  }
  return context->WORD()->getText();
}

antlrcpp::Any MyVisitor::visitVec3(DissolveParser::Vec3Context *context) {
  return Vec3{visit(context->x), visit(context->y), visit(context->z)};
}

antlrcpp::Any MyVisitor::visitNum(DissolveParser::NumContext *context) {
  if (context->Num()) {
    double n = std::stof(context->Num()->getText());
    return n;
  }
  double n = std::stof(context->INT()->getText());
  return n;
}

// The top level program visitor
antlrcpp::Any MyVisitor::visitProgram(DissolveParser::ProgramContext *context) {
  for (auto ctx : context->master())
    visit(ctx);
  return Program{visitVector<Species>(context->species()),
		 visit(context->pairPotential(0))};
}
