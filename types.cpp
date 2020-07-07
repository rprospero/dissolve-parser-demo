#include "types.h"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const Vec3 &vec) {
  out << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Cos3 &bond) {
  return out << "Cos3 " << bond.vec;
}

std::ostream &operator<<(std::ostream &out, const Harmonic &bond) {
  return out << "Harmonic " << bond.i << " " << bond.j;
}

std::ostream& operator<<(std::ostream& out, const BondKind& bond) {
  if (std::holds_alternative<Cos3>(bond)) {
    return out << std::get<Cos3>(bond);
  } else if (std::holds_alternative<Harmonic>(bond)) {
    return out << std::get<Harmonic>(bond);
  }
  return out << "Invalid BondKind" << bond.index();
}

std::ostream &operator<<(std::ostream &out, const Atom &atom) {
  out << "Atom " << atom.element << " " << atom.index << " " << atom.position
      << " " << atom.type;
  if (atom.charge)
    out << " " << *atom.charge;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Bond &bond) {
  out << "Bond " << bond.i << " " << bond.j << " " << bond.tag;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Angle &angle) {
  out << "Angle " << angle.a << " " << angle.b << " " << angle.c << " "
      << angle.tag;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Torsion &torsion) {
  out << "Torsion " << torsion.a << " " << torsion.b << " " << torsion.c << " "
      << torsion.d << " " << torsion.tag;
  return out;
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
  out << "Forcefield" << forcefield.name;
  return out;
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
