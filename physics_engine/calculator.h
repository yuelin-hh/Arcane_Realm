#pragma once

#include <vector>
#include <cmath>
#include <complex>

using Complex = std::complex<double>;
using Solution = std::pair<Complex, Complex>;

class Calculator
{
public:
	Calculator();
	~Calculator();

	static inline std::vector<Complex> solveQuadratic(double a, double b, double c);

	struct EquationCoeffs;

	static std::vector<Solution> solveBivariateQuadraticOptimized(
		double a1, double b1, double c1, double d1, double e1, double f1,
		double a2, double b2, double c2, double d2, double e2, double f2);

	static void printSolutionsOptimized(const std::vector<Solution>& solutions);
private:
	static const double EPSILON;
	static const double SAMPLE_STEP;  // 更小的步长
	static const double MAX_RANGE;
};