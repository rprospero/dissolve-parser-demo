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
       name=str
       speciesAtom+
       speciesBond*
       speciesAngle*
       speciesTorsion*
       speciesIsotopologue*
       speciesTerm*
       'EndSpecies'
       ;

speciesTerm :
    speciesSite
    | speciesForcefield
    ;

speciesAtom : 'Atom' index=INT element=str vec3 atomtype=str charge=num?;
speciesBond : 'Bond' left=INT right=INT bondKind;
speciesAngle : 'Angle' INT INT INT bondKind;
speciesTorsion : 'Torsion' INT INT INT INT torsionKind;
speciesIsotopologue : 'Isotopologue' name=str kinds=str*;

speciesSite : 'Site' str siteTerm+ 'EndSite' ;
speciesForcefield : 'Forcefield' str ;

bondKind : 'Harmonic' num num | REF ;
torsionKind : REF | 'Cos3' vec3 ;


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

pairPotentialsParameters : 'Parameters' str str num pp ;

pp : ljGeometric | lj ;
lj : 'LJ' num+ ;
ljGeometric : 'LJGeometric' num+ ;

pairPotentialsRange : 'Range' num;
pairPotentialsDelta : 'Delta' num;
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

configurationTemperature : 'Temperature' num;

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

parameterTerm : 'Real' str num;

generatorBox :
        'Box'
        boxTerm+
        'EndBox'
    ;

boxTerm : boxLength | boxAngles | boxNonPeriodic ;

boxLength : 'Lengths' vec3 ;
boxAngles : 'Angles' vec3 ;
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
  | addSpeciesBoxAction
    ;

addSpeciesSpecies : 'Species' str ;
addSpeciesPopulation : 'Population' INT ;
addSpeciesDensity : 'Density' (num | str) str ;
addSpeciesRotate : 'Rotate' boolean ;
addSpeciesPositioning : 'Positioning' str ;
addSpeciesBoxAction : 'BoxAction' boxAction ;

boxAction : 'None' | 'ScaleVolume' ;

// Layer Terms

layer : 'Layer'
        QUOTE
        frequency?
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
rotationStepSize : 'RotationStepSize' num ;
translationStepSize : 'TranslationStepSize' num ;

mD : 'MD' str frequency configName ;
energy : 'Energy' str frequency configName ;

rDF : 'RDF' str frequency configName intraBroadening num ;
intraBroadening : 'IntraBroadening' str ;

neutronSQ : 'NeutronSQ' str frequency configName qbroadening exchangeable? isotopologue+ reference ;
qbroadening : 'QBroadening' str num ;
exchangeable : 'Exchangeable' str ;
isotopologue : 'Isotopologue' str str str num ;
reference : 'Reference' str str 'EndReference' ;


ePSR : 'EPSR' str frequency ereq target+;
ereq : 'EReq' num ;
target : 'Target' str str;

calculateRDF : 'CalculateRDF' str frequency configName site+ excludeSameMolecule ;
site : ('SiteA' | 'SiteB' | 'SiteC' | 'Site') str str+ ;

calculateCN : 'CalculateCN' str frequency sourceRDF range ;
sourceRDF : 'SourceRDF' str ;
range : ('RangeA' | 'RangeB') num num ;

calculateDAngle : 'CalculateDAngle' str frequency configName distanceRange site+ excludeSameMolecule ;
excludeSameMolecule : 'ExcludeSameMolecule' boolean ;
distanceRange : 'DistanceRange' vec3 ;

calculateAvgMol : 'CalculateAvgMol' str frequency configName site ;
calculateSDF: 'CalculateSDF' str frequency configName site+ ;
benchmark: 'Benchmark' str? configName ;

// Simulation Terms

simulation : 'Simulation' 'Seed' INT 'EndSimulation' ;


// Lexer Terms

COMMENT: '#' ~('\r' | '\n')* -> skip ;

Space:  [ \t\r\n]+ -> skip;


fragment SIGNED : ('-'|'+')?;

fragment DIGITS : [0-9]+;

fragment EXPONENT: ('e' | 'E') SIGNED DIGITS ;

Num : SIGNED DIGITS '.' (DIGITS (EXPONENT)? )?;

INT: '\'' SIGNED DIGITS '\'' | SIGNED DIGITS ;

QUOTE: '\''~('\'')+'\'';

REF: '@' WORD;

WORD: ~(' ' | '\r' | '\n')+ ;

str : REF | QUOTE | WORD ;
num : Num | INT ;
vec3 : x=num y=num z=num ;

boolean : truthy | falsy ;
truthy : 'True' | 'On' ;
falsy : 'False' | 'Off' ;

