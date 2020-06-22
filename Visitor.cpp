#include "Visitor.h"
#include <iostream>

antlrcpp::Any MyVisitor::visitProgram(DissolveParser::ProgramContext *context) {
  std::cout << "Program" << std::endl;
  return false;
}


antlrcpp::Any MyVisitor::visitSection(DissolveParser::SectionContext *context) {}

antlrcpp::Any MyVisitor::visitMaster(DissolveParser::MasterContext *context) {}

antlrcpp::Any MyVisitor::visitMasterTerm(DissolveParser::MasterTermContext *context) {}

antlrcpp::Any MyVisitor::visitMasterBond(DissolveParser::MasterBondContext *context) {}

antlrcpp::Any MyVisitor::visitMasterAngle(DissolveParser::MasterAngleContext *context) {}

antlrcpp::Any MyVisitor::visitMasterTorsion(DissolveParser::MasterTorsionContext *context) {}

antlrcpp::Any MyVisitor::visitSpecies(DissolveParser::SpeciesContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesTerm(DissolveParser::SpeciesTermContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesAtom(DissolveParser::SpeciesAtomContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesBond(DissolveParser::SpeciesBondContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesIsotopologue(DissolveParser::SpeciesIsotopologueContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesSite(DissolveParser::SpeciesSiteContext *context) {}

antlrcpp::Any MyVisitor::visitSpeciesForcefield(DissolveParser::SpeciesForcefieldContext *context) {}

antlrcpp::Any MyVisitor::visitBondKind(DissolveParser::BondKindContext *context) {}

antlrcpp::Any MyVisitor::visitTorsionKind(DissolveParser::TorsionKindContext *context) {}

antlrcpp::Any MyVisitor::visitSiteTerm(DissolveParser::SiteTermContext *context) {}

antlrcpp::Any MyVisitor::visitSiteOrigin(DissolveParser::SiteOriginContext *context) {}

antlrcpp::Any MyVisitor::visitSiteOriginMassWeighted(DissolveParser::SiteOriginMassWeightedContext *context) {}

antlrcpp::Any MyVisitor::visitSiteXAxis(DissolveParser::SiteXAxisContext *context) {}

antlrcpp::Any MyVisitor::visitSiteYAxis(DissolveParser::SiteYAxisContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotential(DissolveParser::PairPotentialContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialTerm(DissolveParser::PairPotentialTermContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialsParameters(DissolveParser::PairPotentialsParametersContext *context) {}

antlrcpp::Any MyVisitor::visitPp(DissolveParser::PpContext *context) {}

antlrcpp::Any MyVisitor::visitLj(DissolveParser::LjContext *context) {}

antlrcpp::Any MyVisitor::visitLjGeometric(DissolveParser::LjGeometricContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialsRange(DissolveParser::PairPotentialsRangeContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialsDelta(DissolveParser::PairPotentialsDeltaContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialsIncludeCoulomb(DissolveParser::PairPotentialsIncludeCoulombContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialsCoulombTruncation(DissolveParser::PairPotentialsCoulombTruncationContext *context) {}

antlrcpp::Any MyVisitor::visitPairPotentialsShortRangeTruncation(DissolveParser::PairPotentialsShortRangeTruncationContext *context) {}

antlrcpp::Any MyVisitor::visitTruncation(DissolveParser::TruncationContext *context) {}

antlrcpp::Any MyVisitor::visitConfiguration(DissolveParser::ConfigurationContext *context) {}

antlrcpp::Any MyVisitor::visitConfigurationTerm(DissolveParser::ConfigurationTermContext *context) {}

antlrcpp::Any MyVisitor::visitConfigurationTemperature(DissolveParser::ConfigurationTemperatureContext *context) {}

antlrcpp::Any MyVisitor::visitConfigurationGenerator(DissolveParser::ConfigurationGeneratorContext *context) {}

antlrcpp::Any MyVisitor::visitGeneratorTerm(DissolveParser::GeneratorTermContext *context) {}

antlrcpp::Any MyVisitor::visitGeneratorParameter(DissolveParser::GeneratorParameterContext *context) {}

antlrcpp::Any MyVisitor::visitParameterTerm(DissolveParser::ParameterTermContext *context) {}

antlrcpp::Any MyVisitor::visitGeneratorBox(DissolveParser::GeneratorBoxContext *context) {}

antlrcpp::Any MyVisitor::visitBoxTerm(DissolveParser::BoxTermContext *context) {}

antlrcpp::Any MyVisitor::visitBoxLength(DissolveParser::BoxLengthContext *context) {}

antlrcpp::Any MyVisitor::visitBoxAngles(DissolveParser::BoxAnglesContext *context) {}

antlrcpp::Any MyVisitor::visitBoxNonPeriodic(DissolveParser::BoxNonPeriodicContext *context) {}

antlrcpp::Any MyVisitor::visitGeneratorAddSpecies(DissolveParser::GeneratorAddSpeciesContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesTerm(DissolveParser::AddSpeciesTermContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesSpecies(DissolveParser::AddSpeciesSpeciesContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesPopulation(DissolveParser::AddSpeciesPopulationContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesDensity(DissolveParser::AddSpeciesDensityContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesRotate(DissolveParser::AddSpeciesRotateContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesPositioning(DissolveParser::AddSpeciesPositioningContext *context) {}

antlrcpp::Any MyVisitor::visitAddSpeciesBoxAction(DissolveParser::AddSpeciesBoxActionContext *context) {}

antlrcpp::Any MyVisitor::visitBoxAction(DissolveParser::BoxActionContext *context) {}

antlrcpp::Any MyVisitor::visitLayer(DissolveParser::LayerContext *context) {}

antlrcpp::Any MyVisitor::visitFrequency(DissolveParser::FrequencyContext *context) {}

antlrcpp::Any MyVisitor::visitConfigName(DissolveParser::ConfigNameContext *context) {}

antlrcpp::Any MyVisitor::visitModule(DissolveParser::ModuleContext *context) {}

antlrcpp::Any MyVisitor::visitModuleTerm(DissolveParser::ModuleTermContext *context) {}

antlrcpp::Any MyVisitor::visitMolShake(DissolveParser::MolShakeContext *context) {}

antlrcpp::Any MyVisitor::visitRotationStepSize(DissolveParser::RotationStepSizeContext *context) {}

antlrcpp::Any MyVisitor::visitTranslationStepSize(DissolveParser::TranslationStepSizeContext *context) {}

antlrcpp::Any MyVisitor::visitMD(DissolveParser::MDContext *context) {}

antlrcpp::Any MyVisitor::visitEnergy(DissolveParser::EnergyContext *context) {}

antlrcpp::Any MyVisitor::visitRDF(DissolveParser::RDFContext *context) {}

antlrcpp::Any MyVisitor::visitIntraBroadening(DissolveParser::IntraBroadeningContext *context) {}

antlrcpp::Any MyVisitor::visitNeutronSQ(DissolveParser::NeutronSQContext *context) {}

antlrcpp::Any MyVisitor::visitQbroadening(DissolveParser::QbroadeningContext *context) {}

antlrcpp::Any MyVisitor::visitExchangeable(DissolveParser::ExchangeableContext *context) {}

antlrcpp::Any MyVisitor::visitIsotopologue(DissolveParser::IsotopologueContext *context) {}

antlrcpp::Any MyVisitor::visitReference(DissolveParser::ReferenceContext *context) {}

antlrcpp::Any MyVisitor::visitEPSR(DissolveParser::EPSRContext *context) {}

antlrcpp::Any MyVisitor::visitEreq(DissolveParser::EreqContext *context) {}

antlrcpp::Any MyVisitor::visitTarget(DissolveParser::TargetContext *context) {}

antlrcpp::Any MyVisitor::visitCalculateRDF(DissolveParser::CalculateRDFContext *context) {}

antlrcpp::Any MyVisitor::visitSite(DissolveParser::SiteContext *context) {}

antlrcpp::Any MyVisitor::visitCalculateCN(DissolveParser::CalculateCNContext *context) {}

antlrcpp::Any MyVisitor::visitSourceRDF(DissolveParser::SourceRDFContext *context) {}

antlrcpp::Any MyVisitor::visitRange(DissolveParser::RangeContext *context) {}

antlrcpp::Any MyVisitor::visitCalculateDAngle(DissolveParser::CalculateDAngleContext *context) {}

antlrcpp::Any MyVisitor::visitExcludeSameMolecule(DissolveParser::ExcludeSameMoleculeContext *context) {}

antlrcpp::Any MyVisitor::visitDistanceRange(DissolveParser::DistanceRangeContext *context) {}

antlrcpp::Any MyVisitor::visitCalculateAvgMol(DissolveParser::CalculateAvgMolContext *context) {}

antlrcpp::Any MyVisitor::visitCalculateSDF(DissolveParser::CalculateSDFContext *context) {}

antlrcpp::Any MyVisitor::visitBenchmark(DissolveParser::BenchmarkContext *context) {}

antlrcpp::Any MyVisitor::visitSimulation(DissolveParser::SimulationContext *context) {}

antlrcpp::Any MyVisitor::visitStr(DissolveParser::StrContext *context) {}

antlrcpp::Any MyVisitor::visitNum(DissolveParser::NumContext *context) {}

antlrcpp::Any MyVisitor::visitBoolean(DissolveParser::BooleanContext *context) {}

antlrcpp::Any MyVisitor::visitTruthy(DissolveParser::TruthyContext *context) {}

antlrcpp::Any MyVisitor::visitFalsy(DissolveParser::FalsyContext *context) {}
