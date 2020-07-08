#include "Visitor.h"
#include "types.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

antlrcpp::Any
MyVisitor::visitPairPotential(DissolveParser::PairPotentialContext *context) {
  std::vector<PairPotentialParameters> params;
  double range = 0, delta = 0;
  bool includeCoulomb = false, coulombShifted = false,
       shortRangeShifted = false;
  for (auto &par : context->pairPotentialsParameters()) {
    params.push_back(visitPairPotentialsParameters(par));
  }
  if (!context->pairPotentialsRange().empty()) {
    range = visit(context->pairPotentialsRange(0)->num());
  }
  if (!context->pairPotentialsDelta().empty()) {
    delta = visit(context->pairPotentialsDelta(0)->num());
  }
  if (!context->pairPotentialsIncludeCoulomb().empty()) {
    includeCoulomb = visit(context->pairPotentialsIncludeCoulomb(0)->boolean());
  }
  if (!context->pairPotentialsCoulombTruncation().empty()) {
    coulombShifted =
	visit(context->pairPotentialsCoulombTruncation(0)->truncation());
  }
  if (!context->pairPotentialsShortRangeTruncation().empty()) {
    shortRangeShifted =
	visit(context->pairPotentialsShortRangeTruncation(0)->truncation());
  }

  return PairPotential(params, range, delta, includeCoulomb, coulombShifted,
		       shortRangeShifted);
};

antlrcpp::Any MyVisitor::visitPairPotentialsParameters(
    DissolveParser::PairPotentialsParametersContext *context) {
  auto result =
      PairPotentialParameters(visit(context->name), visit(context->element),
			      visit(context->strength), visit(context->pp()));
  return result;
}

antlrcpp::Any MyVisitor::visitPp(DissolveParser::PpContext *context) {
  std::vector<double> params;
  if (context->lj()) {
    for (auto p : context->lj()->num())
      params.push_back(visit(p));
    return PP(PP::LJ, params);
  }
  if (context->ljGeometric()) {
    for (auto p : context->ljGeometric()->num())
      params.push_back(visit(p));
    return PP(PP::LJGeometric, params);
  }
};

antlrcpp::Any
MyVisitor::visitTruncation(DissolveParser::TruncationContext *context) {
  return context->getText() == "Shifted";
}
