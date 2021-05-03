#pragma once

#include <vector>
#include "optimizable.h"

using namespace std;


struct res {
    vector<double> point;
    double value;
    vector<vector<double>> iterations;

    res(vector<double> &&p, double v, vector<vector<double>> &&iters) : point(std::move(p)), value(v),
                                                                        iterations(std::move(iters)) {}
};


struct quadratic_function : optimizable {

    function<double(double, double)> comp_func;
    function<double(double, double)> d_x1;
    function<double(double, double)> d_x2;

    quadratic_function(double a00, double a01, double a10, double a11) {
        comp_func = [=](double x1, double x2) {
            return a00 * pow(x1, 2) + (a10 + a01) * x1 * x2 + a11 * pow(x2, 2);
        };
        d_x1 = [=](double x1, double x2) {
            return 2 * a00 * x1 + (a10 + a01) * x2;
        };
        d_x2 = [=](double x1, double x2) {
            return 2 * a11 * x2 + (a10 + a01) * x1;
        };
    }

    [[nodiscard]] vector<double> get_grad(const vector<double> &x) override {
        return {d_x1(x[0], x[1]), d_x2(x[0], x[1])};
    }

    [[nodiscard]] double get_val(const vector<double> &x) override {
        return comp_func(x[0], x[1]);
    }

};

double vec_norm(const vector<double> &p) {
    double res = 0;
    for (auto elem : p) {
        res += pow(elem, 2);
    }
    return res;
}