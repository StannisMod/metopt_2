#pragma once

#include "optimizing_method.h"
#include <vector>

class dichotomy_method : optimizing_method {
public:
    result
    optimize(std::function<long double(long double)> target_func, long double left_bound, long double right_bound,
             long double tolerance) override {
        long double x1, x2;
        long double delta = tolerance / 5;
        std::vector<iter_step> steps;
        int count = 0;
        while ((right_bound - left_bound) / 2 > tolerance) {
            x1 = (left_bound + right_bound - delta) / 2;
            x2 = (left_bound + right_bound + delta) / 2;
            steps.emplace_back(count, left_bound, right_bound, (left_bound + right_bound - delta) / 2,
                               target_func((left_bound + right_bound - delta) / 2),
                               (left_bound + right_bound + delta) / 2,
                               target_func((left_bound + right_bound + delta) / 2));
            count += 2; // т.к целевая функция на каждой итерации вычисляется 2 раза
            if (target_func(x1) <= target_func(x2)) {
                right_bound = x2;
            } else {
                left_bound = x1;
            }
        }
        x1 = (left_bound + right_bound - tolerance) / 2;
        x2 = (left_bound + right_bound + tolerance) / 2;
        long double f_x1 = target_func(x1);
        long double f_x2 = target_func(x2);
        if (f_x1 <= f_x2) {
            return result(x1, f_x1, std::move(steps));
        } else {
            return result(x2, f_x2, std::move(steps));
        }
    }
};