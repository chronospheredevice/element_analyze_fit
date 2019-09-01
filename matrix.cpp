#include "matrix.h"

namespace matrix {
	int sign(unsigned int src) {
		// return (-1)^src.
		if (src & 1)
			return -1;
		else
			return 1;
	}

	std::vector<std::vector<float>> trans(const std::vector<std::vector<float>> &src) {
		assert(!src.empty());
		assert(!src[0].empty());
		unsigned int rowsize = src[0].size(); // switch row and column.
		unsigned int columnsize = src.size(); // switch row and column.
		std::vector<float> tmp(columnsize);
		std::vector<std::vector<float>> out(rowsize, tmp);
		for (unsigned int i = 0; i < rowsize; ++i) {
			for (unsigned int j = 0; j < columnsize; ++j)
				out[i][j] = src[j][i];
		}
		return out;
	}

	std::vector<std::vector<float>> cofactor(const std::vector<std::vector<float>> &src, const std::pair<int, int> &coordinate) {
		assert(src.size() > 1);
		assert(src[0].size() > 1);
		unsigned int rowsize = src.size() - 1;
		unsigned int columnsize = src[0].size() - 1;
		std::vector<float> tmp(columnsize);
		std::vector<std::vector<float>> out(rowsize, tmp);
		for (unsigned int i = 0, x = 0; x < rowsize; ++i, ++x) {
			if (i == coordinate.first) {
				--x;
				continue;
			}
			for (unsigned int j = 0, y = 0; y < columnsize; ++j, ++y) {
				if (j == coordinate.second) {
					--y;
					continue;
				}
				out[x][y] = src[i][j];
			}
		}
		return out;
	}

	float det(const std::vector<std::vector<float>> &src) {
		assert(!src.empty());
		assert(!src[0].empty());
		assert(src.size() == src[0].size());
		if (src.size() == 1)
			return src[0][0];
		float out = 0.0;
		for (unsigned int i = 0, j = 0; j < src[0].size(); ++j)
			out += sign(i + j) * src[i][j] * det(cofactor(src, std::make_pair(i, j)));
		return out;
	}

	std::vector<std::vector<float>> inv(const std::vector<std::vector<float>> &src) {
		assert(!src.empty());
		assert(!src[0].empty());
		assert(src.size() == src[0].size());
		float detval = det(src);
		if (detval == 0.0)
			throw "singular matrix";
		unsigned int rowsize = src.size();
		unsigned int columnsize = src[0].size();
		std::vector<float> tmp(columnsize);
		std::vector<std::vector<float>> out(rowsize, tmp);
		if (rowsize == 1)
			out[0][0] = 1 / detval;
		else {
			for (unsigned int i = 0; i < rowsize; ++i) {
				for (unsigned int j = 0; j < columnsize; ++j)
					out[j][i] = sign(i + j) * det(cofactor(src, std::make_pair(i, j))) / detval;
			}
		}
		return out;
	}

	std::vector<std::vector<float>> multi(const std::vector<std::vector<float>> &left, const std::vector<std::vector<float>> &right) {
		assert(!left.empty());
		assert(!left[0].empty());
		assert(!right.empty());
		assert(!right[0].empty());
		assert(left[0].size() == right.size());
		unsigned int rowsize = left.size();
		unsigned int columnsize = right[0].size();
		unsigned int interval = right.size();
		std::vector<float> tmp(columnsize, 0.0);
		std::vector<std::vector<float>> out(rowsize, tmp);
		for (unsigned int i = 0; i < rowsize; ++i) {
			for (unsigned int j = 0; j < columnsize; ++j) {
				for (unsigned int k = 0; k < interval; ++k)
					out[i][j] += left[i][k] * right[k][j];
			}
		}
		return out;
	}

	std::vector<std::vector<float>> minus(const std::vector<std::vector<float>> &left, const std::vector<std::vector<float>> &right) {
		assert(!left.empty());
		assert(!left[0].empty());
		assert(!right.empty());
		assert(!right[0].empty());
		assert(left.size() == right.size());
		assert(left[0].size() == right[0].size());
		unsigned int rowsize = left.size();
		unsigned int columnsize = right[0].size();
		std::vector<float> tmp(columnsize, 0.0);
		std::vector<std::vector<float>> out(rowsize, tmp);
		for (unsigned int i = 0; i < rowsize; ++i) {
			for (unsigned int j = 0; j < columnsize; ++j)
				out[i][j] = left[i][j] - right[i][j];
		}
		return out;
	}
}