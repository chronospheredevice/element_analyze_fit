// elemanal.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "readwrite.h"
#include "easolver.h"
#include "stdatomweight.h"
#define PAUSE_AT_END
constexpr int output_precision = 3;

int main(int argc, char **argv)
{
	std::ostream& os = std::cout;
	os.precision(output_precision);

	readwrite::writewelcome(os);

	if (argc < 2) {
		readwrite::writeusage(os, argv[0]);
		os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
		system("pause");
#endif // PAUSE_AT_END
		return 1;
	}

	if (argc > 2) {
		os << "Too many input files.\n\n";
		os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
		system("pause");
#endif // PAUSE_AT_END
		return 9;
	}

	if (argv[1][0] == '?') {
		std::ofstream ofs(readwrite::samplefile);
		if (!ofs.good()) {
			os << "Failed to open sample file.\n\n";
			os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
			system("pause");
#endif // PAUSE_AT_END
			return 255;
		}
		readwrite::writesample(ofs);
		os << "A sample input file has been writen as \"input.txt\".\n\n";
		os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
		system("pause");
#endif // PAUSE_AT_END
		return 0;
	}

	std::ifstream is(argv[1]);

	if (!is.good()) {
		os << "Failed to open input file.\n\n";
		os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
		system("pause");
#endif // PAUSE_AT_END
		return 255;
	}

	readwrite::Readin data;

	try {
		data = readwrite::readfile(is);
	}
	catch (const std::string &err) {
		std::cout << err;
		os << "\nEASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
		system("pause");
#endif // PAUSE_AT_END
		return 2;
	}

	stdweight::Molecule mole;

	for (const std::string &str : data.exp_element) {
		if (mole.iselement(str))
			continue;
		os << "Element Error: " << str << " is not an element or has no atom mass.\n";
		os << "  Calculation failed.\n\n";
		os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
		system("pause");
#endif // PAUSE_AT_END
		return 2;
	}

	std::vector<std::vector<float>> thr;
	
	for (size_t i = 0; i < data.mol_list.size(); ++i) {
		try {
			thr.push_back(mole.getpercent(data.mol_list[i], data.exp_element));
		}
		catch (const std::string &err){
			std::cout << err;
			os << "\nEASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
			system("pause");
#endif // PAUSE_AT_END
			return 2;
		}
	}

	easolver::Solver solver(data.exp_val, thr);
	std::vector<float> err_vec;
	bool converged = false;
	float limit = data.maxerr * data.maxerr;
	readwrite::Putout cycledata;
	cycledata.exp_element = data.exp_element;
	cycledata.calc_val = data.exp_val;
	cycledata.mol_list = data.mol_list;
	int i;

	for (i = 0; i < data.maxcyc; ++i) {
		err_vec = solver.geterr();
		if (solver.checkerr(err_vec, limit)) {
			converged = true;
			break;
		}
		if (data.printmore) {
			auto guess = solver.getguess();
			cycledata.mol_massratio = guess;
			cycledata.err_vec = err_vec;
			os << "Cycle " << i << " :\n";
			readwrite::writefile_step(os, cycledata);
		}
		solver.iterate();
	}
	
	if (!converged)
		os << "Fail to converge in " << data.maxcyc << " cycles.\n\n";
	else {
		os << "Coverged after " << i << " cycles.\n\n";
		os << "Final Result:\n";
		readwrite::Putoutlast finale;
		finale.mol_list = data.mol_list;
		auto guess = solver.getguess();
		finale.mol_molratio = mole.massratio_to_molratio(data.mol_list, guess);
		cycledata.mol_massratio = guess;
		cycledata.err_vec = err_vec;
		readwrite::writefile_step(os, cycledata);
		readwrite::writefile(os, finale);
	}
	os << "EASlover terminated." << std::endl;
#ifdef PAUSE_AT_END
	system("pause");
#endif // PAUSE_AT_END
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
