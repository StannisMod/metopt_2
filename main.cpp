#include <iostream>
#include <functional>

#include "functions.h"

void test(const string& name, const function<result(double)>& tester, double eps) {
    result res = tester(eps);
    cout << "Testing " << name << " with EPS = " << eps << endl;
    cout << "Result: " << res.x << endl;
    cout << "Iterations: " << res.iterations.size() << endl;
    for (const vec& it : res.iterations) {
        cout << it;
    }
    cout << endl;
}

void test(const string& name, const function<result(double)>& tester, int iterations) {
    double eps = 1;
    for (int i = 0; i < iterations; i++) {
        test(name, tester, eps);
        eps *= 0.1;
    }
}

int main() {
    test("gradient drop", gradientDrop, 10);
    test("fastest drop", fastestDrop, 10);
    test("conjugate gradients", conjugateGradients, 10);
    return 0;
}
