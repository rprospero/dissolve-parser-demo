{pkgs ? import <nixpkgs> {} }:

let
  all-hies = import (fetchTarball "https://github.com/infinisil/all-hies/tarball/master") {};

in

pkgs.mkShell {
  buildInputs = [
    (pkgs.haskell.packages.ghc882.ghcWithPackages (pkgs: [pkgs.Cabal pkgs.hlint pkgs.megaparsec]))
    # (all-hies.selection { selector = p: { inherit (p) ghc882; }; })
  ];
}
