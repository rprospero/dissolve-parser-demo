// Basic Parser

grammar Dissolve;

options {
  language=Cpp;
  }

program :
	section+
	;

section :
	master
    | species
    | pairPotential
    | configuration
    | layer
	;

// Master Section
master :
       'Master'
       masterTerm+
       'EndMaster'
       ;

masterTerm :
	   masterBond
	   | masterAngle
	   ;


masterBond :
	   'Bond'
	   WORD
	   WORD
	   Num
	   Num
	   ;

masterAngle :
	    'Angle'
	    WORD
	    WORD
	    Num
	    Num
	    ;

// Species Terms
species :
       'Species'
       WORD
       speciesTerm+
       'EndSpecies'
       ;

speciesTerm :
        speciesAtom
    | speciesBond
    | speciesAngle
    | speciesTorsion
    | speciesIsotopologue
    | speciesSite
    ;

speciesAtom : 'Atom' INT WORD Num Num Num WORD Num;
speciesBond : 'Bond' INT INT WORD;
speciesAngle : 'Angle' INT INT INT WORD;
speciesTorsion : 'Torsion' INT INT INT INT WORD;
speciesIsotopologue : 'Isotopologue' WORD WORD;
speciesSite : 'Site' WORD siteTerm+ 'EndSite' ;


siteTerm : siteOriginMassWeighted
    | siteOrigin
    | siteXAxis
    | siteYAxis
    ;

siteOrigin : 'Origin' INT+ ;
siteOriginMassWeighted : 'OriginMassWeighted' boolean ;
siteXAxis : 'XAxis' INT ;
siteYAxis : 'YAxis' INT ;

// Pair Potential Terms

pairPotential :
        'PairPotentials'
        pairPotentialTerm+
        'EndPairPotentials'
    ;

pairPotentialTerm :
  pairPotentialsParameters
  | pairPotentialsRange
  | pairPotentialsDelta
  | pairPotentialsIncludeCoulomb
  | pairPotentialsCoulombTruncation
  | pairPotentialsShortRangeTruncation
    ;

pairPotentialsParameters : 'Parameters' WORD WORD Num pp ;

pp : ljGeometric | lj ;
lj : 'LJ' Num+ ;
ljGeometric : 'LJGeometric' Num+ ;

pairPotentialsRange : 'Range' Num;
pairPotentialsDelta : 'Delta' Num;
pairPotentialsIncludeCoulomb : 'IncludeCoulomb' boolean;
pairPotentialsCoulombTruncation : 'CoulombTruncation' truncation;
pairPotentialsShortRangeTruncation : 'ShortRangeTruncation' truncation;

truncation : 'Shifted' ;

// Configuration Section
configuration :
       'Configuration'
        WORD
       configurationTerm+
       'EndConfiguration'
       ;

configurationTerm :
    configurationGenerator
    | configurationTemperature
    ;

configurationTemperature : 'Temperature' Num;

configurationGenerator :
        'Generator'
        generatorTerm+
        'EndGenerator'
    ;

generatorTerm : generatorParameter | generatorBox | generatorAddSpecies ;

generatorParameter :
        'Parameters'
        parameterTerm+
        'EndParameters'
    ;

parameterTerm : 'Real' WORD Num;

generatorBox :
        'Box'
        boxTerm+
        'EndBox'
    ;

boxTerm : boxLength | boxAngles | boxNonPeriodic ;

boxLength : 'Lengths' Num Num Num ;
boxAngles : 'Angles' Num Num Num ;
boxNonPeriodic : 'NonPeriodic' boolean ;

generatorAddSpecies :
        'AddSpecies'
        addSpeciesTerm+
        'EndAddSpecies'
    ;

addSpeciesTerm :
  addSpeciesSpecies
  | addSpeciesPopulation
  | addSpeciesDensity
  | addSpeciesRotate
  | addSpeciesPositioning
    ;

addSpeciesSpecies : 'Species' WORD ;
addSpeciesPopulation : 'Population' WORD ;
addSpeciesDensity : 'Density' WORD WORD ;
addSpeciesRotate : 'Rotate' boolean ;
addSpeciesPositioning : 'Positioning' WORD ;

// Layer Terms

layer : 'Layer'
        QUOTE
        frequency
        module+
        'EndLayer'
    ;

frequency : 'Frequency' INT ;
configName : 'Configuration' WORD ;

module : 'Module' moduleTerm 'EndModule' ;

moduleTerm : molShake | mD | energy | rDF | neutronSQ | ePSR | calculateRDF | calculateCN | calculateDAngle | calculateAvgMol | calculateSDF ;

molShake : 'MolShake' WORD frequency configName rotationStepSize translationStepSize ;
rotationStepSize : 'RotationStepSize' Num ;
translationStepSize : 'TranslationStepSize' Num ;

mD : 'MD' WORD frequency configName ;
energy : 'Energy' WORD frequency configName ;

rDF : 'RDF' WORD frequency configName intraBroadening Num ;
intraBroadening : 'IntraBroadening' WORD ;

neutronSQ : 'NeutronSQ' WORD frequency configName qbroadening exchangeable? isotopologue+ reference ;
qbroadening : 'QBroadening' WORD Num ;
exchangeable : 'Exchangeable' WORD ;
isotopologue : 'Isotopologue' WORD WORD WORD Num ;
reference : 'Reference' WORD WORD 'EndReference' ;


ePSR : 'EPSR' WORD frequency ereq target+;
ereq : 'EReq' Num ;
target : 'Target' WORD WORD;

calculateRDF : 'CalculateRDF' WORD frequency configName site+ excludeSameMolecule ;
site : ('SiteA' | 'SiteB' | 'SiteC' | 'Site') WORD WORD+ ;

calculateCN : 'CalculateCN' WORD frequency sourceRDF range ;
sourceRDF : 'SourceRDF' WORD ;
range : ('RangeA' | 'RangeB') Num Num ;

calculateDAngle : 'CalculateDAngle' WORD frequency configName distanceRange site+ excludeSameMolecule ;
excludeSameMolecule : 'ExcludeSameMolecule' boolean ;
distanceRange : 'DistanceRange' Num Num Num ;

calculateAvgMol : 'CalculateAvgMol' WORD frequency configName site ;
calculateSDF: 'CalculateSDF' WORD frequency configName site+ ;


// Lexer Terms

INT: [0-9]+ ;

fragment DIGIT : [0-9] ;

WORD: ~(' ' | '\r' | '\n')+ ;

Space:  (' ' | '\t' | '\r' | '\n')+ -> skip;

Comment: '#'('-'*)~[\r\n]* -> skip ;

boolean : 'True' | 'False' ;

Num : DIGIT+ ('.' DIGIT+)? ;

QUOTE: '\''~('\'')+'\'';
