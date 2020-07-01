#include "DissolveBaseVisitor.h"

class MyVisitor : public DissolveBaseVisitor {
public:
  antlrcpp::Any visitSpecies(DissolveParser::SpeciesContext *context) override;

  antlrcpp::Any visitSpeciesAtom(DissolveParser::SpeciesAtomContext *context) override;

  antlrcpp::Any visitSpeciesBond(DissolveParser::SpeciesBondContext *context) override;

  antlrcpp::Any visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context) override;

  antlrcpp::Any visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context) override;

  antlrcpp::Any visitSpeciesIsotopologue(DissolveParser::SpeciesIsotopologueContext *context) override;

  antlrcpp::Any visitSpeciesSite(DissolveParser::SpeciesSiteContext *context) override;

  antlrcpp::Any visitSpeciesForcefield(DissolveParser::SpeciesForcefieldContext *context) override;

  antlrcpp::Any visitBondKind(DissolveParser::BondKindContext *context) override;

  antlrcpp::Any visitSiteOriginMassWeighted(DissolveParser::SiteOriginMassWeightedContext *context) override;

  antlrcpp::Any visitStr(DissolveParser::StrContext *context) override;

  antlrcpp::Any visitBoolean(DissolveParser::BooleanContext *context) override;

  antlrcpp::Any visitVec3(DissolveParser::Vec3Context *context) override;

  antlrcpp::Any visitNum(DissolveParser::NumContext *context) override;
};
