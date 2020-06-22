#include "Visitor.h"
#include <iostream>
#include <tuple>
#include <vector>


antlrcpp::Any MyVisitor::visitSpecies(DissolveParser::SpeciesContext *context) {
  std::string name = visit(context->name);
  std::cout << "Species " << name << std::endl;

  auto terms = context->speciesTerm();

  for (auto &term : terms) {
    std::tuple<int, int> temp = visit(term);
    std::cout << "(" << std::get<0>(temp) << "," << std::get<1>(temp) << ")" << std::endl;
  }

  return true;
}


antlrcpp::Any MyVisitor::visitSpeciesAtom (DissolveParser::SpeciesAtomContext *context) {
    int index = std::stoi(context->index->getText());
    std::string element = visit(context->element);
    std::cout << "Atom\t" << element << "\t"<< index << std::endl;
    return std::make_tuple(-1, index);
}

antlrcpp::Any MyVisitor::visitSpeciesBond (DissolveParser::SpeciesBondContext *context) {
    int left = std::stoi(context->left->getText());
    int right = std::stoi(context->right->getText());
    // auto bond = visit(context->bondKind());
    std::cout << "Bond from " << left << " to " << right << std::endl;
    return std::make_tuple(left, right);
}

antlrcpp::Any MyVisitor::visitSpeciesAngle (DissolveParser::SpeciesAngleContext *context) {return std::make_tuple(-1, -1);}
antlrcpp::Any MyVisitor::visitSpeciesTorsion (DissolveParser::SpeciesTorsionContext *context) {return std::make_tuple(-1, -1);}
antlrcpp::Any MyVisitor::visitSpeciesIsotopologue (DissolveParser::SpeciesIsotopologueContext *context) {return std::make_tuple(-1, -1);}
antlrcpp::Any MyVisitor::visitSpeciesSite (DissolveParser::SpeciesSiteContext *context) {return std::make_tuple(-1, -1);}
antlrcpp::Any MyVisitor::visitSpeciesForcefield (DissolveParser::SpeciesForcefieldContext *context) {return std::make_tuple(-1, -1);}

antlrcpp::Any MyVisitor::visitSiteOriginMassWeighted (DissolveParser::SiteOriginMassWeightedContext *context) {
  bool activate = visitChildren(context);
  if(activate) {
    std::cout << "Activate Site Origin Mass Weighting" << std:: endl;
  }
  else {
    std::cout << "De-activate Site Origin Mass Weighting" << std:: endl;
  }
  return true;
}


antlrcpp::Any MyVisitor::visitBoolean(DissolveParser::BooleanContext *context) {
  return context->truthy() != nullptr;
}

antlrcpp::Any MyVisitor::visitStr(DissolveParser::StrContext *context) {
  if (context->REF()) {
    return context->REF()->getText();
  }
  if (context->QUOTE()) {
    return context->QUOTE()->getText();
  }
  return context->WORD()->getText();
}
