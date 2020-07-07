#include "Visitor.h"
#include "types.h"
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

// Parse a single species and print it out
antlrcpp::Any MyVisitor::visitSpecies(DissolveParser::SpeciesContext *context) {
  std::vector<Atom> atoms;
  std::vector<Bond> bonds;
  std::vector<Angle> angles;
  std::vector<Torsion> torsions;
  std::vector<Isotopologue> isotopologues;
  std::vector<Site> sites;
  std::vector<Forcefield> forcefields;
  std::string name = visit(context->name);

  for (auto &at : context->speciesAtom())
    atoms.push_back(visit(at));
  for (auto &bond : context->speciesBond())
    bonds.push_back(visit(bond));
  for (auto &angle : context->speciesAngle())
    angles.push_back(visit(angle));
  for (auto &torsion : context->speciesTorsion())
    torsions.push_back(visit(torsion));
  for (auto &isotopologue : context->speciesIsotopologue())
    isotopologues.push_back(visit(isotopologue));
  for (auto &site : context->speciesSite())
    sites.push_back(visit(site));
  for (auto &forcefield : context->speciesForcefield())
    forcefields.push_back(visit(forcefield));

  Species result(name, atoms, bonds, angles, torsions, isotopologues, sites,
		 forcefields);

  return result;
}

//Parse an Atom from a species
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

//Parse a bond from a species
antlrcpp::Any
MyVisitor::visitSpeciesBond(DissolveParser::SpeciesBondContext *context) {
  Bond bond;
  bond.i = std::stoi(context->left->getText());
  bond.j = std::stoi(context->right->getText());
  bond.tag = strictBondKind(context->bondKind());
  return bond;
}

//Parse an angle from a species
antlrcpp::Any
MyVisitor::visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context) {
  Angle angle;
  angle.a = std::stoi(context->INT(0)->getText());
  angle.b = std::stoi(context->INT(1)->getText());
  angle.c = std::stoi(context->INT(2)->getText());
  angle.tag = strictBondKind(context->bondKind());
  return angle;
}

//Parse a torsion from a species
antlrcpp::Any
MyVisitor::visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context) {
  Torsion torsion;
  torsion.a = std::stoi(context->INT(0)->getText());
  torsion.b = std::stoi(context->INT(1)->getText());
  torsion.c = std::stoi(context->INT(2)->getText());
  torsion.d = std::stoi(context->INT(3)->getText());
  torsion.tag = strictBondKind(context->bondKind());
  return torsion;
}

//parse an isotopologue in a species
antlrcpp::Any MyVisitor::visitSpeciesIsotopologue(
    DissolveParser::SpeciesIsotopologueContext *context) {
  Isotopologue iso;
  iso.name = context->name->getText();
  for (auto kind : context->ISO()) {
    iso.kind.push_back(kind->getText());
  }
  return iso;
}

//parse a site in a species.
//
//By convention, the xaxis and yaxis are zero when the site isn't mass
//weighted.
antlrcpp::Any
MyVisitor::visitSpeciesSite(DissolveParser::SpeciesSiteContext *context) {
  Site result;
  result.name = context->name->getText();
  result.origins = visit(context->siteOrigin()).as<std::vector<int>>();
  result.massWeighted = false;
  result.xaxis = 0;
  result.yaxis = 0;

  if (context->siteOriginMassWeighted() != nullptr) {
    result.massWeighted = visit(context->siteOriginMassWeighted()).as<bool>();
    result.xaxis = visit(context->siteXAxis()).as<int>();
    result.yaxis = visit(context->siteYAxis()).as<int>();
  }
  // result.origins = visit(context->siteOrigin());
  // for (auto ctx : context->siteTerm()) {
  //   SiteTerm term = visit(ctx)
  // }
  return result;
}

//Parse an XAxis in a Site
antlrcpp::Any
MyVisitor::visitSiteXAxis(DissolveParser::SiteXAxisContext *context) {
  return std::stoi(context->INT()->getText());
}

//Parse an YAxis in a Site
antlrcpp::Any
MyVisitor::visitSiteYAxis(DissolveParser::SiteYAxisContext *context) {
  return std::stoi(context->INT()->getText());
}

//Parse the Origins of a site
antlrcpp::Any
MyVisitor::visitSiteOrigin(DissolveParser::SiteOriginContext *context) {
  std::vector<int> result;
  for (auto ctx : context->INT()) {
    result.push_back(std::stoi(ctx->getText()));
  }
  return result;
}

// Parse a bond term, which is currently either Harmonic or Cos3
BondKind MyVisitor::strictBondKind(DissolveParser::BondKindContext *context) {
  if (context->REF()) {
    return references_[context->getText()];
  }
  if (context->vec3()) {
    Cos3 b;
    b.vec = visit(context->vec3());
    return b;
  } else {
    Harmonic b;
    b.i = visit(context->num(0));
    b.j = visit(context->num(1));
    return b;
  }
}

// Parse a forcefield from a species
antlrcpp::Any MyVisitor::visitSpeciesForcefield(
    DissolveParser::SpeciesForcefieldContext *context) {
  Forcefield result;
  result.name = context->name->getText();
  return result;
}
