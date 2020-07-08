/*
  This file contains all of the types that we intend to parse out of
  the file.  In the actual dissolve, these types are already defined
  for us, so much of this wouldn't have to exist.  However, some of
  this is also meant to show how some of those classes might be
  simplified.
 */
#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <variant>
#include <vector>

// This class defines a three-vector of doubles
struct Vec3 {
  double x, y, z;
  friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
};


/*
  We use a variant to represent the different types of bond definition
  that we can have.  Since we're not using pointers, we can't just use
  inheritance, since the compiler needs to know the amount of space to
  allocate.
 */
struct Harmonic {
  double i, j;
  friend std::ostream& operator<<(std::ostream& out, const Harmonic& bond);
};

struct Cos3 {
  Vec3 vec;
  friend std::ostream& operator<<(std::ostream& out, const Cos3& bond);
};

using BondKind = std::variant<Harmonic, Cos3>;

// Since BondKind isn't a real class, we need to declare the <<
// operator separately.
std::ostream& operator<<(std::ostream& out, const BondKind& bond);

// The class for a single atom in Dissolve
struct Atom {
  int index;
  Vec3 position;
  std::string element, type;
  std::optional<double> charge;
  friend std::ostream& operator<<(std::ostream& out, const Atom& atom);
};

// The class for the bond between two atoms
struct Bond {
  int i, j;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Bond& bond);
};

// The class for the angle between three atoms
struct Angle {
  int a, b, c;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Angle& angle);
};

// The class for the torsion across four atoms.
struct Torsion {
  int a, b, c, d;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Torsion& torsion);
};

// A collectiong of Isotopologues.  We may need to parse and define these a bit better
struct Isotopologue {
  std::string name;
  std::vector<std::string> kind;
  friend std::ostream& operator<<(std::ostream& out, const Isotopologue& isotopologue);
};

// The location of a site within a species.  We may want to split this
// into two classes, one which is mass weighted and one which isn't.
struct Site {
  std::string name;
  std::vector<int> origins;
  bool massWeighted;
  int xaxis;
  int yaxis;
  friend std::ostream& operator<<(std::ostream& out, const Site& site);
};

// Which forcefield to use for a species
struct Forcefield {
  std::string name;
  friend std::ostream& operator<<(std::ostream& out, const Forcefield& forcefield);
};

// A single species within the simulation
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

class PP {
public:
  enum PPType {LJ, LJGeometric};
  PP(PPType type, std::vector<double> params) : params_(params), type_(type) {}
  friend std::ostream& operator<<(std::ostream& out, const PP& p);
private:
  PPType type_;
  std::vector<double> params_;
};


// The Pair Potential terms
class PairPotentialParameters {
public:
  PairPotentialParameters(std::string name, std::string element, double strength, PP type) : name_(name), element_(element), strength_(strength), type_(type) {};
  friend std::ostream& operator<<(std::ostream& out, const PairPotentialParameters& p);
private:
  std::string name_, element_;
  double strength_;
  PP type_;
};

class PairPotential {
public:
  PairPotential(std::vector<PairPotentialParameters> params, double range, double delta, bool includeCoulomb) : params_(params), range_(range), delta_(delta), includeCoulomb_(includeCoulomb) {};
  friend std::ostream& operator<<(std::ostream& out, const PairPotential& s);
private:
  std::vector<PairPotentialParameters> params_;
  double range_, delta_;
  bool includeCoulomb_;
};

//The full program specified in the file
class Program {
public:
  Program(std::vector<Species> species, PairPotential pairPotential) : species_(species), pairPotential_(pairPotential) {}
  friend std::ostream& operator<<(std::ostream& out, const Program& p);
private:
  std::vector<Species> species_;
  PairPotential pairPotential_;
};
