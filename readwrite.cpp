#include "readwrite.h"

namespace readwrite {
	static const char * en = "ElementNumber:";
	static const char * el = "ElementList:";
	static const char * em = "ElementMeasure:";
	static const char * mn = "MaterialNumber:";
	static const char * ml = "MaterialList:";
	static const char * ca = "ConvergeAt:";
	static const char * mc = "MaxCycle:";
	static const char * pm = "PrintMore:";
	const char * samplefile = "input.txt";
	static constexpr int maxlinesize = 255;
	static constexpr int defaultmaxcyc = 32;
	static constexpr float defaultmaxerr = 0.4f;
	static constexpr bool defaultprintmore = false;

	Readin::Readin() : maxerr(readwrite::defaultmaxerr),
		maxcyc(readwrite::defaultmaxcyc),
		printmore(readwrite::defaultprintmore) {};

	class Linereader {
	public:
		bool operator << (const char * buf) {
			std::string str = buf;
			std::istringstream strs(str);
			std::string word;
			strs >> word;
			if (word == readwrite::en) {
				if (reg.en) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::en);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				strs >> element_num;
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::en);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
					return false;
				}
				if (element_num < 1) {
					std::string errinfo = "Logic Error: Non-positive parameter for \"";
					errinfo.append(readwrite::en);
					errinfo.append("\".\n  Must give a positive integer.\n");
					throw errinfo;
					return false;
				}
				reg.en = true;
				return true;
			}
			if (word == readwrite::el) {
				if (!reg.en) {
					std::string errinfo = "Logic Error: Sepcify elements' number first.\n";
					errinfo.append("  Sepcifiers' order error.\n");
					throw errinfo;
					return false;
				}
				if (reg.el) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::el);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				for (int i = 0; i < element_num; ++i) {
					strs >> word;
					info.exp_element.push_back(word);
				}
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::el);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
					return false;
				}
				reg.el = true;
				return true;
			}
			if (word == readwrite::em) {
				if (!reg.en) {
					std::string errinfo = "Logic Error: Sepcify elements' number first.\n";
					errinfo.append("  Sepcifiers' order error.\n");
					throw errinfo;
				}
				if (reg.em) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::em);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
				}
				float fword;
				for (int i = 0; i < element_num; ++i) {
					strs >> fword;
					info.exp_val.push_back(fword);
				}
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::em);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
				}
				reg.em = true;
				return true;
			}
			if (word == readwrite::mn) {
				if (!reg.en) {
					std::string errinfo = "Logic Error: Sepcify elements' number first.\n";
					errinfo.append("  Sepcifiers' order error.\n");
					throw errinfo;
					return false;
				}
				if (reg.mn) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::mn);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				strs >> material_num;
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::mn);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
					return false;
				}
				if (material_num < 1) {
					std::string errinfo = "Logic Error: Non-positive parameter for \"";
					errinfo.append(readwrite::mn);
					errinfo.append("\".\n  Must give a positive integer.\n");
					throw errinfo;
					return false;
				}
				if (material_num > element_num + 1) {
					std::string errinfo = "Logic Error: Materials' number should be no larger than elements' + 1.\n";
					errinfo.append("  Materials' number is too large.\n");
					throw errinfo;
					return false;
				}
				reg.mn = true;
				return true;
			}
			if (word == readwrite::ml) {
				if (!reg.mn) {
					std::string errinfo = "Logic Error: Sepcify materials' number first.\n";
					errinfo.append("  Sepcifiers' order error.\n");
					throw errinfo;
					return false;
				}
				if (reg.ml) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::ml);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				for (int i = 0; i < material_num; ++i) {
					strs >> word;
					if (strs.fail()) {
						std::string errinfo = "Syntax Error: Fail to read \"";
						errinfo.append(readwrite::ml);
						errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
						throw errinfo;
						return false;
					}
					info.mol_list.push_back(getmolecule(word));
				}
				reg.ml = true;
				return true;
			}
			if (word == readwrite::ca) {
				if (reg.ca) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::ca);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				strs >> info.maxerr;
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::ca);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
					return false;
				}
				reg.ca = true;
				return true;
			}
			if (word == readwrite::mc) {
				if (reg.mc) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::mc);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				strs >> info.maxcyc;
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::mc);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
					return false;
				}
				reg.mc = true;
				return true;
			}
			if (word == readwrite::pm) {
				if (reg.pm) {
					std::string errinfo = "Logic Error: Duplicate specify \"";
					errinfo.append(readwrite::pm);
					errinfo.append("\".\n  Duplicate.\n");
					throw errinfo;
					return false;
				}
				strs >> info.printmore;
				if (strs.fail()) {
					std::string errinfo = "Syntax Error: Fail to read \"";
					errinfo.append(readwrite::pm);
					errinfo.append("\"'s parameter.\n  Invalid parameter or parameters.\n");
					throw errinfo;
					return false;
				}
				reg.pm = true;
				return true;
			}
			std::string errinfo = "Syntax Error: cannot understand \"";
			errinfo.append(word);
			errinfo.append("\".\n  Invalid specifier.\n");
			throw errinfo;
			return false;
		}
		bool valid() const {
			if (reg.el && reg.em && reg.en && reg.ml && reg.mn)
				return true;
			return false;
		}
		Readin getinfo() const {
			return info;
		}
	private:
		struct Register {
			bool en; bool el; bool em; bool mn; bool ml; bool ca; bool mc; bool pm;
			Register() : en(false), el(false), em(false), mn(false), ml(false), ca(false), mc(false), pm(false) {};
		};

		Readin info;
		Register reg;
		int element_num = 0, material_num = 0;

		std::map<std::string, int> getmolecule(const std::string& str) {
			std::map<std::string, int> mol;
			std::istringstream strs(str);
			while (strs.good()) {
				auto piece = getpiece(strs);
				if (piece.first.empty() || piece.second == 0) {
					std::string errinfo = "Syntax Error: \"";
					errinfo.append(str);
					errinfo.append("\" is not a molecule formula.\n");
					errinfo.append("  Invalid molecule formula.\n");
					throw errinfo;
					return mol;
				}
				auto iter = mol.find(piece.first);
				if (iter == mol.end())
					mol[piece.first] = piece.second;
				else
					iter->second += piece.second;
			}
			return mol;
		}
		std::pair<std::string, int> getpiece(std::istringstream &iss) {
			std::string element, number;
			while (iss.good()) {
				char ch = iss.peek();
				if (!isalpha(ch))
					break;
				element.push_back(iss.get());
			}
			while (iss.good()) {
				char nu = iss.peek();
				if (!isdigit(nu))
					break;
				number.push_back(iss.get());
			}
			int number_int = atoi(number.c_str());
			return std::make_pair(element, number_int);
		}
	};
}

