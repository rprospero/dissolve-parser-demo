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
      (context->pairPotentialsRange().empty())
	  ? 0
	  : visit(context->pairPotentialsRange(0)->num()).as<double>(),
      (context->pairPotentialsDelta().empty())
	  ? 0
	  : visit(context->pairPotentialsDelta(0)->num()).as<double>(),
      (context->pairPotentialsIncludeCoulomb().empty())
	  ? false
	  : visit(context->pairPotentialsIncludeCoulomb(0)->boolean())
		.as<bool>(),
      (context->pairPotentialsCoulombTruncation().empty())
	  ? false
	  : visit(context->pairPotentialsCoulombTruncation(0)->truncation())
		.as<bool>(),
      (context->pairPotentialsShortRangeTruncation().empty())
	  ? false
	  : visit(context->pairPotentialsShortRangeTruncation(0)->truncation())
		.as<bool>()};
};

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
