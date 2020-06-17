{pkgs ? import <nixpkgs> {} }:

let
  all-hies = import (fetchTarball "https://github.com/infinisil/all-hies/tarball/master") {};

in

pkgs.mkShell {
  buildInputs = [
    pkgs.antlr4
    (pkgs.antlr4.runtime.cpp)
    (pkgs.antlr4.runtime.cpp.dev)
   (pkgs.haskell.packages.ghc882.ghcWithPackages (pkgs: [pkgs.Cabal pkgs.hlint pkgs.megaparsec pkgs.parser-combinators]))
    # (all-hies.selection { selector = p: { inherit (p) ghc882; }; })
  ];
}
