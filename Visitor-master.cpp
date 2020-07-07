#include "Visitor.h"

// Store a reference to an angle
antlrcpp::Any MyVisitor::visitMasterAngle(DissolveParser::MasterAngleContext *context) {
  std::string name = visit(context->str());
  BondKind bond = strictBondKind(context->bondKind());
  references_["@"+name] = bond;
  return name;
}

// Store a reference to a bond
antlrcpp::Any MyVisitor::visitMasterBond(DissolveParser::MasterBondContext *context) {
  std::string name = visit(context->str());
  BondKind bond = strictBondKind(context->bondKind());
  references_["@"+name] = bond;
  return name;
}

// Store a reference to a torsion
antlrcpp::Any MyVisitor::visitMasterTorsion(DissolveParser::MasterTorsionContext *context) {
  std::string name = visit(context->str());
  BondKind bond = strictBondKind(context->bondKind());
  references_["@"+name] = bond;
  return name;
}
