{-# LANGUAGE OverloadedStrings #-}

-- import           Control.Applicative
import qualified Data.Text as T
import qualified Data.Text.IO as T
import Data.Void
import Text.Megaparsec
import Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer as L

type Parser = Parsec Void T.Text

data MasterTerm = MasterBond T.Text T.Text Double Double
  | MasterAngle T.Text T.Text Double Double
  deriving (Show)

data Section = Master [MasterTerm] | Species T.Text [SpeciesTerm]
  deriving (Show)

data SpeciesTerm =
  Atom Int T.Text Double Double Double T.Text Double
  | SpeciesBond Int Int T.Text
  | SpeciesAngle Int Int Int T.Text
  | SpeciesIsotopologue T.Text T.Text
  | SpeciesSite
  deriving (Show)

sc = L.space space1 (L.skipLineComment "#") empty

symbol = L.symbol sc
lexeme = L.lexeme sc

constant :: Parser Double
constant = lexeme $ L.signed sc L.float

word :: Parser T.Text
word = T.pack <$> (some $ letterChar <|> char '-')

parser :: Parser [Section]
parser = some . choice $ [
  Master <$> parseBlock "Master" masterTerm
  , uncurry Species <$> parseNamedBlock "Species" speciesTerm
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
  title <- quoted word
  result <- some inner
  symbol $ "End" <> name
  return (title, result)

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
                     ]

quoted :: Parser p -> Parser p
quoted p = lexeme $ "'" *> p <* "'"

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

main = do
  info <- readFile "water.txt"
  parseTest parser $ T.pack info
