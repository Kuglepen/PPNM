#include<iostream>
#include<cmath>
#include<string>
#include"vec.h"
#include<cmath>

namespace vec_funs{

//member operators

vec& vec::operator+=(const vec& other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec& vec::operator-=(const vec& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec& vec::operator*=(double n){
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

vec& vec::operator/=(double n){
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

// non menber

vec operator+(vec a, const vec& b){
    a += b;
    return a;
}

vec operator-(const vec& a){
    vec r = a;
    r *= -1;
    return r;
}

vec operator-(const vec& a, const vec& b){
    vec r = a;
    r -= b;
    return r;
}

vec operator*(vec a, double n){
    a *= n;
    return a;
}

vec operator*(double n, const vec& a){
    vec r = a;
    r *= n;
    return r;
}

vec operator/(vec a, double n){
    a /= n;
    return a;
}

// approx

bool approx(double a,double b,double acc,double eps){
    if(std::fabs(a-b)<acc)return true;
    if(std::fabs(a-b)<eps*(std::fabs(a)+std::fabs(b)))return true;
    return false;
}

bool approx(const vec& u, const vec& v, double acc, double eps){
    if(!approx(u.x,v.x,acc,eps))return false;
    if(!approx(u.y,v.y,acc,eps))return false;
    if(!approx(u.z,v.z,acc,eps))return false;
    return true;
}

// print

std::ostream& operator<<(std::ostream& os, const vec& v){
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    return os;
}

void vec::print(const std::string& s) const {
    std::cout << s << x << " " << y << " " << z << std::endl;
}


}//namespace vec_funs

