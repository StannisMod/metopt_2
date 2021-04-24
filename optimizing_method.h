#pragma once
#include <functional>
#include <vector>

class iter_step {
public:
    long double left_bound;
    long double right_bound;
    long double calc_x;
    long double f_cal_x;
    std::optional<long double> calc_x2;
    std::optional<long double> f_calc_2;

    iter_step() = default;

    iter_step(int n, long double l, long double r, long double x, long double f_x) : number_of_computations(n),
                                                                                     left_bound(l), right_bound(r),
                                                                                     calc_x(x), f_cal_x(f_x) {}

    iter_step(int n, long double l, long double r, long double x, long double f_x, long double x_2, long double fx_2)
            : number_of_computations(n),
              left_bound(l), right_bound(r),
              calc_x(x), f_cal_x(f_x), calc_x2(x_2), f_calc_2(fx_2) {}

    int number_of_computations;
};

class result {
public:
    long double x_min = 0;
    long double f_min = 0;
    std::vector<iter_step> steps;
    result() = default;
    result(long double x, long double f, std::vector<iter_step> &&s) : x_min(x), f_min(f), steps(std::move(s)) {}
};

class optimizing_method {
    virtual result
    optimize(std::function<long double(long double)> target_func, long double left_bound, long double right_bound,
             long double tolerance) = 0;
};