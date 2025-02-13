#include <iostream>
#include <cmath>
#include <fstream>
#include <locale>
#include <cstdlib>

using namespace std;

double f1(double x, double y, double z) {
    return z;
}

double f2(double x, double y, double z) {
    return (2 * log(x) - 2 * y - z) / x;
}

double EulerMethod(double x0, double y0, double z0, double xn, double h, double eps, const string& filename) {
    double y1, z1, y, z, x;
    x = x0;
    y = y0;
    z = z0;
    double error_y, error_z;
    double y1_2h, z1_2h;

    ofstream final(filename);

    if (!final.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return -1;
    }

    if (eps == 0) {
        final.precision(15);
        final << x << "\t" << y << "\n";

        while (x < xn) {
            y1 = y + f1(x, y, z) * h;
            z1 = z + f2(x, y, z) * h;
            y = y1;
            z = z1;
            x += h;
            final << x << "\t" << y << "\n";
        }
    } else {
        h = (xn - x0) * eps;
        final << x << "\t" << y << "\t" << h << "\t" << eps << "\n";

        do {
            do {
                y1 = y + f1(x, y, z) * h;
                y1_2h = y + f1(x, y, z) * 2 * h;
                z1 = z + f2(x, y, z) * h;
                z1_2h = z + f2(x, y, z) * 2 * h;

                error_y = fabs(y1_2h - y1);
                error_z = fabs(z1_2h - z1);

                if (error_y > eps || error_z > eps) {
                    h *= 0.9;
                } else if (error_z < eps * 0.95 || error_y < eps * 0.95) {
                    h *= 1.1;
                }
                y = y1;
                z = z1;
            } while (error_z > eps && error_y > eps && (error_z < eps * 0.95 || error_y < eps * 0.95));

            x += h;
            final << x << "\t" << y << "\t" << h << "\t" << error_y << "\n";
        } while (x < xn);
    }

    final.close();
    return y;
}

double shoot(double x0, double y0, double z0, double xn, double fv, double h, double eps, double a1, double b1, const string& filename) {
    double x, y, z, y1, z1, theta, yl, zl;
    x = x0;
    y = y0;
    z = z0;
    theta = z0;
    yl = z0;
    int i = 0;
    double c1 = (b1 + a1) * 0.5;
    int steps = static_cast<int>((xn - x0) / h);

    ofstream final(filename);

    if (!final.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return -1;
    }

    if (eps == 0) {
        do {
            zl = EulerMethod(x0, y0, c1, xn, h, eps, filename);
            if (zl - fv > 0) {
                b1 = c1;
            } else if (zl - fv < 0) {
                a1 = c1;
            }
            c1 = (b1 + a1) * 0.5;
            i++;
        } while (i < steps);
    } else {
        do {
            zl = EulerMethod(x0, y0, c1, xn, h, eps, filename);
            if (zl - fv > 0) {
                b1 = c1;
            } else if (zl - fv < 0) {
                a1 = c1;
            }
            c1 = (b1 + a1) * 0.5;
        } while (fabs(zl - fv) > eps);
    }

    final.close();
    return zl;
}

int main() {


    double x0 = 1;
    double y0 = 0;
    double z0 = 1; // Initial condition z0
    double xn = 2;
    double fv = log(2.0); // Target value at x = xn, which is log(2)
    double h = 0.001;

    shoot(x0, y0, z0, xn, fv, 0.1, 0, 0.83, 1.21, "fixed_10.txt");
    shoot(x0, y0, z0, xn, fv, 0.01, 0, 0.83, 1.21, "fixed_100.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.1, 0.83, 1.21, "eps_e-1.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.01, 0.83, 1.21, "eps_e-2.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.001, 0.83, 1.21, "eps_e-3.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.0001, 0.83, 1.21, "eps_e-4.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.00001, 0.83, 1.21, "eps_e-5.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.000001, 0.83, 1.21, "eps_e-6.txt");
    shoot(x0, y0, z0, xn, fv, 0, 0.0000001, 0.83, 1.21, "eps_e-7.txt");

    return 0;
}
