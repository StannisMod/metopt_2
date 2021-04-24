#pragma once

#include <functional>
#include <utility>
#include "brent_method.h"
#include <limits>

using namespace std;

struct res {
    pair<double, double> point;
    double value;

    res(pair<double, double> p, double v) : point(std::move(p)), value(v) {}
};


struct quadratic_function {
    double a00;
    double a01;
    double a10;
    double a11;
    function<double(double, double)> comp_func;
    function<double(double, double)> d_x1;
    function<double(double, double)> d_x2;

    quadratic_function(double a00, double a01, double a10, double a11) : a00(a00), a01(a01), a10(a10), a11(a11) {
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

    [[nodiscard]] pair<double, double> get_grad(double x1, double x2) const {
        return {d_x1(x1, x2), d_x2(x1, x2)};
    }

    [[nodiscard]] double get_val(double x1, double x2) const {
        return comp_func(x1, x2);
    }

};

double pair_norm(pair<double, double> p) {
    return sqrt(pow(p.first, 2) + pow(p.second, 2));
}


res steepest_gradient_descent(const quadratic_function &func, double tol, pair<double, double> starting_point) {
    double val = func.get_val(starting_point.first, starting_point.second);
    brent_method optimizer;
    pair<double, double> grad = func.get_grad(starting_point.first, starting_point.second);
    while (true) {
        if (pair_norm(grad) < tol) {
            return res(starting_point, val);
        }
        function<double(double)> grad_direct = [=](double alpha) {
            return func.get_val(starting_point.first - alpha * grad.first, starting_point.second - alpha * grad.second);
        };
        auto res = optimizer.optimize(grad_direct, 0, 10000, tol);
        starting_point = {starting_point.first - res.x_min * grad.first,
                          starting_point.second - res.x_min * grad.second};
        grad = func.get_grad(starting_point.first, starting_point.second);
        cout << starting_point.first << " " << starting_point.second << endl;
    }

}

