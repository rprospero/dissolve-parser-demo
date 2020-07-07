#pragma once

#include "DissolveBaseVisitor.h"
#include "types.h"
#include <map>

class MyVisitor : public DissolveBaseVisitor {
private:
  std::map<std::string, BondKind> references_;

public:
  //The main parser
  antlrcpp::Any
  visitProgram(DissolveParser::ProgramContext *context) override;

  // The parsers for master terms

  antlrcpp::Any
  visitMasterAngle(DissolveParser::MasterAngleContext *context) override;

  antlrcpp::Any
  visitMasterBond(DissolveParser::MasterBondContext *context) override;

  antlrcpp::Any
  visitMasterTorsion(DissolveParser::MasterTorsionContext *context) override;

  //The parsers for species terms

  antlrcpp::Any visitSpecies(DissolveParser::SpeciesContext *context) override;

  antlrcpp::Any
  visitSpeciesAtom(DissolveParser::SpeciesAtomContext *context) override;

  antlrcpp::Any
  visitSpeciesBond(DissolveParser::SpeciesBondContext *context) override;

  antlrcpp::Any
  visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context) override;

  antlrcpp::Any
  visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context) override;

  antlrcpp::Any visitSpeciesIsotopologue(
      DissolveParser::SpeciesIsotopologueContext *context) override;

  antlrcpp::Any
  visitSpeciesSite(DissolveParser::SpeciesSiteContext *context) override;

  antlrcpp::Any visitSpeciesForcefield(
      DissolveParser::SpeciesForcefieldContext *context) override;

  BondKind
  strictBondKind(DissolveParser::BondKindContext *context);

  //The parsers for Site components
  antlrcpp::Any
  visitSiteOrigin(DissolveParser::SiteOriginContext *context) override;

  antlrcpp::Any
  visitSiteXAxis(DissolveParser::SiteXAxisContext *context) override;

  antlrcpp::Any
  visitSiteYAxis(DissolveParser::SiteYAxisContext *context) override;

  //The parsers for pair potential terms

  antlrcpp::Any visitPp(DissolveParser::PpContext *context) override;

  antlrcpp::Any visitPairPotential(DissolveParser::PairPotentialContext *context) override;

  antlrcpp::Any visitPairPotentialsParameters(DissolveParser::PairPotentialsParametersContext *context) override;


  //The parsers for low level types
  antlrcpp::Any visitStr(DissolveParser::StrContext *context) override;

  antlrcpp::Any visitBoolean(DissolveParser::BooleanContext *context) override;

  antlrcpp::Any visitVec3(DissolveParser::Vec3Context *context) override;

  antlrcpp::Any visitNum(DissolveParser::NumContext *context) override;
};
