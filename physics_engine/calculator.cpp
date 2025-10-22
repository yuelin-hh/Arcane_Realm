#include "calculator.h"
#include <iostream>

using namespace std;

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

inline vector<Complex> Calculator::solveQuadratic(double a, double b, double c) {
    if (abs(a) < EPSILON) {
        if (abs(b) < EPSILON) return vector<Complex>();
        return vector<Complex>{Complex(-c / b, 0)};
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= -EPSILON) {
        double sqrt_d = sqrt(max(discriminant, 0.0));
        return vector<Complex>{
            Complex((-b + sqrt_d) / (2 * a), 0),
                Complex((-b - sqrt_d) / (2 * a), 0)
        };
    }
    else {
        double sqrt_d = sqrt(-discriminant);
        double real_part = -b / (2 * a);
        double imag_part = sqrt_d / (2 * a);
        return vector<Complex>{
            Complex(real_part, imag_part),
                Complex(real_part, -imag_part)
        };
    }
}

struct Calculator::EquationCoeffs {
    double a, b, c, d, e, f;

    EquationCoeffs(double a_val, double b_val, double c_val, double d_val, double e_val, double f_val)
        : a(a_val), b(b_val), c(c_val), d(d_val), e(e_val), f(f_val) {
    }

    // 快速计算在给定y时的x解
    inline vector<Complex> solveForX(double y) const {
        double A = a;
        double B = b * y + d;
        double C = c * y * y + e * y + f;
        return solveQuadratic(A, B, C);
    }

    // 快速计算在给定x时的y解
    inline vector<Complex> solveForY(double x) const {
        double A = c;
        double B = b * x + e;
        double C = a * x * x + d * x + f;
        return solveQuadratic(A, B, C);
    }

    // 计算方程在点(x,y)处的值
    double evaluate(double x, double y) const {
        return a * x * x + b * x * y + c * y * y + d * x + e * y + f;
    }
};

vector<Solution> Calculator::solveBivariateQuadraticOptimized(
    double a1, double b1, double c1, double d1, double e1, double f1,
    double a2, double b2, double c2, double d2, double e2, double f2) {

    vector<Solution> solutions;
    solutions.reserve(8);

    EquationCoeffs eq1(a1, b1, c1, d1, e1, f1);
    EquationCoeffs eq2(a2, b2, c2, d2, e2, f2);

    // 改进的求解策略：直接代入法
    auto solveBySubstitution = [&]() {
        // 如果第一个方程是线性的，直接代入
        if (abs(a1) < EPSILON && abs(b1) < EPSILON && abs(c1) < EPSILON) {
            // 线性方程: d1*x + e1*y + f1 = 0
            if (abs(d1) > EPSILON) {
                // 用y表示x: x = (-e1*y - f1) / d1
                for (double y = -MAX_RANGE; y <= MAX_RANGE; y += SAMPLE_STEP) {
                    double x = (-e1 * y - f1) / d1;
                    double error1 = abs(eq1.evaluate(x, y));
                    double error2 = abs(eq2.evaluate(x, y));
                    if (error1 < EPSILON && error2 < EPSILON) {
                        solutions.push_back(make_pair(Complex(x, 0), Complex(y, 0)));
                    }
                }
            }
        }

        // 如果第二个方程是线性的，直接代入
        if (abs(a2) < EPSILON && abs(b2) < EPSILON && abs(c2) < EPSILON) {
            // 线性方程: d2*x + e2*y + f2 = 0
            if (abs(d2) > EPSILON) {
                // 用y表示x: x = (-e2*y - f2) / d2
                for (double y = -MAX_RANGE; y <= MAX_RANGE; y += SAMPLE_STEP) {
                    double x = (-e2 * y - f2) / d2;
                    double error1 = abs(eq1.evaluate(x, y));
                    double error2 = abs(eq2.evaluate(x, y));
                    if (error1 < EPSILON && error2 < EPSILON) {
                        solutions.push_back(make_pair(Complex(x, 0), Complex(y, 0)));
                    }
                }
            }
        }
        };

    solveBySubstitution();

    // 如果还没有找到解，使用数值方法
    if (solutions.empty()) {
        // 数值搜索
        for (double x = -MAX_RANGE; x <= MAX_RANGE; x += SAMPLE_STEP) {
            auto y_sols1 = eq1.solveForY(x);
            auto y_sols2 = eq2.solveForY(x);

            for (const auto& y1 : y_sols1) {
                for (const auto& y2 : y_sols2) {
                    if (abs(y1 - y2) < EPSILON) {
                        double error1 = abs(eq1.evaluate(x, y1.real()));
                        double error2 = abs(eq2.evaluate(x, y1.real()));
                        if (error1 < EPSILON && error2 < EPSILON) {
                            solutions.push_back(make_pair(Complex(x, 0), y1));
                        }
                    }
                }
            }
        }

        for (double y = -MAX_RANGE; y <= MAX_RANGE; y += SAMPLE_STEP) {
            auto x_sols1 = eq1.solveForX(y);
            auto x_sols2 = eq2.solveForX(y);

            for (const auto& x1 : x_sols1) {
                for (const auto& x2 : x_sols2) {
                    if (abs(x1 - x2) < EPSILON) {
                        double error1 = abs(eq1.evaluate(x1.real(), y));
                        double error2 = abs(eq2.evaluate(x1.real(), y));
                        if (error1 < EPSILON && error2 < EPSILON) {
                            solutions.push_back(make_pair(x1, Complex(y, 0)));
                        }
                    }
                }
            }
        }
    }

    // 去重
    if (solutions.size() > 1) {
        vector<Solution> unique_solutions;
        for (size_t i = 0; i < solutions.size(); i++) {
            bool is_duplicate = false;
            for (size_t j = 0; j < i; j++) {
                if (abs(solutions[i].first - solutions[j].first) < EPSILON &&
                    abs(solutions[i].second - solutions[j].second) < EPSILON) {
                    is_duplicate = true;
                    break;
                }
            }
            if (!is_duplicate) {
                unique_solutions.push_back(solutions[i]);
            }
        }
        solutions = unique_solutions;
    }

    return solutions;
}

void Calculator::printSolutionsOptimized(const vector<Solution>& solutions) {
    if (solutions.empty()) {
        cout << "无解" << endl;
        return;
    }

    cout << "找到 " << solutions.size() << " 个解:" << endl;
    for (size_t i = 0; i < solutions.size(); i++) {
        const auto& sol = solutions[i];
        cout << "解 " << i + 1 << ": ";
        cout << "x = " << sol.first.real() << ", y = " << sol.second.real();
        if (abs(sol.first.imag()) > EPSILON || abs(sol.second.imag()) > EPSILON) {
            cout << " (包含虚部)";
        }
        cout << endl;
    }
}

const double Calculator::EPSILON = 1e-8;
const double Calculator::SAMPLE_STEP = 0.01;
const double Calculator::MAX_RANGE = 20.0;