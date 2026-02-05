#include <cmath>
#include "sfuns.h"
#include<numbers>

constexpr double PI = std::numbers::pi;
constexpr double E  = std::numbers::e;
constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

namespace sfuns {

double sqrt2() {
	return std::sqrt(2);
}

double two_to_one_fifth() {
    return std::pow(2.0, 1.0 / 5.0);
}

double e_pow_pi() {
    return std::pow(E, PI);
}

double fgamma(double x){
	if(x<0)return PI/std::sin(PI*x)/fgamma(1-x);
	if(x<9)return fgamma(x+1)/x;
	double lnfgamma=x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
	return std::exp(lnfgamma);
	}

// Log-gamma (positive arguments only)
double lngamma(double x){
	if(x <= 0) return NaN;
	if(x < 9) return lngamma(x+1) - std::log(x);

	return
		x*std::log(x + 1/(12*x - 1/x/10))
		- x
		+ std::log(2*PI/x)/2;
}

}//namespace sfuns

