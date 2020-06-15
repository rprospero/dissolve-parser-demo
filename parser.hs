{-# LANGUAGE OverloadedStrings #-}

import qualified Data.Text as T
import qualified Data.Text.IO as T
import Data.Void
import Text.Megaparsec
import Text.Megaparsec.Char
import Text.Megaparsec.Debug
import qualified Text.Megaparsec.Char.Lexer as L

type Parser = Parsec Void T.Text

data MasterTerm = MasterBond T.Text T.Text Double Double
  | MasterAngle T.Text T.Text Double Double
  deriving (Show)

data Section = Master [MasterTerm]
  | Species T.Text [SpeciesTerm]
  | PairPotential [PairPotentialTerm]
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

sc = L.space space1 (L.skipLineComment "#") empty

symbol = L.symbol sc
lexeme = L.lexeme sc

constant :: Parser Double
constant = lexeme $ L.signed sc L.float

word :: Parser T.Text
word = T.pack <$> (some $ letterChar <|> char '-')

printable :: Parser T.Text
printable = T.pack <$> (some $ alphaNumChar <|> symbolChar <|> punctuationChar)

parser :: Parser [Section]
parser = some . choice $ [
  Master <$> parseBlock "Master" masterTerm
  , uncurry Species <$> parseNamedBlock "Species" speciesTerm
  , PairPotential <$> parseBlock "PairPotentials" pairPotentialTerm
  ]

parseBlock :: T.Text -> Parser a -> Parser [a]
parseBlock name inner= do
  sc
  symbol name
  result <- some inner
  symbol $ "End" <> name
  return result

parseNamedBlock :: T.Text -> Parser a -> Parser (T.Text, [a])
parseNamedBlock name inner= do
  sc
  symbol name
  title <- quoted . lexeme . some $ alphaNumChar
  result <- some inner
  symbol $ "End" <> name
  return (T.pack title, result)

parseBool :: Parser Bool
parseBool = true <|> false
  where
    true = symbol "True" *> return True
    false = symbol "True" *> return False

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
  (name, terms) <- parseNamedBlock "Site" siteTerm
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

main = do
  info <- readFile "water.txt"
  parseTest parser $ T.pack info
