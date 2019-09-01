#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
#include <cassert>

namespace readwrite{
	extern const char * samplefile;
	
	struct Readin {
		std::vector<std::string> exp_element;
		std::vector<float> exp_val;
		std::vector<std::map<std::string, int>> mol_list;
		float maxerr;
		int maxcyc;
		bool printmore;
		Readin();
	};
	struct Putout {
		std::vector<std::string> exp_element;
		std::vector<float> calc_val;
		std::vector<std::map<std::string, int>> mol_list;
		std::vector<float> mol_massratio;
		std::vector<float> err_vec;
	};
	struct Putoutlast {
		std::vector<std::map<std::string, int>> mol_list;
		std::vector<float> mol_molratio;
	};
	
	readwrite::Readin readfile(std::ifstream &is);
	std::ostream & writefile_step(std::ostream &os, const Putout &res);
	std::ostream & writefile(std::ostream &os, const Putoutlast &res);
	std::ofstream & writesample(std::ofstream &os);
	std::ostream & writewelcome(std::ostream &os);
	std::ostream & writeusage(std::ostream &os, const char * progname);
}
