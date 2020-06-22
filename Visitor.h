#include "DissolveVisitor.h"

class MyVisitor : public DissolveVisitor {
public:
    antlrcpp::Any visitProgram(DissolveParser::ProgramContext *context);

    antlrcpp::Any visitSection(DissolveParser::SectionContext *context);

    antlrcpp::Any visitMaster(DissolveParser::MasterContext *context);

    antlrcpp::Any visitMasterTerm(DissolveParser::MasterTermContext *context);

    antlrcpp::Any visitMasterBond(DissolveParser::MasterBondContext *context);

    antlrcpp::Any visitMasterAngle(DissolveParser::MasterAngleContext *context);

    antlrcpp::Any visitMasterTorsion(DissolveParser::MasterTorsionContext *context);

    antlrcpp::Any visitSpecies(DissolveParser::SpeciesContext *context);

    antlrcpp::Any visitSpeciesTerm(DissolveParser::SpeciesTermContext *context);

    antlrcpp::Any visitSpeciesAtom(DissolveParser::SpeciesAtomContext *context);

    antlrcpp::Any visitSpeciesBond(DissolveParser::SpeciesBondContext *context);

    antlrcpp::Any visitSpeciesAngle(DissolveParser::SpeciesAngleContext *context);

    antlrcpp::Any visitSpeciesTorsion(DissolveParser::SpeciesTorsionContext *context);

    antlrcpp::Any visitSpeciesIsotopologue(DissolveParser::SpeciesIsotopologueContext *context);

    antlrcpp::Any visitSpeciesSite(DissolveParser::SpeciesSiteContext *context);

    antlrcpp::Any visitSpeciesForcefield(DissolveParser::SpeciesForcefieldContext *context);

    antlrcpp::Any visitBondKind(DissolveParser::BondKindContext *context);

    antlrcpp::Any visitTorsionKind(DissolveParser::TorsionKindContext *context);

    antlrcpp::Any visitSiteTerm(DissolveParser::SiteTermContext *context);

    antlrcpp::Any visitSiteOrigin(DissolveParser::SiteOriginContext *context);

    antlrcpp::Any visitSiteOriginMassWeighted(DissolveParser::SiteOriginMassWeightedContext *context);

    antlrcpp::Any visitSiteXAxis(DissolveParser::SiteXAxisContext *context);

    antlrcpp::Any visitSiteYAxis(DissolveParser::SiteYAxisContext *context);

    antlrcpp::Any visitPairPotential(DissolveParser::PairPotentialContext *context);

    antlrcpp::Any visitPairPotentialTerm(DissolveParser::PairPotentialTermContext *context);

    antlrcpp::Any visitPairPotentialsParameters(DissolveParser::PairPotentialsParametersContext *context);

    antlrcpp::Any visitPp(DissolveParser::PpContext *context);

    antlrcpp::Any visitLj(DissolveParser::LjContext *context);

    antlrcpp::Any visitLjGeometric(DissolveParser::LjGeometricContext *context);

    antlrcpp::Any visitPairPotentialsRange(DissolveParser::PairPotentialsRangeContext *context);

    antlrcpp::Any visitPairPotentialsDelta(DissolveParser::PairPotentialsDeltaContext *context);

    antlrcpp::Any visitPairPotentialsIncludeCoulomb(DissolveParser::PairPotentialsIncludeCoulombContext *context);

    antlrcpp::Any visitPairPotentialsCoulombTruncation(DissolveParser::PairPotentialsCoulombTruncationContext *context);

    antlrcpp::Any visitPairPotentialsShortRangeTruncation(DissolveParser::PairPotentialsShortRangeTruncationContext *context);

    antlrcpp::Any visitTruncation(DissolveParser::TruncationContext *context);

    antlrcpp::Any visitConfiguration(DissolveParser::ConfigurationContext *context);

    antlrcpp::Any visitConfigurationTerm(DissolveParser::ConfigurationTermContext *context);

    antlrcpp::Any visitConfigurationTemperature(DissolveParser::ConfigurationTemperatureContext *context);

    antlrcpp::Any visitConfigurationGenerator(DissolveParser::ConfigurationGeneratorContext *context);

    antlrcpp::Any visitGeneratorTerm(DissolveParser::GeneratorTermContext *context);

    antlrcpp::Any visitGeneratorParameter(DissolveParser::GeneratorParameterContext *context);

    antlrcpp::Any visitParameterTerm(DissolveParser::ParameterTermContext *context);

    antlrcpp::Any visitGeneratorBox(DissolveParser::GeneratorBoxContext *context);

    antlrcpp::Any visitBoxTerm(DissolveParser::BoxTermContext *context);

