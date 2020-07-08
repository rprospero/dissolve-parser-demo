#include "Visitor.h"
#include "types.h"
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

// Parse a single species and print it out
antlrcpp::Any MyVisitor::visitSpecies(DissolveParser::SpeciesContext *context) {
  return Species{visit(context->name),
		 visitVector<Atom>(context->speciesAtom()),
		 visitVector<Bond>(context->speciesBond()),
		 visitVector<Angle>(context->speciesAngle()),
		 visitVector<Torsion>(context->speciesTorsion()),
		 visitVector<Isotopologue>(context->speciesIsotopologue()),
		 visitVector<Site>(context->speciesSite()),
		 visitVector<Forcefield>(context->speciesForcefield())};
}

// Parse an Atom from a species
antlrcpp::Any
MyVisitor::visitSpeciesAtom(DissolveParser::SpeciesAtomContext *context) {
  return Atom{std::stoi(context->index->getText()), visit(context->vec3()),
	      visit(context->element), visit(context->atomtype),
	      visitOptional<double>(context->charge)};
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
  return Isotopologue{context->name->getText(),
		      visitVector<std::string>(context->ISO(), [](auto kind) {
			return kind->getText();
		      })};
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
  return visitVector<int>(context->INT(),
			  [](auto &ctx) { return std::stoi(ctx->getText()); });
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
