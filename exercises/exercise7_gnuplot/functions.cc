#include "functions.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <numbers>
#include <complex>


constexpr double PI = std::numbers::pi;

namespace functions {

double erf(double x){
// single precision error function (Abramowitz and Stegun, from Wikipedia)
if(x<0) return -erf(-x);
std::vector<double> a {0.254829592,-0.284496736,1.421413741,-1.453152027,1.061405429};
double t=1/(1+0.3275911*x);
double sum=t*(a[0]+t*(a[1]+t*(a[2]+t*(a[3]+t*a[4]))));/* the right thing */
return 1-sum*std::exp(-x*x);
} 

double sgamma(double x){
if(x<0)return PI/std::sin(PI*x)/sgamma(1-x);
if(x<9)return sgamma(x+1)/x;
double lnsgamma=std::log(2*PI)/2+(x-0.5)*std::log(x)-x
    +(1.0/12)/x-(1.0/360)/(x*x*x)+(1.0/1260)/(x*x*x*x*x);
return std::exp(lnsgamma);
}

double lngamma(double x){
if(x<=0) return std::numeric_limits<double>::quiet_NaN();
if(x<9) return lngamma(x+1)-std::log(x);
return x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
}

std::complex<double> cgamma(std::complex<double> z) {

    if (z.real() < 0.5) {
        return PI / (std::sin(PI * z) * cgamma(1.0 - z));
    }

    std::complex<double> log_gamma =
        std::log(2.0 * PI) / 2.0 +
        (z - 0.5) * std::log(z) - z +
        1.0/(12.0*z) - 1.0/(360.0*z*z*z);

    return std::exp(log_gamma);
}
	


// Load data from file
std::vector<std::pair<double,double>> load_data(const std::string& filename) {

    std::vector<std::pair<double,double>> data;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << "\n";
        return data;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        double x, y;
        if (iss >> x >> y) {  // only first two columns
            data.emplace_back(x, y);
        }
    }

    return data;
}

}