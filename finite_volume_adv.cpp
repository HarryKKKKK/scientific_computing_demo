#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>

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

enum class FluxMode {
    LaxFriedrichs = 0,
    Richtmyer     = 1,
    FORCE         = 2,
    Godunov       = 3
};
std::string modeName(FluxMode mode) {
    if (mode == FluxMode::LaxFriedrichs) return "lf";
    if (mode == FluxMode::Richtmyer)     return "richt";
    if (mode == FluxMode::FORCE)         return "force";
    if (mode == FluxMode::Godunov)       return "godunov";
    return "Unknown";
}

// Parameter Setting
int nCells = 80;
double x0 = -1.0;
double x1 =  1.0;
double tStart = 0.0;
double tStop  = 1.0;
double a      = 1.05;
double CFL    = 0.8;

// Quantities
double dx = (x1 - x0) / nCells;
double dt;
std::vector<double> u(nCells+2);
std::vector<double> uPlus1(nCells+2);
std::vector<double> flux(nCells+1);

void init(UInitMode mode) {
    for (int i = 1; i <= nCells; i++) {
        double x = x0 + (i - 0.5) * dx;
        if (mode == UInitMode::Sine) {
            u[i] = std::sin(2.0 * PI * x);
        }
        else if (mode == UInitMode::Riemann) {
            if (x < 0.3 || x > 0.7) u[i] = 0.0;
            else                    u[i] = 1.0;
        }
        else if (mode == UInitMode::Gaussian) {
            u[i] = std::exp(-8.0 * x * x);
        }
    }
}


double computeTimeStep() {
    return CFL * dx / std::fabs(a);
}

double fluxLF(double uL, double uR) {
    double fL = a * uL;
    double fR = a * uR;
    return 0.5 * (fL + fR) - 0.5 * (dx / dt) * (uR - uL);
}

double fluxRichtmyer(double uL, double uR) {
    double fL = a * uL;
    double fR = a * uR;
    double uHalf = 0.5 * (uL + uR) - 0.5 * (dt/dx) * (fR - fL);
    return a * uHalf;
}

double fluxFORCE(double uL, double uR) {
    double fLF  = fluxLF(uL, uR);
    double fRIC = fluxRichtmyer(uL, uR);
    return 0.5 * (fLF + fRIC);
}

double fluxGodunov(double uL, double uR) {
    if (a > 0.0) {
        return a * uL;
    } else {
        return a * uR;
    }
}

double getFlux(double uL, double uR, FluxMode mode) {
    if (mode == FluxMode::LaxFriedrichs) return fluxLF(uL, uR);
    if (mode == FluxMode::Richtmyer) return fluxRichtmyer(uL, uR);
    if (mode == FluxMode::FORCE) return fluxFORCE(uL, uR);
    if (mode == FluxMode::Godunov) return fluxGodunov(uL, uR);
    return 0.0;
}

void update(FluxMode mode) {
    u[0] = u[1];
    u[nCells+1] = u[nCells];

    for (int i = 0; i < nCells+1; i++) {
        flux[i] = getFlux(u[i], u[i+1], mode);
    }
    for (int i = 1; i < nCells+1; i++) {
        uPlus1[i] = u[i] - (dt/dx) * (flux[i] - flux[i-1]);
    }
    u = uPlus1;
}


void output(UInitMode umode, FluxMode fmode) {
    std::string filename = "result/advection_fv_" + modeName(umode) + "_" + modeName(fmode) + ".dat";
    std::ofstream output_file(filename);

    for (int i = 1; i <= nCells; i++) {
        double x = x0 + (i - 0.5) * dx;
        output_file << x << " " << u[i] << std::endl;
    }
}

int main(int argc, char* argv[]) {
    int um = std::atoi(argv[1]);
    UInitMode mode = static_cast<UInitMode>(um);

    int fm = std::atoi(argv[2]);
    FluxMode fluxMode = static_cast<FluxMode>(fm);

    std::cout << "Calculating FV for " << modeName(mode) << " using " << modeName(fluxMode) << std::endl;

    init(mode);

    double t = tStart;
    do {
        dt = computeTimeStep();
        update(fluxMode);
        t += dt;
    } while (t < tStop);

    output(mode, fluxMode);
    return 1;
}
