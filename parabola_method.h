#pragma once

#include "optimizing_method.h"
#include "iostream"

class parabola_method : optimizing_method {
    static int
    parabola_cond(long double x1, long double x2, long double x3, const std::function<long double(long double)> &f) {
        return x1 < x2 && x2 < x3 && f(x1) >= f(x2) && f(x2) <= f(x3);
    }

public:
    result
    optimize(std::function<long double(long double)> target_func, long double left_bound, long double right_bound,
             long double tolerance) override {
        int test;
        long double x1 = left_bound;
        long double x2 = (left_bound + right_bound) / 2;
        long double x3 = right_bound;

        if (!parabola_cond(x1, x2, x3, target_func)) {
            for (int i = 0; i < 1000; i++) {
                x2 = left_bound + rand() * (right_bound - left_bound);
                if (parabola_cond(x1, x2, x3, target_func)) {
                    break;
                }
            }
            if (!parabola_cond(x1, x2, x3, target_func)) {
                return result();
            }
        }

        long double x_min = 0;
        long double x_min_prev;
        int count = 4;
        int iter_count = 0;
        long double f1 = target_func(x1);
        long double f2 = target_func(x2);
        long double f3 = target_func(x3);
        std::vector<iter_step> steps;
        steps.emplace_back(0, left_bound, right_bound, x1, f1, x2, f2);
        while (true) {
            long double a1 = (f2 - f1) / (x2 - x1);
            long double a2 = ((f3 - f1) / (x3 - x1) - (f2 - f1) / (x2 - x1)) / (x3 - x2);
            x_min_prev = x_min;
            x_min = (x1 + x2 - a1 / a2) / 2; // q(min)
            long double f_min = target_func(x_min);

            // x_min propagation
            if (x1 < x_min && x_min < x2 && x2 < x3) {
                // 1
                if (f_min >= f2) {
                //    left_bound = x_min;
                //    right_bound = x3;
                    x1 = x_min;
                    f1 = f_min;
                } else {
                //    left_bound = x1;
                //    right_bound = x2;
                    x3 = x2;
                    f3 = f2;
                    x2 = x_min;
                    f2 = f_min;
                }
            } else if (x1 < x2 && x2 < x_min && x_min < x3) {
                // 2
                if (f2 >= f_min) {
               //     left_bound = x2;
               //     right_bound = x3;
                    x1 = x2;
                    f1 = f2;
                    x2 = x_min;
                    f2 = f_min;
                } else {
            //        left_bound = x1;
             //       right_bound = x_min;
                    x3 = x_min;
                    f3 = f_min;
                }
            }
            steps.emplace_back(count, left_bound, right_bound, x_min, target_func(x_min));
            iter_count++;
            count++;
            if (iter_count >= 2) {
                if (std::abs(x_min - x_min_prev) < tolerance) {
                    return result(x_min, target_func(x_min), std::move(steps));
                }
            }
        }
    }
};