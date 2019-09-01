#pragma once
#include <string>
#include <map>
#include <vector>
#include <cassert>

namespace stdweight {
	std::map<std::string, float> gettable();

	class Molecule {
	public:
		Molecule();
		float getweight(const std::map<std::string, int> &mol) const;
		std::vector<float> getpercent(const std::map<std::string, int> &mol, const std::vector<std::string> &element) const;
		std::vector<float> massratio_to_molratio(const std::vector<std::map<std::string, int>> &mols, const std::vector<float> &mass) const;
	private:
		std::map<std::string, float> table;
	};
}
