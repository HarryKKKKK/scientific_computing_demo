#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#define PI (4.0 * atan(1.0))

enum class UInitMode {
    Sine = 0,
    Riemann = 1,
    Gaussian = 2
};
std::string modeName(UInitMode mode) {
    if (mode == UInitMode::Sine) return "sine";
    if (mode == UInitMode::Riemann) return "riemann";
    if (mode == UInitMode::Gaussian) return "gaussian";
    return "Unknown";
}
enum class MethodMode {
    Forward = 0,
    Backward = 1,
    Central = 2,
    Lax_Friedrichs = 3,
    Lax_Wendroff = 4,
    Warming_Beam = 5
};
std::string modeName(MethodMode mode) {
    if (mode == MethodMode::Forward) return "forward";
    if (mode == MethodMode::Backward) return "backward";
    if (mode == MethodMode::Central) return "central";
    if (mode == MethodMode::Lax_Friedrichs) return "lf";
    if (mode == MethodMode::Lax_Wendroff) return "lw";
    if (mode == MethodMode::Warming_Beam) return "wb";
    return "Unknown";
}

// Parameter Setting
int nPoints = 80; 
double x0 = -1.0;
double x1 = 1.0;
double tStart = 0.0;
double tStop = 1.0;
double a = 1.05;

// Quantities
double dx = (x1 - x0) / nPoints;
double dt = dx;
std::vector<double> u(nPoints+4); // +4 for ghost zones
std::vector<double> uPlus1(nPoints+4);


void init(UInitMode mode) {
    if (mode == UInitMode::Sine) {
        for (int i = 0; i < u.size(); i++) {
            double x = x0 + (i-1) * dx;
            u[i] = std::sin(2*PI*x);      // u0(x) = sin(2*pi*x)
        }
    }
    else if (mode == UInitMode::Riemann) {
        for (int i = 0; i < u.size(); i++) {
            double x = x0 + (i-1) * dx;
            if (x < 0.3 || x > 0.7) {
                u[i] = 0;
            } else {
                u[i] = 1;
            }
        }
    }
    else if (mode == UInitMode::Gaussian) {
        for (int i = 0; i < u.size(); i++) {
            double x = x0 + (i-1) * dx;
            u[i] = exp(-8 * (x*x));
        }
    }
    else {
        std::cout << "Erorr - unseen type for u" << std::endl;
    }
}

void update(MethodMode method) {
    // Periodic Condition
    u[0] = u[nPoints];
    u[1] = u[nPoints+1];
    u[nPoints+2] = u[2];
    u[nPoints+3] = u[3];

    // Forward Diff
    if (method == MethodMode::Forward) {
        for (int i = 2; i < nPoints+2; i++) {
            uPlus1[i] = u[i] - a * (dt/dx) * (u[i+1] - u[i]);
        }
    }
    if (method == MethodMode::Backward) {
        for (int i = 2; i < nPoints+2; i++) {
            uPlus1[i] = u[i] - a * (dt/dx) * (u[i] - u[i-1]);
        }
    }
    if (method == MethodMode::Central) {
        for (int i = 2; i < nPoints+2; i++) {
            uPlus1[i] = u[i] - a * (dt/(2*dx)) * (u[i+1] - u[i-1]);
        }
    }
    if (method == MethodMode::Lax_Friedrichs) {
        for (int i = 2; i < nPoints+2; i++) {
            // float C = a*(dt/dx);
            float C = 0.8;
            uPlus1[i] = (0.5 * (1+C) * u[i-1]) + (0.5 * (1-C) * u[i+1]);
        }
    }
    if (method == MethodMode::Lax_Wendroff) {
        for (int i = 2; i < nPoints+2; i++) {
            // float C = a*(dt/dx);
            float C = 0.8;
            uPlus1[i] = u[i] - 0.5 * C * (u[i+1] - u[i-1]) + 0.5 * C * C * (u[i+1] - 2.0 * u[i] + u[i-1]);
        }
    }
    if (method == MethodMode::Warming_Beam) {
        for (int i = 2; i < nPoints+2; i++) {
            // float C = a*(dt/dx);
            float C = 0.8;
            uPlus1[i] = u[i] - 0.5 * C * (3.0 * u[i] - 4.0 * u[i-1] + u[i-2]) + 0.5 * C * C * (u[i] - 2.0 * u[i-1] + u[i-2]);
        }
    }

    u = uPlus1;
}

void output(UInitMode u_mode, MethodMode m_mode, bool is_raw = false) {
    std::string filename;
    if (is_raw) {
        filename = "result/advection_" + modeName(u_mode) + "_raw" + ".dat";
    } else {
        filename = "result/advection_" + modeName(u_mode) + "_" + modeName(m_mode)  + ".dat";
    }
    std::ofstream output_file(filename);

    for (int i = 2; i < nPoints+2; i++) {
        double x = x0 + (i-1) * dx;
        output_file << x << " " << u[i] << std::endl;
    }

}

int main(int argc, char* argv[]) {
    int um = std::atoi(argv[1]);
    UInitMode mode = static_cast<UInitMode>(um);
    int mm = std::atoi(argv[2]);
    MethodMode method = static_cast<MethodMode>(mm);

    std::cout << "Calculating for " << modeName(mode) << " using " << modeName(method) << std::endl;
    init(mode);
    // output(mode, true);

    double t = tStart;
    do {
        t = t + dt;
        update(method);
    } while (t < tStop);

    output(mode, method);
    return 1;
}
