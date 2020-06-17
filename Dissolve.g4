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

// Lexer Terms

INT: [0-9]+ ;

fragment DIGIT : [0-9] ;

WORD: ~(' ' | '\r' | '\n')+ ;

Space:  (' ' | '\t' | '\r' | '\n')+ -> skip;

Comment: '#'('-'*)~[\r\n]* -> skip ;

boolean : 'True' | 'False' ;

Num : DIGIT+ ('.' DIGIT+)? ;
