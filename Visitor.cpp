#include "Visitor.h"
#include "types.h"
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

antlrcpp::Any MyVisitor::visitSpecies(DissolveParser::SpeciesContext *context) {
  std::vector<Atom> atoms;
  std::vector<Bond> bonds;
  std::vector<Angle> angles;
  std::vector<Torsion> torsions;
  std::vector<Isotopologue> isotopologues;
  std::string name = visit(context->name);

  auto terms = context->speciesTerm();

  for (auto &at : context->speciesAtom())
    atoms.push_back(visit(at));
  for (auto &bond : context->speciesBond())
    bonds.push_back(visit(bond));
  for (auto &angle : context->speciesAngle())
    angles.push_back(visit(angle));
  for (auto &torsion : context->speciesTorsion())
    torsions.push_back(visit(torsion));
  // for (auto &isotopologue : context->speciesIsotopologue())
  //   isotopologues.push_back(visit(isotopologue));

  Species result(name, atoms, bonds, angles, torsions, isotopologues);

  std::cout << result << std::endl;

  return result;
}

antlrcpp::Any
MyVisitor::visitSpeciesAtom(DissolveParser::SpeciesAtomContext *context) {
  Atom atom;
  atom.index = std::stoi(context->index->getText());
  atom.position = visit(context->vec3());
  std::string element = visit(context->element);
  atom.element = element;
  std::string type = visit(context->atomtype);
  atom.type = type;
  if (context->charge)
    atom.charge = visit(context->charge);
  return atom;
}

antlrcpp::Any
MyVisitor::visitSpeciesBond(DissolveParser::SpeciesBondContext *context) {
  Bond bond;
  bond.i = std::stoi(context->left->getText());
  bond.j = std::stoi(context->right->getText());
  // auto bond = visit(context->bondKind());
  return bond;
}

antlrcpp::Any
MyVisitor::visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context) {
  Angle angle;
  angle.a = std::stoi(context->INT(0)->getText());
  angle.b = std::stoi(context->INT(1)->getText());
  angle.c = std::stoi(context->INT(2)->getText());
  // auto angle = visit(context->angleKind());
  return angle;
}
antlrcpp::Any
MyVisitor::visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context) {
  Torsion torsion;
  torsion.a = std::stoi(context->INT(0)->getText());
  torsion.b = std::stoi(context->INT(1)->getText());
  torsion.c = std::stoi(context->INT(2)->getText());
  torsion.d = std::stoi(context->INT(3)->getText());
  // auto torsion = visit(context->torsionKind());
  return torsion;
}
antlrcpp::Any MyVisitor::visitSpeciesIsotopologue(
    DissolveParser::SpeciesIsotopologueContext *context) {
  Isotopologue iso;
  iso.name = context->name->getText();
  for (auto v = context->str().begin(); v != context->str().end(); ++v)
    iso.values.push_back(visit(*v));
  return iso;
}
antlrcpp::Any
MyVisitor::visitSpeciesSite(DissolveParser::SpeciesSiteContext *context) {
  SpeciesTerm result = std::make_tuple(-1.5, 0.4);
  return result;
}
antlrcpp::Any MyVisitor::visitSpeciesForcefield(
    DissolveParser::SpeciesForcefieldContext *context) {
  SpeciesTerm result = std::make_tuple(-1.5, 0.4);
  return result;
}

antlrcpp::Any MyVisitor::visitSiteOriginMassWeighted(
    DissolveParser::SiteOriginMassWeightedContext *context) {
  bool activate = visitChildren(context);
  if (activate) {
    std::cout << "Activate Site Origin Mass Weighting" << std::endl;
  } else {
    std::cout << "De-activate Site Origin Mass Weighting" << std::endl;
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
