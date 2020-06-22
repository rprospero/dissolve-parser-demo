#include "Visitor.h"
#include <iostream>

antlrcpp::Any MyVisitor::visitProgram(DissolveParser::ProgramContext *context) {
  std::cout << "Program" << std::endl;

  visitChildren(context);

  return true;
}


antlrcpp::Any MyVisitor::visitSection(DissolveParser::SectionContext *context) {
  std::cout << "Section" << std::endl;

  if(context->master()) {
    std::cout << "Master" << std::endl;
  }

  visitChildren(context);

  return true;
}

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
