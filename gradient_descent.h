#include "utils.h"
#include "optimizable.h"


#pragma once

res gradient_descent(optimizable *func, double tol, vector<double> &starting_point) {
    double alpha = 10;
    double f_x = func->get_val(starting_point);
    vector <vector<double>> iters(starting_point.size());
    for (int i = 0; i < starting_point.size(); i++) {
        iters[i].push_back(starting_point[i]);
    }
    while (true) {
        auto grad = func->get_grad(starting_point);
        if (vec_norm(grad) < tol) {
            return res(std::move(starting_point), f_x, std::move(iters));
        }
        while (true) {
            vector<double> y(starting_point.size());
            for (int i = 0; i < starting_point.size(); i++) {
                y[i] = starting_point[i] - alpha * grad[i];
            }
            auto f_y = func->get_val(y);
            if (f_y < f_x) {
                starting_point = y;
                f_x = f_y;
                break;
            } else {
                alpha = alpha / 2;
            }
        }
        for (int i = 0; i < starting_point.size(); i++) {
            iters[i].push_back(starting_point[i]);
        }
    }
}