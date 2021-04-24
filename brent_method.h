#pragma once

#include "optimizing_method.h"


class brent_method : optimizing_method {
public:

    static bool n_eq(long double lhs, long double rhs, long double tolerance) {
        return std::abs(rhs - lhs) > tolerance;
    }

    static int sign(long double x) {
        return (x > 0 ? 1 : x < 0 ? -1 : 0);
    }

    result
    optimize(std::function<long double(long double)> target_func, long double left_bound, long double right_bound,
             long double tolerance) override {
        long double K = (3 - std::sqrt(5)) / 2;
        long double x, w, v, f_x, f_w, f_v, d, e, u, f_u, g;
        x = w = v = left_bound + K * (right_bound - left_bound);
        f_x = f_w = f_v = target_func(x);
        d = e = right_bound - left_bound;
        int count = 1;
        std::vector<iter_step> steps;
        steps.emplace_back(0, left_bound, right_bound, x, f_x);
        while (std::abs(x - (left_bound + right_bound) * 0.5l) + (right_bound - left_bound) * 0.5l >= 2 * tolerance) {
            g = e;
            e = d;
            bool acc = false;
            if (n_eq(x, w, tolerance) && n_eq(x, v, tolerance) && n_eq(v, w, tolerance) && n_eq(f_x, f_w, tolerance) &&
                n_eq(f_x, f_v, tolerance) &&
                n_eq(f_w, f_v, tolerance)) { // check if x, w, v and f_x, f_w, f_v are different
                u = w - (((f_w - f_v) * powl((w - x), 2)) - ((f_w - f_x) * powl((w - v), 2))) /
                        (2 * (((w - x) * (f_w - f_v)) - ((w - v) * (f_w - f_x))));
                if (u >= left_bound + tolerance && u <= right_bound - tolerance && std::abs(u - x) < g / 2) {
                    acc = true;
                }
            }
            if (!acc) {
                if (x < left_bound + (right_bound - left_bound) / 2) {
                    u = x + K * (right_bound - x);
                    e = right_bound - x;
                } else {
                    u = x - K * (x - left_bound);
                    e = x - left_bound;
                }
            }
            f_u = target_func(u);
            d = std::abs(u - x);
            if (f_u <= f_x) {
                if (u >= x) {
                    left_bound = x;
                } else {
                    right_bound = x;
                }
                v = w;
                w = x;
                x = u;
                f_v = f_w;
                f_w = f_x;
                f_x = f_u;
            } else {
                if (u >= x) {
                    right_bound = u;
                } else {
                    left_bound = u;
                }
                if (f_u <= f_w || w == x) {
                    v = w;
                    w = u;
                    f_v = f_w;
                    f_w = f_u;
                } else if (f_u <= f_v || v == x || v == w) {
                    v = u;
                    f_v = f_u;
                }
            }
            steps.emplace_back(count, left_bound, right_bound, u, f_u);
            count++;
        }

        return result(x, f_x, std::move(steps));
    }
};