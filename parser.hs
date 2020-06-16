{-# LANGUAGE OverloadedStrings #-}

import qualified Data.Text as T
import qualified Data.Text.IO as T
import Data.Void
import Text.Megaparsec
import Text.Megaparsec.Char
import Text.Megaparsec.Debug
import qualified Text.Megaparsec.Char.Lexer as L

type Parser = Parsec Void T.Text

data Section = Master [MasterTerm]
  | Species T.Text [SpeciesTerm]
  | PairPotential [PairPotentialTerm]
  | Configuration T.Text [ConfigurationTerm]
  | Layer T.Text Int [Module]
  | Simulation Int
  deriving (Show)

data MasterTerm = MasterBond T.Text T.Text Double Double
  | MasterAngle T.Text T.Text Double Double
  deriving (Show)

data SpeciesTerm =
  Atom Int T.Text Double Double Double T.Text Double
  | SpeciesBond Int Int T.Text
  | SpeciesAngle Int Int Int T.Text
  | SpeciesIsotopologue T.Text T.Text
  | SpeciesSite T.Text [SiteTerm]
  deriving (Show)

data SiteTerm =
  SiteOrigin [Int]
  | SiteOriginMassWeighted Bool
  | SiteXAxis Int
  | SiteYAxis Int
  deriving (Show)

data PairPotentialTerm =
  PairPotentialsParameters T.Text T.Text Double T.Text Double Double Double Double
  | PairPotentialsRange Double
  | PairPotentialsDelta Double
  | PairPotentialsCoulombTruncation Truncation
  | PairPotentialsShortRangeTruncation Truncation
  deriving (Show)

data Truncation = Shifted
  deriving (Show)

data ConfigurationTerm =
  ConfigurationGenerator [GeneratorTerm]
  | ConfigurationTemperature Double
  deriving (Show)

data GeneratorTerm =
  GeneratorParameter [ParameterTerm]
  | GeneratorBox [BoxTerm]
  | GeneratorAddSpecies [AddSpeciesTerm]
  deriving (Show)

data ParameterTerm = ParameterReal T.Text Double
  deriving (Show)

data BoxTerm = BoxLength Double Double Double
  | BoxAngles Double Double Double
  | BoxNonPeriodic Bool
  deriving (Show)

data AddSpeciesTerm = AddSpeciesSpecies T.Text
  | AddSpeciesPopulation T.Text
  | AddSpeciesDensity T.Text T.Text
  | AddSpeciesRotate Bool
  | AddSpeciesPositioning T.Text
  deriving (Show)

data Module = Module T.Text Int ModuleTerm
  deriving (Show)

data ModuleTerm = MolShake T.Text Double Double
  | MD T.Text
  | Energy T.Text
  | RDF T.Text T.Text Double
  | NeutronSQ T.Text QBroadening (Maybe Exchangeable) [Isotopologue] Reference
  | EPSR Double [Target]
  | CalculateRDF T.Text [Site] Bool
  | CalculateCN T.Text Range
  | CalculateDAngle T.Text DistanceRange [Site] Bool
  | CalculateAvgMol T.Text Site
  | CalculateSDF T.Text [Site]
  deriving (Show)

data QBroadening = QBroadening T.Text Double
  deriving Show
data Exchangeable = Exchangeable T.Text
  deriving Show
data Isotopologue = Isotopologue T.Text T.Text T.Text Double
  deriving Show
data Reference = Reference T.Text T.Text
  deriving Show
data Target = Target T.Text T.Text
  deriving Show
data Site = Site T.Text [T.Text]
  deriving Show
data Range = Range T.Text Double Double
  deriving Show
data DistanceRange = DistanceRange Double Double Double
  deriving Show


sc = L.space space1 (L.skipLineComment "#") empty

symbol = L.symbol sc
lexeme = L.lexeme sc

constant :: Parser Double
constant = lexeme $ L.signed sc L.float

word :: Parser T.Text
word = T.pack <$> (some $ letterChar <|> char '-')

printable :: Parser T.Text
printable = T.pack <$> (some $ alphaNumChar <|> symbolChar <|> punctuationChar)

printableWithSpace :: Parser T.Text
printableWithSpace = T.pack <$> (some $ alphaNumChar <|> symbolChar <|> punctuationChar <|> char ' ')

quotable :: Parser T.Text
quotable = T.pack <$> ("'" *> someTill printChar "'")

parser :: Parser [Section]
parser = some . choice $ [
  Master <$> parseBlock "Master" (some masterTerm)
  , uncurry Species <$> parseNamedBlock "Species" (some speciesTerm)
  , PairPotential <$> parseBlock "PairPotentials" (some pairPotentialTerm)
  , uncurry Configuration <$> parseNamedBlock "Configuration" (some configurationTerm)
  , layer
  , Simulation <$> parseBlock "Simulation" (symbol "Seed" *> lexeme (L.signed sc L.decimal))
  ]

parseBlock :: T.Text -> Parser a -> Parser a
parseBlock name inner= do
  sc
  symbol name
  result <- inner
  symbol $ "End" <> name
  return result

parseNamedBlock :: T.Text -> Parser a -> Parser (T.Text, a)
parseNamedBlock name inner= do
  sc
  symbol name
  title <- quoted . lexeme . some $ alphaNumChar
  result <- inner
  symbol $ "End" <> name
  return (T.pack title, result)

parseBool :: Parser Bool
parseBool = true <|> false
  where
    true = symbol "True" *> return True
    false = symbol "False" *> return False

parseInt :: Parser Int
parseInt = lexeme L.decimal

masterTerm :: Parser MasterTerm
masterTerm = choice [masterBond, masterAngle]

masterBond = do
  symbol "Bond"
  MasterBond <$> quoted word <*> lexeme word <*> constant <*> constant

masterAngle = do
  symbol "Angle"
  MasterAngle <$> quoted word <*> lexeme word <*> constant <*> constant

speciesTerm :: Parser SpeciesTerm
speciesTerm = choice [speciesAtom
                     , speciesBond
                     , speciesAngle
                     , speciesIsotopologue
                     , speciesSite
                     ]

quoted :: Parser p -> Parser p
quoted p = lexeme $ between "'" "'" p

speciesAtom :: Parser SpeciesTerm
speciesAtom = do
  symbol "Atom"
  Atom <$> lexeme L.decimal <*> lexeme word <*> constant <*> constant <*> constant <*> quoted word <*> constant

speciesBond :: Parser SpeciesTerm
speciesBond = do
  symbol "Bond"
  SpeciesBond <$> lexeme L.decimal <*> lexeme L.decimal <*> lexeme ("@" *> word)

speciesAngle :: Parser SpeciesTerm
speciesAngle = do
  symbol "Angle"
  SpeciesAngle <$> lexeme L.decimal <*> lexeme L.decimal <*> lexeme L.decimal <*> lexeme ("@" *> word)

speciesIsotopologue :: Parser SpeciesTerm
speciesIsotopologue = do
  symbol "Isotopologue"
  SpeciesIsotopologue <$> quoted word <*> label
  where
    label = do
      first <- word
      char '='
      second <- L.decimal
      sc
      return $ first <> "=" <> T.pack (show second)

speciesSite = do
  (name, terms) <- parseNamedBlock "Site" (some siteTerm)
  return $ SpeciesSite name terms

siteTerm :: Parser SiteTerm
siteTerm = choice [
  siteOriginMassWeighted
  , siteOrigin
  , siteXAxis
  , siteYAxis
  ]

siteOrigin :: Parser SiteTerm
siteOrigin = do
  symbol "Origin"
  SiteOrigin <$> (lexeme L.decimal `sepBy` sc)

siteOriginMassWeighted :: Parser SiteTerm
siteOriginMassWeighted = do
  symbol "OriginMassWeighted"
  SiteOriginMassWeighted <$> parseBool

siteXAxis :: Parser SiteTerm
siteXAxis = do
  symbol "XAxis"
  SiteXAxis <$> parseInt

siteYAxis :: Parser SiteTerm
siteYAxis = do
  symbol "YAxis"
  SiteYAxis <$> parseInt

pairPotentialTerm :: Parser PairPotentialTerm
pairPotentialTerm = choice [
  pairPotentialsParameters
  , pairPotentialsRange
  , pairPotentialsDelta
  , pairPotentialsCoulombTruncation
  , pairPotentialsShortRangeTruncation
  ]

pairPotentialsParameters :: Parser PairPotentialTerm
pairPotentialsParameters = do
  symbol "Parameters"
  PairPotentialsParameters <$> lexeme word <*> lexeme word <*> constant <*> lexeme word <*> constant <*> constant <*> constant <*> constant

pairPotentialsRange :: Parser PairPotentialTerm
pairPotentialsRange = do
  symbol "Range"
  PairPotentialsRange <$> constant

pairPotentialsDelta :: Parser PairPotentialTerm
pairPotentialsDelta = do
  symbol "Delta"
  PairPotentialsDelta <$> constant

pairPotentialsCoulombTruncation :: Parser PairPotentialTerm
pairPotentialsCoulombTruncation = do
  symbol "CoulombTruncation"
  PairPotentialsCoulombTruncation <$> truncation

pairPotentialsShortRangeTruncation :: Parser PairPotentialTerm
pairPotentialsShortRangeTruncation = do
  symbol "ShortRangeTruncation"
  PairPotentialsShortRangeTruncation <$> truncation

truncation = do
  lexeme "Shifted"
  return Shifted

configurationTerm = choice [
  configurationGenerator
  , configurationTemperature
  ]

configurationTemperature = do
  symbol "Temperature"
  ConfigurationTemperature <$> constant

configurationGenerator = ConfigurationGenerator <$> parseBlock "Generator" (some generatorTerm)

generatorTerm = choice [
  generatorParameter
  , generatorBox
  , generatorAddSpecies
  ]

generatorParameter = GeneratorParameter <$> parseBlock "Parameters" (some parameterTerm)

parameterTerm = do
  symbol "Real"
  ParameterReal <$> lexeme word <*> constant

generatorBox = GeneratorBox <$> parseBlock "Box" (some boxTerm)

boxTerm = choice [boxLength, boxAngles, boxNonPeriodic]

boxLength = do
  symbol "Lengths"
  BoxLength <$> constant <*> constant <*> constant

boxAngles = do
  symbol "Angles"
  BoxAngles <$> constant <*> constant <*> constant

boxNonPeriodic = do
  symbol "NonPeriodic"
  BoxNonPeriodic <$> parseBool

generatorAddSpecies = GeneratorAddSpecies <$> parseBlock "AddSpecies" (some addSpeciesTerm)

addSpeciesTerm = choice [
  addSpeciesSpecies
  , addSpeciesPopulation
  , addSpeciesDensity
  , addSpeciesRotate
  , addSpeciesPositioning
  ]

addSpeciesSpecies = do
  symbol "Species"
  AddSpeciesSpecies <$> quoted word

addSpeciesPopulation = do
  symbol "Population"
  AddSpeciesPopulation . T.pack<$> quoted (some alphaNumChar)

addSpeciesDensity = do
  symbol "Density"
  AddSpeciesDensity <$> quoted word <*> lexeme printable

addSpeciesRotate = do
  symbol "Rotate"
  AddSpeciesRotate <$> parseBool

addSpeciesPositioning = do
  symbol "Positioning"
  AddSpeciesPositioning <$> lexeme word

layer :: Parser Section
layer = between (symbol "Layer") (symbol "EndLayer") $
  Layer <$> lexeme quotable <*> frequency <*> some module_

module_ :: Parser Module
module_ = between (symbol "Module") (symbol "EndModule") . choice . zipWith parseModule moduleNames $ modules

moduleNames = ["MolShake", "MD", "Energy", "RDF", "NeutronSQ", "EPSR", "CalculateRDF", "CalculateCN", "CalculateDAngle", "CalculateAvgMol", "CalculateSDF"]
modules = [molshake, md, energy, rdf, neutronsq, epsr, calculateRDF, calculateCN, calculateDAngle, calculateAvgMol, calculateSDF]

parseModule :: T.Text -> Parser ModuleTerm -> Parser Module
parseModule mname parser = symbol mname *> (Module <$> lexeme quotable <*> frequency <*> parser)

frequency :: Parser Int
frequency = symbol "Frequency" *> parseInt

configuration :: Parser T.Text
configuration = symbol "Configuration" *> lexeme quotable

molshake = do
  MolShake <$> configuration <*> rotationStepSize <*>  translationStepSize

rotationStepSize = symbol "RotationStepSize" *> constant
translationStepSize = symbol "TranslationStepSize" *> constant

md = do
  MD <$> configuration

energy = do
  Energy <$> configuration

rdf = (RDF <$> configuration <*> (symbol "IntraBroadening" *> lexeme word) <*> constant)

neutronsq = do
  NeutronSQ <$> configuration <*> qbroadening <*> optional exchangeable <*> some isotopologue <*> reference

qbroadening = do
  symbol "QBroadening"
  QBroadening <$> lexeme quotable <*> constant
exchangeable = symbol "Exchangeable" *> (Exchangeable <$> lexeme word)
isotopologue = do
  symbol "Isotopologue"
  Isotopologue <$> lexeme quotable <*> lexeme quotable <*> lexeme quotable <*> constant
reference = do
  symbol "Reference" *> (Reference <$> lexeme word <*> lexeme quotable) <* symbol "EndReference"

epsr = EPSR <$> (symbol "EReq" *> constant) <*> some target

target = symbol "Target" *> (Target <$> lexeme quotable <*> lexeme quotable)

calculateRDF = (CalculateRDF <$> configuration <*> some site <*> (symbol "ExcludeSameMolecule" *> parseBool))

site = symbol "Site" *> (Site <$> (T.pack <$> lexeme (many upperChar)) <*> some (lexeme quotable))

calculateCN = (CalculateCN <$> (symbol "SourceRDF" *> lexeme quotable) <*> range)

range = symbol "Range" *> (Range <$> (T.pack <$> lexeme (many upperChar)) <*> constant <*> constant)

calculateDAngle = (CalculateDAngle <$> configuration <*> distanceRange <*> some site <*> (symbol "ExcludeSameMolecule" *> parseBool))

distanceRange = symbol "DistanceRange" *> (DistanceRange <$> constant <*> constant <*> constant)

calculateAvgMol = (CalculateAvgMol <$> configuration <*> site)

calculateSDF = (CalculateSDF <$> configuration <*> some site)

main = do
  info <- readFile "water.txt"
  parseTest parser $ T.pack info
