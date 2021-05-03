#pragma once

struct optimizable {

    virtual double get_val(const std::vector<double> &x) = 0;
    virtual std::vector<double> get_grad(const std::vector<double> &x) = 0;

};