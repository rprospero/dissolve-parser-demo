#include "Visitor.h"

antlrcpp::Any MyVisitor::visitMasterAngle(DissolveParser::MasterAngleContext *context) {
  std::string name = visit(context->str());
  BondKind bond = visit(context->bondKind());
  references_["@"+name] = bond;
  return name;
}

antlrcpp::Any MyVisitor::visitMasterBond(DissolveParser::MasterBondContext *context) {
  std::string name = visit(context->str());
  BondKind bond = visit(context->bondKind());
  references_["@"+name] = bond;
  return name;
}

antlrcpp::Any MyVisitor::visitMasterTorsion(DissolveParser::MasterTorsionContext *context) {
  std::string name = visit(context->str());
  BondKind bond = visit(context->bondKind());
  references_["@"+name] = bond;
  return name;
}
