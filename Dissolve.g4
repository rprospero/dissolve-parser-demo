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
    | simulation
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
	   | masterTorsion
	   ;


masterBond : 'Bond' str bondKind ;

masterAngle : 'Angle' str bondKind ;

masterTorsion : 'Torsion' str torsionKind ;

// Species Terms
species :
       'Species'
       str
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
    | speciesForcefield
    ;

speciesAtom : 'Atom' INT str Num Num Num str Num;
speciesBond : 'Bond' INT INT bondKind;
speciesAngle : 'Angle' INT INT INT bondKind;
speciesTorsion : 'Torsion' INT INT INT INT torsionKind;
speciesIsotopologue : 'Isotopologue' str str;
speciesSite : 'Site' str siteTerm+ 'EndSite' ;
speciesForcefield : 'Forcefield' str ;

bondKind : 'Harmonic' Num Num | REF ;
torsionKind : REF | 'Cos3' Num Num Num ;


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

pairPotentialsParameters : 'Parameters' str str Num pp ;

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
        str
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

parameterTerm : 'Real' str Num;

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

addSpeciesSpecies : 'Species' str ;
addSpeciesPopulation : 'Population' INT ;
addSpeciesDensity : 'Density' str str ;
addSpeciesRotate : 'Rotate' boolean ;
addSpeciesPositioning : 'Positioning' str ;

// Layer Terms

layer : 'Layer'
        QUOTE
        frequency
        module+
        'EndLayer'
    ;

frequency : 'Frequency' INT ;
configName : 'Configuration' str ;

module : 'Module' moduleTerm 'EndModule' ;

moduleTerm : molShake | mD | energy | rDF | neutronSQ | ePSR | calculateRDF
	   | calculateCN | calculateDAngle | calculateAvgMol | calculateSDF
	   | benchmark;

molShake : 'MolShake' str frequency configName rotationStepSize translationStepSize ;
rotationStepSize : 'RotationStepSize' Num ;
translationStepSize : 'TranslationStepSize' Num ;

mD : 'MD' str frequency configName ;
energy : 'Energy' str frequency configName ;

rDF : 'RDF' str frequency configName intraBroadening Num ;
intraBroadening : 'IntraBroadening' str ;

neutronSQ : 'NeutronSQ' str frequency configName qbroadening exchangeable? isotopologue+ reference ;
qbroadening : 'QBroadening' str Num ;
exchangeable : 'Exchangeable' str ;
isotopologue : 'Isotopologue' str str str Num ;
reference : 'Reference' str str 'EndReference' ;


ePSR : 'EPSR' str frequency ereq target+;
ereq : 'EReq' Num ;
target : 'Target' str str;

calculateRDF : 'CalculateRDF' str frequency configName site+ excludeSameMolecule ;
site : ('SiteA' | 'SiteB' | 'SiteC' | 'Site') str str+ ;

calculateCN : 'CalculateCN' str frequency sourceRDF range ;
sourceRDF : 'SourceRDF' str ;
range : ('RangeA' | 'RangeB') Num Num ;

calculateDAngle : 'CalculateDAngle' str frequency configName distanceRange site+ excludeSameMolecule ;
excludeSameMolecule : 'ExcludeSameMolecule' boolean ;
distanceRange : 'DistanceRange' Num Num Num ;

calculateAvgMol : 'CalculateAvgMol' str frequency configName site ;
calculateSDF: 'CalculateSDF' str frequency configName site+ ;
benchmark: 'Benchmark' str configName ;

// Simulation Terms

simulation : 'Simulation' 'Seed' INT 'EndSimulation' ;


// Lexer Terms

COMMENT: '#' ~('\r' | '\n')* -> skip ;

Space:  [ \t\r\n]+ -> skip;


fragment SIGNED : ('-'|'+')?;

fragment DIGITS : [0-9]+;

fragment EXPONENT: ('e' | 'E') SIGNED DIGITS ;

Num : SIGNED DIGITS '.' (DIGITS (EXPONENT)? )?;

INT: SIGNED DIGITS ;

QUOTE: '\''~('\'')+'\'';

REF: '@' WORD;

WORD: ~(' ' | '\r' | '\n')+ ;

str : REF | QUOTE | WORD ;

boolean : 'True' | 'False' ;

