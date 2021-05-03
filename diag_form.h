#pragma once

#include <vector>
#include "optimizable.h"
#include <random>

using namespace std;

struct diag_form : optimizable {

    vector<double> matrix;

    std::function<double(vector<double>)> comp_func;
    std::function<vector<double>(vector<double>)> grad_func;

    diag_form(int n, int k) : matrix(n, 0) {
        std::mt19937 rand_engn(std::random_device{}());
        std::uniform_real_distribution dst(1., static_cast<double>(k));

        for (int i = 0; i < n; i++) {
            matrix[i] = dst(rand_engn);
        }
        matrix[0] = 1;
        matrix[n - 1] = k;
        comp_func = [=](const vector<double> &x) {
            double res = 0;
            for (int i = 0; i < n; i++) {
                res += pow(x[i], 2) * matrix[i];
            }
            return res;
        };
    }

    vector<double> get_grad(const vector<double> &x) override {
        vector<double> result(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            result[i] = 2 * matrix[i] * x[i];
        }
        return result;
    }

    [[nodiscard]] double get_val(const vector<double> &x) override {
        return comp_func(x);
    };

};