readwrite::Readin readwrite::readfile(std::ifstream &is) {
	char buf[maxlinesize + 1];
	Linereader lin;
	while (is.good()) {
		is.getline(buf, maxlinesize);
		if (buf[0] == '\0' || buf[0] == '#')
			continue;
		if (lin << buf)
			continue;
		
	}
	if (!lin.valid()) {
		std::string errinfo = "Syntax Error: lack of required specifier.\n";
		throw errinfo;
	}
	return lin.getinfo();
}

std::ostream & readwrite::writewelcome(std::ostream &os){
	os << "****************\n";
	os << "*              *\n";
	os << "*   EASolver   *\n";
	os << "*              *\n";
	os << "****************\n";
	os << std::endl;
	return os;
}

std::ostream & readwrite::writeusage(std::ostream &os, const char * progname){
	os << "Usage:\n";
	os << "  " << progname << " <infile>\n\n";
	os << "Instance:\n";
	os << "  " << progname << " input.txt\n\n";
	os << "Call\n";
	os << "  " << progname << " \?\n";
	os << "for a sample infile as \"" << readwrite::samplefile << "\" at current folder.\n";
	os << std::endl;
	return os;
}

std::ofstream & readwrite::writesample(std::ofstream &os){
	os << "# All lines start with '#' will be ignored.\n\n";
	os << "# Also, blank line (with no spacer) will be ignored.\n";
	os << "# Every line should be no longer than " << readwrite::maxlinesize << " bytes.\n";
	os << "# These lines are in format \"<specifier>: <parameter>\".\n";
	os << "# Duplicate specifiers are NOT allowed.\n";
	os << "# The specifier and the parameter are both CASE SeNsItIvE.\n";
	os << "# (Required) " << readwrite::en << " <int>\n\n";
	
	os << readwrite::en << " 3\n\n";
	
	os << "# (Required) " << readwrite::el << " <string> ...\n";
	os << "# This line MUST be after the line \"" << readwrite::en << " <int>\".\n";
	os << "# Must has exact quantity of parameters declared in \"" << readwrite::en << "\".\n\n";
	
	os << readwrite::el << " C H N\n\n";
	
	os << "# (Required) " << readwrite::em << " <float> ...\n";
	os << "# This line MUST be after the line \"" << readwrite::en << " <int>\".\n";
	os << "# Must has exact quantity of parameters declared in \"" << readwrite::en << "\".\n";
	os << "# These values should be in percent format.\n";
	os << "# These values should be in same order of \"" << readwrite::el <<"\".\n\n";
	
	os << readwrite::em << " 83.79 10.11 6.11\n\n";
	
	os << "# (Required) " << readwrite::mn << " <int>\n";
	os << "# This line MUST be after the line \"" << readwrite::en << " <int>\".\n";
	os << "# The value shoule be no larger than " << readwrite::en << " + 1.\n\n";
	
	os << readwrite::mn << " 2\n\n";
	
	os << "# (Required) " << readwrite::ml << " <string> ...\n";
	os << "# This line MUST be after the line \"" << readwrite::mn << " <int>\".\n";
	os << "# Must has exact quantity of parameters declared in \"" << readwrite::mn << "\".\n";
	os << "# \"H2O\" is NOT allowed! you should write \"H2O1\" instead.\n";
	os << "# Brakets \"(N1H4)2S1O4\", floats \"Pd1H0.5\", dots \"Cu1S1O4.H2O1\" are NOT allowed!\n";
	os << "# Your main substance shoule be the first one.\n\n";
	
	os << readwrite::ml << " C10H8 C6H15N1\n\n";
	
	os << "# (Optional) " << readwrite::ca << " <float>\n";
	os << "# Assume the maximum error allowed.\n";
	os << "# DO NOT set it if you don't understand it.\n\n";
	
	os << "#" << readwrite::ca << " " << readwrite::defaultmaxerr << "\n\n";
	
	os << "# (Optional) " << readwrite::mc << " <int>\n";
	os << "# Assume the maximum iteration cycles allowed.\n";
	os << "# DO NOT set it if you don't understand it.\n\n";
	
	os << "#" << readwrite::mc << " " << readwrite::defaultmaxcyc << "\n\n";
	
	os << "# (Optional) " << readwrite::pm << " <int>\n";
	os << "# 0 for Standard Print, 1 for Detail Print.\n";
	os << "# DO NOT set it if you don't understand it.\n\n";
	int i = readwrite::defaultprintmore ? 1 : 0;
	
	os << "#" << readwrite::pm << " " << i << "\n";
	
	os << std::endl;
	return os;
}

