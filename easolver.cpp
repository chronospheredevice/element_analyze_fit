#include "easolver.h"

namespace easolver{
	constexpr float stepsize = 0.001f;

	Solver::Solver(const std::vector<float> &exp, const std::vector<std::vector<float>> &thr){
		assert(exp.size() == thr[0].size());
		std::vector<std::vector<float>> exp_tmp;
		exp_tmp.push_back(exp);
		exp_val = matrix::trans(exp_tmp);
		thr_val = matrix::trans(thr);
		std::vector<std::vector<float>> guess_tmp;
		std::vector<float> guess_tmp_row(thr.size(), 0.0);
		guess_tmp_row[0] = 1.0;
		guess_tmp.push_back(guess_tmp_row);
		guess = matrix::trans(guess_tmp);
		guess_change = true;
	}

	std::vector<float> Solver::getguess() {
		return matrix::trans(guess)[0];
	}

	std::vector<float> Solver::geterr() {
		return matrix::trans(geterr_inner())[0];
	}
	
	std::vector<std::vector<float>> Solver::geterr_inner() {
		if (guess_change) {
			std::vector<std::vector<float>> product = matrix::multi(thr_val, guess);
			assert(product[0].size() == 1);
			err = matrix::minus(product, exp_val);
			for (unsigned int i = 0; i < err.size(); ++i)
				err[i][0] *= err[i][0];
			guess_change = false;
		}
		return err;
	}

	bool Solver::checkerr(const std::vector<float> &err, float maxerr) const {
		for (unsigned int i = 0; i < err.size(); ++i)
			if (err[i] > maxerr)
				return false;
		return true;
	}

	inline void Solver::updateguess(){
		float sum = 0.0;
		for(unsigned int i = 1; i < guess.size(); ++i)
			sum += guess[i][0];
		guess[0][0] = 1.0f - sum;
	}

	std::vector<std::vector<float>> Solver::jacobi() {
		std::vector<float> out_tmp(thr_val[0].size() - 1);
		std::vector<std::vector<float>> out(thr_val.size(), out_tmp);
		std::vector<std::vector<float>> nowerr = geterr_inner();
		for (unsigned int i = 1; i < guess.size(); ++i) {
			guess[0][0] -= easolver::stepsize;
			guess[i][0] += easolver::stepsize;
			guess_change = true;
			std::vector<std::vector<float>> delta = matrix::minus(geterr_inner(), nowerr);
			assert(out.size() == delta.size());
			for (unsigned int j = 0; j < out.size(); ++j)
				out[j][i - 1] = delta[j][0] / easolver::stepsize;
			guess[0][0] += easolver::stepsize;
			guess[i][0] -= easolver::stepsize;
		}
		guess_change = true;
		return out;
	}

	void Solver::iterate() {
		std::vector<std::vector<float>> err = geterr_inner();
		std::vector<std::vector<float>> jac = jacobi();
		std::vector<std::vector<float>> jac_T = matrix::trans(jac);
		std::vector<std::vector<float>> delta =
			matrix::multi(matrix::inv(matrix::multi(jac_T, jac)), matrix::multi(jac_T, err));
		for (unsigned int i = 1; i < guess.size(); ++i)
			guess[i][0] -= delta[i - 1][0];
		updateguess();
		guess_change = true;
	}
}
