#include <iostream>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

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
  friend std::ostream& operator<<(std::ostream& out, const Bond& bond) {
    out << "Bond " << bond.i << " " << bond.j;
    return out;
  }
};

struct Angle {
  int a, b, c;
  friend std::ostream& operator<<(std::ostream& out, const Angle& angle) {
    out << "Angle " << angle.a << " " << angle.b << " " << angle.c;
    return out;
  }
};

// using Atom = int;
using NullTerm = std::tuple<double, double>;
using SpeciesTerm = std::variant<Bond, Angle, NullTerm>;

class Species {
public:
  Species(std::string name, std::vector<Atom> atoms, std::vector<Bond> bonds, std::vector<Angle> angles) : name_(name), atoms_(atoms), bonds_(bonds), angles_(angles) {}
  std::string name_;
  std::vector<Atom> atoms_;
  std::vector<Bond> bonds_;
  std::vector<Angle> angles_;
  friend std::ostream& operator<<(std::ostream& out, const Species& s) {
    out << "Species " << s.name_ << std::endl;
    for (auto atom : s.atoms_) {out << atom << std::endl;}
    for (auto bond : s.bonds_) {out << bond << std::endl;}
    for (auto angle : s.angles_) {out << angle << std::endl;}
    return out;
  }
};
