#pragma once

#include <functional>
#include <utility>
#include "brent_method.h"
#include <limits>
#include "diag_form.h"
#include "optimizable.h"
#include "utils.h"

using namespace std;

res steepest_gradient_descent(optimizable *func, double tol, vector<double> &starting_point) {
    double val = func->get_val(starting_point);
    brent_method optimizer;
    vector<vector<double>> iters(starting_point.size());
    vector<double> grad = func->get_grad(starting_point);
    for (int i = 0; i < starting_point.size(); i++) {
        iters[i].push_back(starting_point[i]);
    }
    while (true) {
//        std::cerr << vec_norm(grad) << std::endl;
        if (vec_norm(grad) < tol) {
            return res(std::move(starting_point), val, std::move(iters));
        }
        function<double(double)> grad_direct = [=](double alpha) {
            vector<double> x_n(starting_point.size());
            for (int i = 0; i < starting_point.size(); i++) {
                x_n[i] = starting_point[i] - alpha * grad[i];
            }
            return func->get_val(x_n);
        };
        auto res = optimizer.optimize(grad_direct, 0., 10000., 1e-5);
        for (auto i = 0; i < starting_point.size(); i++) {
            starting_point[i] = starting_point[i] - res.x_min * grad[i];
        }
        grad = func->get_grad(starting_point);
        for (auto i = 0; i < starting_point.size(); i++) {
            iters[i].push_back(starting_point[i]);
        }
    }
}

