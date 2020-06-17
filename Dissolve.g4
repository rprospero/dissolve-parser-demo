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


// Lexer Terms

INT: [0-9]+ ;

fragment DIGIT : [0-9] ;

WORD: ~(' ' | '\r' | '\n')+ ;

Space:  (' ' | '\t' | '\r' | '\n')+ -> skip;

Comment: '#'('-'*)~[\r\n]* -> skip ;

boolean : 'True' | 'False' ;

Num : DIGIT+ ('.' DIGIT+)? ;
