#pragma once

#include "optimizing_method.h"
class fibonacci_method : optimizing_method {

    static long double fib(int n) { // calculates nth fibonacci number
        return std::floor((pow((1 + sqrt(5)) / 2, n) - pow((1 - sqrt(5)) / 2, n)) / sqrt(5));
    }

public:
    result
    optimize(std::function<long double(long double)> target_func, long double left_bound, long double right_bound,
             long double tolerance) override {
        int n = 0;
        while (fib(n) <= (right_bound - left_bound) / tolerance) { // supress that warning somehow
            n++;
        }
        long double lambda =
                left_bound + (fib(n - 2)) / (fib(n)) * (right_bound - left_bound);
        long double mu =
                left_bound + (fib(n - 1)) / (fib(n)) * (right_bound - left_bound);
        long double f_lambda = target_func(lambda);
        long double f_mu = target_func(mu);
        std::vector<iter_step> steps;
        steps.emplace_back(0, left_bound, right_bound,
                           left_bound + (fib(n - 2)) / (fib(n)) * (right_bound - left_bound),
                           target_func(left_bound + (fib(n - 2)) / (fib(n)) * (right_bound - left_bound)),
                           left_bound + (fib(n - 1)) / (fib(n)) * (right_bound - left_bound),
                           target_func(left_bound + (fib(n - 1)) / (fib(n)) * (right_bound - left_bound)));
        int count = 2;
        for (int k = 1; k <= n - 2; k++) {
            if (f_lambda > f_mu) {
                left_bound = lambda;
                lambda = mu;
                mu = left_bound +
                     ((fib(n - k - 1)) / (fib(n - k))) * (right_bound - left_bound);
                f_lambda = f_mu;
                f_mu = target_func(mu);
                steps.emplace_back(count, left_bound, right_bound, mu,
                                   f_mu);
            } else {
                right_bound = mu;
                mu = lambda;
                lambda = left_bound + ((fib(n - k - 2)) / (fib(n - k))) *
                                      (right_bound - left_bound);
                f_mu = f_lambda;
                f_lambda = target_func(lambda);
                steps.emplace_back(count, left_bound, right_bound, lambda,
                                   f_lambda);
            }

            count++;
        }

        long double x = (left_bound + right_bound) / 2;
        return result(x, target_func(x), std::move(steps));
    }
};