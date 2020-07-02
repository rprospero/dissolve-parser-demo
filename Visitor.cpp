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
  Vec3 result;
  result.x = visit(context->x);
  result.y = visit(context->y);
  result.z = visit(context->z);
  return result;
}

antlrcpp::Any MyVisitor::visitNum(DissolveParser::NumContext *context) {
  if (context->Num()) {
    double n = std::stof(context->Num()->getText());
    return n;
  }
  double n = std::stof(context->INT()->getText());
  return n;
}