    antlrcpp::Any visitBoxLength(DissolveParser::BoxLengthContext *context);

    antlrcpp::Any visitBoxAngles(DissolveParser::BoxAnglesContext *context);

    antlrcpp::Any visitBoxNonPeriodic(DissolveParser::BoxNonPeriodicContext *context);

    antlrcpp::Any visitGeneratorAddSpecies(DissolveParser::GeneratorAddSpeciesContext *context);

    antlrcpp::Any visitAddSpeciesTerm(DissolveParser::AddSpeciesTermContext *context);

    antlrcpp::Any visitAddSpeciesSpecies(DissolveParser::AddSpeciesSpeciesContext *context);

    antlrcpp::Any visitAddSpeciesPopulation(DissolveParser::AddSpeciesPopulationContext *context);

    antlrcpp::Any visitAddSpeciesDensity(DissolveParser::AddSpeciesDensityContext *context);

    antlrcpp::Any visitAddSpeciesRotate(DissolveParser::AddSpeciesRotateContext *context);

    antlrcpp::Any visitAddSpeciesPositioning(DissolveParser::AddSpeciesPositioningContext *context);

    antlrcpp::Any visitAddSpeciesBoxAction(DissolveParser::AddSpeciesBoxActionContext *context);

    antlrcpp::Any visitBoxAction(DissolveParser::BoxActionContext *context);

    antlrcpp::Any visitLayer(DissolveParser::LayerContext *context);

    antlrcpp::Any visitFrequency(DissolveParser::FrequencyContext *context);

    antlrcpp::Any visitConfigName(DissolveParser::ConfigNameContext *context);

    antlrcpp::Any visitModule(DissolveParser::ModuleContext *context);

    antlrcpp::Any visitModuleTerm(DissolveParser::ModuleTermContext *context);

    antlrcpp::Any visitMolShake(DissolveParser::MolShakeContext *context);

    antlrcpp::Any visitRotationStepSize(DissolveParser::RotationStepSizeContext *context);

    antlrcpp::Any visitTranslationStepSize(DissolveParser::TranslationStepSizeContext *context);

    antlrcpp::Any visitMD(DissolveParser::MDContext *context);

    antlrcpp::Any visitEnergy(DissolveParser::EnergyContext *context);

    antlrcpp::Any visitRDF(DissolveParser::RDFContext *context);

    antlrcpp::Any visitIntraBroadening(DissolveParser::IntraBroadeningContext *context);

    antlrcpp::Any visitNeutronSQ(DissolveParser::NeutronSQContext *context);

    antlrcpp::Any visitQbroadening(DissolveParser::QbroadeningContext *context);

    antlrcpp::Any visitExchangeable(DissolveParser::ExchangeableContext *context);

    antlrcpp::Any visitIsotopologue(DissolveParser::IsotopologueContext *context);

    antlrcpp::Any visitReference(DissolveParser::ReferenceContext *context);

    antlrcpp::Any visitEPSR(DissolveParser::EPSRContext *context);

    antlrcpp::Any visitEreq(DissolveParser::EreqContext *context);

    antlrcpp::Any visitTarget(DissolveParser::TargetContext *context);

    antlrcpp::Any visitCalculateRDF(DissolveParser::CalculateRDFContext *context);

    antlrcpp::Any visitSite(DissolveParser::SiteContext *context);

    antlrcpp::Any visitCalculateCN(DissolveParser::CalculateCNContext *context);

    antlrcpp::Any visitSourceRDF(DissolveParser::SourceRDFContext *context);

    antlrcpp::Any visitRange(DissolveParser::RangeContext *context);

    antlrcpp::Any visitCalculateDAngle(DissolveParser::CalculateDAngleContext *context);

    antlrcpp::Any visitExcludeSameMolecule(DissolveParser::ExcludeSameMoleculeContext *context);

    antlrcpp::Any visitDistanceRange(DissolveParser::DistanceRangeContext *context);

    antlrcpp::Any visitCalculateAvgMol(DissolveParser::CalculateAvgMolContext *context);

    antlrcpp::Any visitCalculateSDF(DissolveParser::CalculateSDFContext *context);

    antlrcpp::Any visitBenchmark(DissolveParser::BenchmarkContext *context);

    antlrcpp::Any visitSimulation(DissolveParser::SimulationContext *context);

    antlrcpp::Any visitStr(DissolveParser::StrContext *context);

    antlrcpp::Any visitNum(DissolveParser::NumContext *context);

    antlrcpp::Any visitBoolean(DissolveParser::BooleanContext *context);

    antlrcpp::Any visitTruthy(DissolveParser::TruthyContext *context);

    antlrcpp::Any visitFalsy(DissolveParser::FalsyContext *context);
};