std::pair<float, float> maxrws(const std::vector<float> err){
	assert(!err.empty());
	float maxerr = 0.0f, rwserr = 0.0f;
	for(float item : err){
		maxerr = item > maxerr ? item : maxerr;
		rwserr += item;
	}
	rwserr /= err.size();
	maxerr = std::sqrt(maxerr);
	rwserr = std::sqrt(rwserr);
	return std::make_pair(maxerr, rwserr);
}

std::ostream & readwrite::writefile_step(std::ostream &os, const Putout &res){
	assert(res.exp_element.size() == res.calc_val.size());
	assert(res.mol_list.size() == res.mol_massratio.size());
	os << "  Material Composition in Mass Ratio:\n";
	for(size_t i = 0; i < res.mol_list.size(); ++i){
		os << "    ";
		for(const std::pair<std::string, int> & item : res.mol_list[i])
			os << item.first << item.second;
		os << ": " << res.mol_massratio[i] << '\n';
	}
	os << "  Element Composition in the Condition above:\n";
	for(size_t i = 0; i < res.exp_element.size(); ++i){
		os << "    " << res.exp_element[i];
		os << ": " << res.calc_val[i] << '\n';
	}
	auto error = maxrws(res.err_vec);
	os << "  Converge Information:\n";
	os << "    Maximum Error: " << error.first << '\n';
	os << "    RWS     Error: " << error.second << '\n';
	os << std::endl;
	return os;
}

std::ostream & readwrite::writefile(std::ostream &os, const Putoutlast &res){
	assert(res.mol_list.size() == res.mol_molratio.size());
	float factor = res.mol_molratio[0];

	os << "  Material Composition in Molar Ratio:\n";
	for (size_t i = 0; i < res.mol_list.size(); ++i) {
		os << "    ";
		for (const std::pair<std::string, int> & item : res.mol_list[i])
			os << item.first << item.second;
		os << ": " << res.mol_molratio[i] / factor << '\n';
	}
	os << std::endl;
	return os;
}
