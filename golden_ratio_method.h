#pragma once

#include "optimizing_method.h"


class golden_ratio_method : optimizing_method {

public:
    result
    optimize(std::function<long double(long double)> target_func, long double left_bound, long double right_bound,
             long double tolerance) override {
        long double t = (sqrt(5) - 1) / 2;
        long double eps_n = (right_bound - left_bound) / 2;
        long double x1 = left_bound + (3 - sqrt(5)) / 2 * (right_bound - left_bound);
        long double x2 = left_bound + (sqrt(5) - 1) / 2 * (right_bound - left_bound);
        int count = 2;
        long double f_x1 = target_func(x1);
        long double f_x2 = target_func(x2);

        std::vector<iter_step> steps;
        steps.emplace_back(0, left_bound, right_bound, left_bound + (3 - sqrt(5)) / 2 * (right_bound - left_bound),
                           target_func(left_bound + (3 - sqrt(5)) / 2 * (right_bound - left_bound)),
                           left_bound + (sqrt(5) - 1) / 2 * (right_bound - left_bound),
                           target_func(left_bound + (sqrt(5) - 1) / 2 * (right_bound - left_bound)));
        while (eps_n > tolerance) {
            // step 3
            if (f_x1 <= f_x2) {
                right_bound = x2;
                x2 = x1;
                f_x2 = f_x1;
                x1 = right_bound - t * (right_bound - left_bound);
                f_x1 = target_func(x1);
                steps.emplace_back(count, left_bound, right_bound, x1,
                                   f_x1);
            } else {
                left_bound = x1;
                x1 = x2;
                f_x1 = f_x2;
                x2 = left_bound + t * (right_bound - left_bound);
                f_x2 = target_func(x2);
                steps.emplace_back(count, left_bound, right_bound, x2,
                                   f_x2);
            }
            count++;
            eps_n *= t;
        }
        // step 4
        auto x_min = (left_bound + right_bound) / 2;
        return result(x_min, target_func(x_min), std::move(steps));
    }
};