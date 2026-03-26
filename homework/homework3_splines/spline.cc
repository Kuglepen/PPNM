#include "spline.h"
#include <cassert>

// binary search
int binsearch(const std::vector<double>& x, double z){
    assert(z>=x[0] && z<=x[x.size()-1]);

    int i=0, j=x.size()-1;
    while(j-i>1){
        int mid=(i+j)/2;
        if(z>x[mid]) i=mid;
        else j=mid;
    }
    return i;
}

// linear interpolation
double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z){
    int i = binsearch(x,z);
    double dx = x[i+1]-x[i];
    double dy = y[i+1]-y[i];
    return y[i] + dy/dx*(z-x[i]);
}

// integral af lineær spline
double linterpInteg(const std::vector<double>& x,
                    const std::vector<double>& y,
                    double z){
    int i = binsearch(x,z);
    double sum = 0;

    // fulde intervaller
    for(int k=0; k<i; k++){
        double dx = x[k+1] - x[k];
        double dy = y[k+1] - y[k];
        sum += y[k]*dx + 0.5*dy*dx;
    }

    // sidste interval
    double dx = z - x[i];
    double slope = (y[i+1] - y[i]) / (x[i+1] - x[i]);

    sum += y[i]*dx + 0.5*slope*dx*dx;

    return sum;
}

// quadratic spline
qspline::qspline(const std::vector<double>& x,
                 const std::vector<double>& y)
    : x(x), y(y), n(x.size()), b(n-1), c(n-1)
{
    std::vector<double> p(n-1);

    // slopes
    for(int i=0;i<n-1;i++){
        p[i] = (y[i+1]-y[i])/(x[i+1]-x[i]);
    }

    c[0] = 0;

    // forward recursion
    for(int i=0;i<n-2;i++){
        c[i+1] = (p[i+1]-p[i]-c[i]*(x[i+1]-x[i]))/(x[i+2]-x[i+1]);
    }

    c[n-2] /= 2;

    // backward recursion
    for(int i=n-3;i>=0;i--){
        c[i] = (p[i+1]-p[i]-c[i+1]*(x[i+2]-x[i+1]))/(x[i+1]-x[i]);
    }

    // b
    for(int i=0;i<n-1;i++){
        b[i] = p[i] - c[i]*(x[i+1]-x[i]);
    }
}

// eval
double qspline::eval(double z){
    int i = binsearch(x,z);
    double dx = z - x[i];
    return y[i] + b[i]*dx + c[i]*dx*dx;
}

// derivative
double qspline::deriv(double z){
    int i = binsearch(x,z);
    double dx = z - x[i];
    return b[i] + 2*c[i]*dx;
}

// integral
double qspline::integ(double z){
    int i = binsearch(x,z);
    double sum = 0;

    // fulde intervaller
    for(int k=0;k<i;k++){
        double dx = x[k+1]-x[k];
        sum += y[k]*dx + b[k]*dx*dx/2 + c[k]*dx*dx*dx/3;
    }

    // sidste interval
    double dx = z - x[i];
    sum += y[i]*dx + b[i]*dx*dx/2 + c[i]*dx*dx*dx/3;

    return sum;
}

// functional part C
#include <functional>

std::function<double(double)>
make_qspline(std::vector<double> x, std::vector<double> y){

    int n = x.size();
    std::vector<double> b(n-1), c(n-1), p(n-1);

    // slopes
    for(int i=0;i<n-1;i++){
        p[i] = (y[i+1]-y[i])/(x[i+1]-x[i]);
    }

    c[0] = 0;

    for(int i=0;i<n-2;i++){
        c[i+1] = (p[i+1]-p[i]-c[i]*(x[i+1]-x[i]))/(x[i+2]-x[i+1]);
    }

    c[n-2] /= 2;

    for(int i=n-3;i>=0;i--){
        c[i] = (p[i+1]-p[i]-c[i+1]*(x[i+2]-x[i+1]))/(x[i+1]-x[i]);
    }

    for(int i=0;i<n-1;i++){
        b[i] = p[i] - c[i]*(x[i+1]-x[i]);
    }

    return [x = std::move(x),
            y = std::move(y),
            b = std::move(b),
            c = std::move(c)]
    (double z){

        int i=0, j=x.size()-1;
        while(j-i>1){
            int mid=(i+j)/2;
            if(z>x[mid]) i=mid;
            else j=mid;
        }

        double dx = z - x[i];
        return y[i] + b[i]*dx + c[i]*dx*dx;
    };
}