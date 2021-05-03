#include "utils.h"
#include "brent_method.h"

#pragma once

res conjugate_gradients(optimizable *func, double tol, vector<double> &starting_point) {
    double val = func->get_val(starting_point);
    brent_method optimizer;
    vector<double> prev_point;
    vector<double> prev_grad;
    vector<vector<double>> iters(starting_point.size());
    for (int i = 0; i < starting_point.size(); i++) {
        iters[i].push_back(starting_point[i]);
    }
    double beta;
    int cur_iter = 0;
    vector<double> grad = func->get_grad(starting_point);
    vector<double> p(grad.size());
    for (int i = 0; i < grad.size(); i++) {
        p[i] = -grad[i];
    }
    while (true) {
        if (vec_norm(p) < tol) {
            return res(std::move(starting_point), val, std::move(iters));
        }
        function<double(double)> grad_direct = [=](double alpha) {
            vector<double> x_n(starting_point.size());
            for (int i = 0; i < starting_point.size(); i++) {
                x_n[i] = starting_point[i] + alpha * p[i];
            }
            return func->get_val(x_n);
        };
        auto res = optimizer.optimize(grad_direct, 0, 10000, tol);
        prev_point = starting_point;
        for (int i = 0; i < starting_point.size(); i++) {
            starting_point[i] = starting_point[i] + res.x_min * p[i];
        }
        prev_grad = grad;
        grad = func->get_grad(starting_point);

        if (cur_iter % starting_point.size() == 0) {
            // beta = 0;
            beta = (vec_norm(func->get_grad(starting_point))) /
                   (vec_norm(func->get_grad(prev_point)));
        } else {
            beta = (vec_norm(func->get_grad(starting_point))) /
                   (vec_norm(func->get_grad(prev_point)));
        }
        for (int i = 0; i < starting_point.size(); i++) {
            p[i] = -grad[i] + beta * p[i];
        }
        for (int i = 0; i < starting_point.size(); i++) {
            iters[i].push_back(starting_point[i]);
        }
        cur_iter++;
    }
}