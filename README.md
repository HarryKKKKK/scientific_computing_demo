# scientific_computing_demo

## Numerical Schemes for 1D Hyperbolic PDEs

This project provides a simple framework to **test, compare, and visualize numerical methods** for solving 1D conservation laws.  
It includes implementations of both **finite difference** and **finite volume** schemes and supports multiple initial conditions and flux functions.

### Step 1 — compile
g++ finite_difference.cpp -o finite_difference

### Step 2 — run with sine IC + forward difference
./finite_difference 0 0

### Step 3 — visualize
gnuplot -c plot_advection_mode.plt sine_forward

## cpp_practicals

This directory contains code from C++ practical sessions, including: ode solvers, array practice, matrix, etc.

## parallization

This directory contains MPI-based parallel programming exercises, including: approximating quadrature and distributed matrix operation.
