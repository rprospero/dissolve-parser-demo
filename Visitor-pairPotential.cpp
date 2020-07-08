#include "Visitor.h"
#include "types.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

antlrcpp::Any
MyVisitor::visitPairPotential(DissolveParser::PairPotentialContext *context) {
  return PairPotential{
      visitVector<PairPotentialParameters>(context->pairPotentialsParameters()),
      visitFirst(context->pairPotentialsRange(), 0.0,
		 [](auto ctx) { return ctx->num(); }),
      visitFirst(context->pairPotentialsDelta(), 0.0,
		 [](auto ctx) { return ctx->num(); }),
      visitFirst(context->pairPotentialsIncludeCoulomb(), false,
		 [](auto ctx) { return ctx->boolean(); }),
      visitFirst(context->pairPotentialsCoulombTruncation(), false,
		 [](auto ctx) { return ctx->truncation(); }),
      visitFirst(context->pairPotentialsShortRangeTruncation(), false,
		 [](auto ctx) { return ctx->truncation(); })};
}

antlrcpp::Any MyVisitor::visitPairPotentialsParameters(
    DissolveParser::PairPotentialsParametersContext *context) {
  return PairPotentialParameters(visit(context->name), visit(context->element),
				 visit(context->strength),
				 visit(context->pp()));
}

antlrcpp::Any MyVisitor::visitPp(DissolveParser::PpContext *context) {
  if (context->lj()) {
    return PP(PP::LJ, visitVector<double>(context->lj()->num()));
  }
  if (context->ljGeometric()) {
    return PP(PP::LJGeometric,
	      visitVector<double>(context->ljGeometric()->num()));
  }
};

antlrcpp::Any
MyVisitor::visitTruncation(DissolveParser::TruncationContext *context) {
  return context->getText() == "Shifted";
}
