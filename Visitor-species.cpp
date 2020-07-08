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

// Parse an Atom from a species
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

// Parse a bond from a species
antlrcpp::Any
MyVisitor::visitSpeciesBond(DissolveParser::SpeciesBondContext *context) {
  return Bond{std::stoi(context->left->getText()),
	      std::stoi(context->right->getText()),
	      strictBondKind(context->bondKind())};
}

// Parse an angle from a species
antlrcpp::Any
MyVisitor::visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context) {
  return Angle{std::stoi(context->INT(0)->getText()),
	       std::stoi(context->INT(1)->getText()),
	       std::stoi(context->INT(2)->getText()),
	       strictBondKind(context->bondKind())};
}

// Parse a torsion from a species
antlrcpp::Any
MyVisitor::visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context) {
  return Torsion{
      std::stoi(context->INT(0)->getText()),
      std::stoi(context->INT(1)->getText()),
      std::stoi(context->INT(2)->getText()),
      std::stoi(context->INT(3)->getText()),
      strictBondKind(context->bondKind()),
  };
}

// parse an isotopologue in a species
antlrcpp::Any MyVisitor::visitSpeciesIsotopologue(
    DissolveParser::SpeciesIsotopologueContext *context) {
  Isotopologue iso;
  iso.name = context->name->getText();
  for (auto kind : context->ISO()) {
    iso.kind.push_back(kind->getText());
  }
  return iso;
}

// parse a site in a species.
//
// By convention, the xaxis and yaxis are zero when the site isn't mass
// weighted.
antlrcpp::Any
MyVisitor::visitSpeciesSite(DissolveParser::SpeciesSiteContext *context) {
  if (context->siteOriginMassWeighted() != nullptr) {
    return Site{context->name->getText(),
		visit(context->siteOrigin()).as<std::vector<int>>(),
		visit(context->siteOriginMassWeighted()).as<bool>(),
		visit(context->siteXAxis()).as<int>(),
		visit(context->siteYAxis()).as<int>()};
  } else {
    return Site{context->name->getText(),
		visit(context->siteOrigin()).as<std::vector<int>>()};
  }
}

// Parse an XAxis in a Site
antlrcpp::Any
MyVisitor::visitSiteXAxis(DissolveParser::SiteXAxisContext *context) {
  return std::stoi(context->INT()->getText());
}

// Parse an YAxis in a Site
antlrcpp::Any
MyVisitor::visitSiteYAxis(DissolveParser::SiteYAxisContext *context) {
  return std::stoi(context->INT()->getText());
}

// Parse the Origins of a site
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
    return Cos3{visit(context->vec3())};
  } else {
    return Harmonic{visit(context->num(0)), visit(context->num(1))};
  }
}

// Parse a forcefield from a species
antlrcpp::Any MyVisitor::visitSpeciesForcefield(
    DissolveParser::SpeciesForcefieldContext *context) {
  return Forcefield{context->name->getText()};
}
