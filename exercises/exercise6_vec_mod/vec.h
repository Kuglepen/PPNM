#pragma once
#include <iostream>
#include <string>
#include <cmath>

namespace vec_funs
{

template<typename T>
struct vec {
    T x, y, z;

    // constructors
    vec(T x, T y, T z) : x(x), y(y), z(z) {}
    vec() : vec(T{}, T{}, T{}) {}

    // arithmetic
    vec& operator+=(const vec& other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec& operator-=(const vec& other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec& operator*=(T n){
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

    vec& operator/=(T n){
        x /= n;
        y /= n;
        z /= n;
        return *this;
    }

    // utility
    void set(T a, T b, T c){
        x = a; y = b; z = c;
    }

    void print(const std::string& s = "") const {
        std::cout << s << x << " " << y << " " << z << std::endl;
    }

    // stream output
    friend std::ostream& operator<<(std::ostream& os, const vec& v){
        return os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    }
};

// NON-MEMBER OPERATORS

template<typename T>
vec<T> operator+(vec<T> a, const vec<T>& b){
    a += b;
    return a;
}

template<typename T>
vec<T> operator-(vec<T> a, const vec<T>& b){
    a -= b;
    return a;
}

template<typename T>
vec<T> operator-(const vec<T>& a){
    vec<T> r = a;
    r *= static_cast<T>(-1);
    return r;
}

template<typename T, typename S>
vec<T> operator*(vec<T> a, S n){
    a *= static_cast<T>(n);
    return a;
}

template<typename T, typename S>
vec<T> operator*(S n, vec<T> a){
    a *= static_cast<T>(n);
    return a;
}

template<typename T, typename S>
vec<T> operator/(vec<T> a, S n){
    a /= static_cast<T>(n);
    return a;
}

// APPROX

template<typename T>
bool approx(T a, T b, double acc, double eps){
    using std::abs;
    if(abs(a-b) < acc) return true;
    if(abs(a-b) < eps*(abs(a)+abs(b))) return true;
    return false;
}

template<typename T>
bool approx(const vec<T>& u, const vec<T>& v, double acc=1e-6, double eps=1e-6){
    return approx(u.x,v.x,acc,eps)
        && approx(u.y,v.y,acc,eps)
        && approx(u.z,v.z,acc,eps);
}

} // namespace vec_funs
