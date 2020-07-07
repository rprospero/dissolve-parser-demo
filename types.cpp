/*
  This file contains the implementations of the << operator for all of
  the datatypes included in types.h.  This file exists both to save a
  bit on compiling time and as a poor, lazy way to force the makefile
  to recompile when I add new types to types.h.

  There's probably a better way of doing that, but this is just the
  prototype and all of this would be handled through cmake in the
  actual dissolve, anyway.

  Minor point of pride - There's currently only a single if statement
  in this whole file.
*/
#include "types.h"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const Vec3 &vec) {
  return out << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
}

std::ostream &operator<<(std::ostream &out, const Cos3 &bond) {
  return out << "Cos3 " << bond.vec;
}

std::ostream &operator<<(std::ostream &out, const Harmonic &bond) {
  return out << "Harmonic " << bond.i << " " << bond.j;
}

std::ostream &operator<<(std::ostream &out, const BondKind &bond) {
  std::visit([&out](auto &&value) { out << value; }, bond);
  return out;
}

std::ostream &operator<<(std::ostream &out, const Atom &atom) {
  out << "Atom " << atom.element << " " << atom.index << " " << atom.position
      << " " << atom.type;
  if (atom.charge)
    out << " " << *atom.charge;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Bond &bond) {
  return out << "Bond " << bond.i << " " << bond.j << " " << bond.tag;
}

std::ostream &operator<<(std::ostream &out, const Angle &angle) {
  return out << "Angle " << angle.a << " " << angle.b << " " << angle.c << " "
	     << angle.tag;
}

std::ostream &operator<<(std::ostream &out, const Torsion &torsion) {
  return out << "Torsion " << torsion.a << " " << torsion.b << " " << torsion.c
	     << " " << torsion.d << " " << torsion.tag;
}

std::ostream &operator<<(std::ostream &out, const Isotopologue &isotopologue) {
  out << "Isotopologue " << isotopologue.name;
  for (auto k : isotopologue.kind)
    out << " " << k;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Site &site) {
  out << "Site " << site.name;
  out << " Origin";
  for (auto org : site.origins)
    out << " " << org;
  out << " Mass Weighted " << site.massWeighted;
  out << " xaxis " << site.xaxis;
  out << " yaxis " << site.yaxis;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Forcefield &forcefield) {
  return out << "Forcefield" << forcefield.name;
}

std::ostream &operator<<(std::ostream &out, const Species &s) {
  out << "Species " << s.name_ << std::endl;
  for (auto atom : s.atoms_) {
    out << atom << std::endl;
  }
  for (auto bond : s.bonds_) {
    out << bond << std::endl;
  }
  for (auto angle : s.angles_) {
    out << angle << std::endl;
  }
  for (auto torsion : s.torsions_) {
    out << torsion << std::endl;
  }
  for (auto isotopologue : s.isotopologues_) {
    out << isotopologue << std::endl;
  }
  for (auto site : s.sites_) {
    out << site << std::endl;
  }
  for (auto forcefield : s.forcefields_) {
    out << forcefield << std::endl;
  }
  return out;
}

// Pair Potential terms

std::ostream &operator<<(std::ostream &out, const PairPotentialParameters &p) {
  return out << "Parameters " << p.name_ << " " << p.element_ << " "
	     << p.strength_;
}

std::ostream &operator<<(std::ostream &out, const PairPotential &p) {
  out << "Pair Potential" << std::endl;
  for (auto param : p.params_)
    out << param << std::endl;
  return out;
}

// The main program

std::ostream &operator<<(std::ostream &out, const Program &p) {
  out << "Program Description" << std::endl;
  for (auto s : p.species_) {
    out << s << std::endl;
  }
  out << p.pairPotential_;
  out << "End Program" << std::endl;
  return out;
}
