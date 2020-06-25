#include <iostream>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

using Atom = int;
using Bond = std::tuple<int, int>;
using NullTerm = bool;

class Species {
public:
  Species(std::string name, std::vector<Atom> atoms, std::vector<Bond> bonds) : name_(name), atoms_(atoms), bonds_(bonds) {}
  std::string name_;
  std::vector<Atom> atoms_;
  std::vector<Bond> bonds_;
  friend std::ostream& operator<<(std::ostream& out, const Species& s) {
    out << "Species " << s.name_ << std::endl;
    for (auto atom : s.atoms_) {out << " Atom " << atom << std::endl;}
    for (auto bond : s.bonds_) {out << " Bond " << std::get<0>(bond) << " " << std::get<1>(bond) << std::endl;}
  }
};

using SpeciesTerm = std::variant<Atom, Bond, NullTerm>;