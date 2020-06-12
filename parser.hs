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

sc = L.space space1 (L.skipLineComment "#") empty

symbol = L.symbol sc
lexeme = L.lexeme sc

constant :: Parser Double
constant = lexeme L.float

word :: Parser T.Text
word = T.pack <$> (some $ letterChar <|> char '-')

parser :: Parser [MasterTerm]
parser = parseBlock "Master" masterTerm

parseBlock :: T.Text -> Parser a -> Parser [a]
parseBlock name inner= do
  sc
  symbol name
  result <- some inner
  symbol $ "End" <> name
  return result

masterTerm :: Parser MasterTerm
masterTerm = choice [masterBond, masterAngle]

masterBond = do
  symbol "Bond"
  MasterBond <$> (lexeme $ "'" *> word <* "'") <*> lexeme word <*> constant <*> constant

masterAngle = do
  symbol "Angle"
  MasterAngle <$> (lexeme $ "'" *> word <* "'") <*> lexeme word <*> constant <*> constant

main = do
  info <- readFile "water.txt"
  parseTest parser $ T.pack info
