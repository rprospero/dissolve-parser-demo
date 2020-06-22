#include "DissolveBaseVisitor.h"

class MyVisitor : public DissolveBaseVisitor {
public:
  antlrcpp::Any visitProgram(DissolveParser::ProgramContext *context) override;

  antlrcpp::Any visitSection(DissolveParser::SectionContext *context) override;

  antlrcpp::Any visitSiteOriginMassWeighted(DissolveParser::SiteOriginMassWeightedContext *context) override;

  antlrcpp::Any visitBoolean(DissolveParser::BooleanContext *context) override;
};
