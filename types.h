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

// using Atom = int;
using Bond = std::tuple<int, int>;
using NullTerm = std::tuple<double, double>;
using SpeciesTerm = std::variant<Bond, NullTerm>;

class Species {
public:
  Species(std::string name, std::vector<Atom> atoms, std::vector<Bond> bonds) : name_(name), atoms_(atoms), bonds_(bonds) {}
  std::string name_;
  std::vector<Atom> atoms_;
  std::vector<Bond> bonds_;
  friend std::ostream& operator<<(std::ostream& out, const Species& s) {
    out << "Species " << s.name_ << std::endl;
    for (auto atom : s.atoms_) {out << atom << std::endl;}
    for (auto bond : s.bonds_) {out << "Bond " << std::get<0>(bond) << " " << std::get<1>(bond) << std::endl;}
    return out;
  }
};
