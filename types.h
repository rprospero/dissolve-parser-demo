#include <iostream>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

using BondKind = std::string;

struct Vec3 {
  double x, y, z;
  friend std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
    out << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
    return out;
  }
};

struct Atom {
  int index;
  Vec3 position;
  std::string element, type;
  std::optional<double> charge;
  friend std::ostream& operator<<(std::ostream& out, const Atom& atom) {
    out << "Atom " << atom.element << " " << atom.index << " " << atom.position << " " << atom.type;
    if (atom.charge) out << " " << *atom.charge;
    return out;
  }
};

struct Bond {
  int i, j;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Bond& bond) {
    out << "Bond " << bond.tag << " "<< bond.i << " " << bond.j;
    return out;
  }
};

struct Angle {
  int a, b, c;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Angle& angle) {
    out << "Angle " << angle.tag << " " << angle.a << " " << angle.b << " " << angle.c;
    return out;
  }
};

struct Torsion {
  int a, b, c, d;
  BondKind tag;
  friend std::ostream& operator<<(std::ostream& out, const Torsion& torsion) {
    out << "Torsion " << torsion.tag << " " << torsion.a << " " << torsion.b << " " << torsion.c << " " << torsion.d;
    return out;
  }
};

struct Isotopologue {
  std::string name;
  std::vector<std::string> kind;
  friend std::ostream& operator<<(std::ostream& out, const Isotopologue& isotopologue) {
    out << "Isotopologue " << isotopologue.name;
    for (auto k : isotopologue.kind)
      out << " " << k;
    return out;
  }
};

struct Site {
  std::string name;
  std::vector<int> origins;
  bool massWeighted;
  int xaxis;
  int yaxis;
  friend std::ostream& operator<<(std::ostream& out, const Site& site) {
    out << "Site " << site.name;
    out << " Origin";
    for (auto org : site.origins) out << " " << org;
    out << " Mass Weighted " << site.massWeighted;
    out << " xaxis " << site.xaxis;
    out << " yaxis " << site.yaxis;
    return out;
  }
};

struct Forcefield {
  std::string name;
  friend std::ostream& operator<<(std::ostream& out, const Forcefield& forcefield) {
    out << "Forcefield" << forcefield.name;
    return out;
  }
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
  friend std::ostream& operator<<(std::ostream& out, const Species& s) {
    out << "Species " << s.name_ << std::endl;
    for (auto atom : s.atoms_) {out << atom << std::endl;}
    for (auto bond : s.bonds_) {out << bond << std::endl;}
    for (auto angle : s.angles_) {out << angle << std::endl;}
    for (auto torsion : s.torsions_) {out << torsion << std::endl;}
    for (auto isotopologue : s.isotopologues_) {out << isotopologue << std::endl;}
    for (auto site : s.sites_) {out << site << std::endl;}
    for (auto forcefield : s.forcefields_) {out << forcefield << std::endl;}
    return out;
  }
};
