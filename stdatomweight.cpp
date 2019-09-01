#include "stdatomweight.h"

namespace stdweight {
	std::map<std::string, float> gettable() {
		std::map<std::string, float> table;
		table["H"] = 1.008f;
		table["He"] = 4.002602f;
		table["Li"] = 6.94f;
		table["Be"] = 9.0121831f;
		table["B"] = 10.81f;
		table["C"] = 12.011f;
		table["N"] = 14.007f;
		table["O"] = 15.999f;
		table["F"] = 18.998403163f;
		table["Ne"] = 20.1797f;
		table["Na"] = 22.98976928f;
		table["Mg"] = 24.305f;
		table["Al"] = 26.9815384f;
		table["Si"] = 28.085f;
		table["P"] = 30.973761998f;
		table["S"] = 32.06f;
		table["Cl"] = 35.45f;
		table["Ar"] = 39.88f;
		table["K"] = 39.0983f;
		table["Ca"] = 40.078f;
		table["Sc"] = 44.955908f;
		table["Ti"] = 47.867f;
		table["V"] = 50.9415f;
		table["Cr"] = 51.9961f;
		table["Mn"] = 54.938043f;
		table["Fe"] = 55.845f;
		table["Co"] = 58.933194f;
		table["Ni"] = 58.6934f;
		table["Cu"] = 63.546f;
		table["Zn"] = 65.38f;
		table["Ga"] = 69.723f;
		table["Ge"] = 72.63f;
		table["As"] = 74.921595f;
		table["Se"] = 78.971f;
		table["Br"] = 79.904f;
		table["Kr"] = 83.798f;
		table["Rb"] = 85.4678f;
		table["Sr"] = 87.62f;
		table["Y"] = 88.90584f;
		table["Zr"] = 91.224f;
		table["Nb"] = 92.90637f;
		table["Mo"] = 95.95f;
		table["Ru"] = 101.07f;
		table["Rh"] = 102.90549f;
		table["Pd"] = 106.42f;
		table["Ag"] = 107.8682f;
		table["Cd"] = 112.414f;
		table["In"] = 114.818f;
		table["Sn"] = 118.71f;
		table["Sb"] = 121.76f;
		table["Te"] = 127.6f;
		table["I"] = 126.90447f;
		table["Xe"] = 131.293f;
		table["Cs"] = 132.90545196f;
		table["Ba"] = 137.327f;
		table["La"] = 138.90547f;
		table["Ce"] = 140.116f;
		table["Pr"] = 140.90766f;
		table["Nd"] = 144.242f;
		table["Sm"] = 150.36f;
		table["Eu"] = 151.964f;
		table["Gd"] = 157.25f;
		table["Tb"] = 158.925354f;
		table["Dy"] = 162.5f;
		table["Ho"] = 164.930328f;
		table["Er"] = 167.259f;
		table["Tm"] = 168.934218f;
		table["Yb"] = 173.045f;
		table["Lu"] = 174.9668f;
		table["Hf"] = 178.49f;
		table["Ta"] = 180.94788f;
		table["W"] = 183.84f;
		table["Re"] = 186.207f;
		table["Os"] = 190.23f;
		table["Ir"] = 192.217f;
		table["Pt"] = 195.084f;
		table["Au"] = 196.96657f;
		table["Hg"] = 200.592f;
		table["Tl"] = 204.38f;
		table["Pb"] = 207.2f;
		table["Bi"] = 208.9804f;
		table["Th"] = 232.0377f;
		table["Pa"] = 231.03588f;
		table["U"] = 238.02891f;
		return table;
	}

