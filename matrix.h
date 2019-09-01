#pragma once
#include <vector>
#include <cassert>

namespace matrix {
	std::vector<std::vector<float>> trans(const std::vector<std::vector<float>> &src);
	float det(const std::vector<std::vector<float>> &src);
	std::vector<std::vector<float>> inv(const std::vector<std::vector<float>> &src);
	std::vector<std::vector<float>> multi(const std::vector<std::vector<float>> &left, const std::vector<std::vector<float>> &right);
	std::vector<std::vector<float>> minus(const std::vector<std::vector<float>> &left, const std::vector<std::vector<float>> &right);
}