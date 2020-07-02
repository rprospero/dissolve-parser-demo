#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <variant>
#include <vector>

struct Vec3 {
  double x, y, z;
  friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
};

struct BondKind {
  enum BondType { Harmonic, Cos3 };
  BondType type;
  Vec3 vec;
  friend std::ostream& operator<<(std::ostream& out, const BondKind& bond);
};

struct Atom {
  int index;
  Vec3 position;
  std::string element, type;
  std::optional<double> charge;
  friend std::ostream& operator<<(std::ostream& out, const Atom& atom);
};

struct Bond {
  int i, j;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Bond& bond);
};

struct Angle {
  int a, b, c;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Angle& angle);
};

struct Torsion {
  int a, b, c, d;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Torsion& torsion);
};

struct Isotopologue {
  std::string name;
  std::vector<std::string> kind;
  friend std::ostream& operator<<(std::ostream& out, const Isotopologue& isotopologue);
};

struct Site {
  std::string name;
  std::vector<int> origins;
  bool massWeighted;
  int xaxis;
  int yaxis;
  friend std::ostream& operator<<(std::ostream& out, const Site& site);
};

struct Forcefield {
  std::string name;
  friend std::ostream& operator<<(std::ostream& out, const Forcefield& forcefield);
};

// using Atom = int;
using NullTerm = std::tuple<double, double>;
using SpeciesTerm = std::variant<Bond, Angle, NullTerm>;

class Species {
public:
  Species(std::string name, std::vector<Atom> atoms, std::vector<Bond> bonds, std::vector<Angle> angles, std::vector<Torsion> torsions, std::vector<Isotopologue> isos, std::vector<Site> sites, std::vector<Forcefield> forcefields) : name_(name), atoms_(atoms), bonds_(bonds), angles_(angles), torsions_(torsions), isotopologues_(isos), sites_(sites), forcefields_(forcefields) {}
  std::string name_;
  std::vector<Atom> atoms_;
  std::vector<Bond> bonds_;
  std::vector<Angle> angles_;
  std::vector<Torsion> torsions_;
  std::vector<Isotopologue> isotopologues_;
  std::vector<Site> sites_;
  std::vector<Forcefield> forcefields_;
  friend std::ostream& operator<<(std::ostream& out, const Species& s);
};
