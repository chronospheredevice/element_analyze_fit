#pragma once
#include "matrix.h"

namespace easolver {
	class Solver {
	public:
		explicit Solver(const std::vector<float> &exp, const std::vector<std::vector<float>> &thr);
		void iterate();
		std::vector<float> getguess();
		std::vector<float> geterr();
		bool checkerr(const std::vector<float> &err, float maxerr) const;
	private:
		std::vector<std::vector<float>> exp_val;
		std::vector<std::vector<float>> thr_val;
		std::vector<std::vector<float>> guess;
		std::vector<std::vector<float>> err;
		bool guess_change;

		std::vector<std::vector<float>> geterr_inner();
		inline void updateguess();		
		std::vector<std::vector<float>> jacobi();		
	};
}