	Molecule::Molecule() {
		table["H"] = 1.008f;
		table["He"] = 4.002602f;
		table["Li"] = 6.94f;
		table["Be"] = 9.0121831f;
		table["B"] = 10.81f;
		table["C"] = 12.011f;
		table["N"] = 14.007f;
		table["O"] = 15.999f;
		table["F"] = 18.998403163f;
		table["Ne"] = 20.1797f;
		table["Na"] = 22.98976928f;
		table["Mg"] = 24.305f;
		table["Al"] = 26.9815384f;
		table["Si"] = 28.085f;
		table["P"] = 30.973761998f;
		table["S"] = 32.06f;
		table["Cl"] = 35.45f;
		table["Ar"] = 39.88f;
		table["K"] = 39.0983f;
		table["Ca"] = 40.078f;
		table["Sc"] = 44.955908f;
		table["Ti"] = 47.867f;
		table["V"] = 50.9415f;
		table["Cr"] = 51.9961f;
		table["Mn"] = 54.938043f;
		table["Fe"] = 55.845f;
		table["Co"] = 58.933194f;
		table["Ni"] = 58.6934f;
		table["Cu"] = 63.546f;
		table["Zn"] = 65.38f;
		table["Ga"] = 69.723f;
		table["Ge"] = 72.63f;
		table["As"] = 74.921595f;
		table["Se"] = 78.971f;
		table["Br"] = 79.904f;
		table["Kr"] = 83.798f;
		table["Rb"] = 85.4678f;
		table["Sr"] = 87.62f;
		table["Y"] = 88.90584f;
		table["Zr"] = 91.224f;
		table["Nb"] = 92.90637f;
		table["Mo"] = 95.95f;
		table["Ru"] = 101.07f;
		table["Rh"] = 102.90549f;
		table["Pd"] = 106.42f;
		table["Ag"] = 107.8682f;
		table["Cd"] = 112.414f;
		table["In"] = 114.818f;
		table["Sn"] = 118.71f;
		table["Sb"] = 121.76f;
		table["Te"] = 127.6f;
		table["I"] = 126.90447f;
		table["Xe"] = 131.293f;
		table["Cs"] = 132.90545196f;
		table["Ba"] = 137.327f;
		table["La"] = 138.90547f;
		table["Ce"] = 140.116f;
		table["Pr"] = 140.90766f;
		table["Nd"] = 144.242f;
		table["Sm"] = 150.36f;
		table["Eu"] = 151.964f;
		table["Gd"] = 157.25f;
		table["Tb"] = 158.925354f;
		table["Dy"] = 162.5f;
		table["Ho"] = 164.930328f;
		table["Er"] = 167.259f;
		table["Tm"] = 168.934218f;
		table["Yb"] = 173.045f;
		table["Lu"] = 174.9668f;
		table["Hf"] = 178.49f;
		table["Ta"] = 180.94788f;
		table["W"] = 183.84f;
		table["Re"] = 186.207f;
		table["Os"] = 190.23f;
		table["Ir"] = 192.217f;
		table["Pt"] = 195.084f;
		table["Au"] = 196.96657f;
		table["Hg"] = 200.592f;
		table["Tl"] = 204.38f;
		table["Pb"] = 207.2f;
		table["Bi"] = 208.9804f;
		table["Th"] = 232.0377f;
		table["Pa"] = 231.03588f;
		table["U"] = 238.02891f;
	}

	float Molecule::getweight(const std::map<std::string, int> &mol) const {
		float weight = 0.0f;
		for (auto item : mol) {
			auto iter = table.find(item.first);
			if (iter == table.end()) {
				std::string errinfo = "Element Error: Element \"";
				errinfo.append(item.first);
				errinfo.append("\" has no atom weight.\n");
				errinfo.append("  Cannot calculate molecular weight.\n");
				throw errinfo;
				return 0.0f;
			}
			weight += iter->second * item.second;
		}
		return weight;
	}

	std::vector<float> Molecule::getpercent(const std::map<std::string, int> &mol, const std::vector<std::string> &element) const {
		std::vector<float> percent(element.size());
		float weight = getweight(mol);
		for (size_t i = 0; i < element.size(); ++i) {
			auto iter = mol.find(element[i]);
			if (iter == mol.end())
				percent[i] = 0.0f;
			else {
				auto table_iter = table.find(element[i]);
				percent[i] = table_iter->second * iter->second / weight * 100;
			}
		}
		return percent;
	}

	std::vector<float> Molecule::massratio_to_molratio(const std::vector<std::map<std::string, int>>& mols, const std::vector<float>& mass) const{
		assert(mols.size() == mass.size());
		std::vector<float> molmass(mass.size());
		for (size_t i = 0; i < mols.size(); ++i) {
			molmass[i] = getweight(mols[i]);
			molmass[i] = mass[i] / molmass[i];
		}
		return molmass;
	}
}