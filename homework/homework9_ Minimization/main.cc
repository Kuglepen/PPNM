#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>
#include <string>
#include "minimization.h"

using pp::vector;

struct HiggsPoint {
    double energy;
    double signal;
    double error;
};

bool is_comment_or_blank(const std::string& line){
    auto pos = line.find_first_not_of(" \t\r\n");
    return pos == std::string::npos || line[pos] == '#';
}

std::vector<HiggsPoint> read_higgs_data(std::istream& in){
    std::vector<HiggsPoint> data;
    std::string line;

    while(std::getline(in, line)){
        if(is_comment_or_blank(line)) continue;

        std::istringstream iss(line);
        HiggsPoint p;
        if(iss >> p.energy >> p.signal >> p.error)
            data.push_back(p);
    }

    return data;
}

double breit_wigner(double E, const vector& x){
    double m = x[0];
    double G = x[1];
    double A = x[2];

    if(G <= 0.0 || A <= 0.0)
        return 1e99;

    double denom = (E - m)*(E - m) + (G*G)/4.0;
    return A / denom;
}

double higgs_deviation(const vector& x, const std::vector<HiggsPoint>& data){
    if(x[1] <= 0.0 || x[2] <= 0.0)
        return 1e99;

    double D = 0.0;

    for(const auto& p : data){
        double F = breit_wigner(p.energy, x);
        double r = (F - p.signal) / p.error;
        D += r*r;
    }

    return D;
}

void write_higgs_data(const std::string& filename, const std::vector<HiggsPoint>& data){
    std::ofstream out(filename);
    for(const auto& p : data)
        out << p.energy << " " << p.signal << " " << p.error << "\n";
}

void write_higgs_fit(const std::string& filename, const vector& x){
    std::ofstream out(filename);

    for(double E = 100.0; E <= 160.0; E += 0.1)
        out << E << " " << breit_wigner(E, x) << "\n";
}

int main(){

    std::cout << "PART A: Newton\n";

    auto rosenbrock = [](vector x){
        double X = x[0];
        double Y = x[1];
        return (1 - X)*(1 - X) + 100.0 * (Y - X*X) * (Y - X*X);
    };

    auto himmelblau = [](vector x){
        double X = x[0];
        double Y = x[1];
        return (X*X + Y - 11)*(X*X + Y - 11)
             + (X + Y*Y - 7)*(X + Y*Y - 7);
    };

    vector x0 = {-1.0, 2.0};

    auto [rosen_min, rosen_steps] = pp::newton_minimize(rosenbrock, x0);
    std::cout << "Rosenbrock minimum (forward): ";
    rosen_min.print();
    std::cout << "Rosenbrock steps (forward): " << rosen_steps << "\n";

    std::vector<vector> starts = {
        { 3.1,  2.1},
        {-2.7,  3.0},
        {-3.7, -3.1},
        { 3.5, -1.8}
    };

    for(auto xstart : starts){
        auto [xmin, steps] = pp::newton_minimize(himmelblau, xstart);
        std::cout << "Himmelblau minimum (forward): ";
        xmin.print();
        std::cout << "Himmelblau steps (forward): " << steps << "\n";
    }

    std::cout << "\nPART B: Higgs fit\n";

    std::vector<HiggsPoint> data = read_higgs_data(std::cin);

    if(data.empty()){
        std::cerr << "No Higgs data read from stdin.\n";
        return 1;
    }

    write_higgs_data("higgs_points.dat", data);

    auto objective = [&](vector x){
        return higgs_deviation(x, data);
    };

    vector xfit = {126.0, 2.0, 10.0};

    auto [best, fit_steps] = pp::newton_minimize(objective, xfit, 1e-6);
    double Dmin = higgs_deviation(best, data);

    std::cout << "Best fit parameters (forward):\n";
    std::cout << "m     = " << best[0] << "\n";
    std::cout << "Gamma = " << best[1] << "\n";
    std::cout << "A     = " << best[2] << "\n";
    std::cout << "Dmin  = " << Dmin << "\n";
    std::cout << "steps = " << fit_steps << "\n";

    write_higgs_fit("higgs_fit.dat", best);

    std::cout << "\nPART C: Central differences\n";

    auto [rosen_min_c, rosen_steps_c] = pp::newton_minimize_central(rosenbrock, x0);
    std::cout << "Rosenbrock minimum (central): ";
    rosen_min_c.print();
    std::cout << "Rosenbrock steps (central): " << rosen_steps_c << "\n";

    for(auto xstart : starts){
        auto [xmin, steps] = pp::newton_minimize_central(himmelblau, xstart);
        std::cout << "Himmelblau minimum (central): ";
        xmin.print();
        std::cout << "Himmelblau steps (central): " << steps << "\n";
    }

    return 0;
}