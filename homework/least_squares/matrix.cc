#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#include<ranges>
#include "matrix.h"
#define SELF (*this)
#define FOR(i,V) for(int i=0;i<V.size();i++)
#define FOR1(i,A) for(int i=0;i<A.size1();i++)
#define FOR2(j,A) for(int j=0;j<A.size2();j++)

namespace pp{

vector& vector::operator+=(const vector& other){
		FOR(i,SELF) SELF[i]+=other[i];
		//for(int i:n())SELF[i]+=other[i];
		return SELF;
		}

	vector& vector::operator-=(const vector& other){
		FOR(i,SELF) SELF[i]-=other[i];
		return SELF;
		}

	vector& vector::operator*=(double c){
		FOR(i,SELF) SELF[i]*=c;
		return SELF;
		}

	vector& vector::operator/=(double c){
		FOR(i,SELF) SELF[i]/=c;
		return SELF;
		}

	double vector::norm() const {
		double sum2=0;
		FOR(i,SELF) sum2+=SELF[i]*SELF[i];
		return std::sqrt(sum2);
	}

	void vector::print(std::string s) const {
		std::cout<<s;
//		for(auto &x : data) std::cout<<x<<" ";
		for(auto &x : data) printf("%10.3g ",x);
		std::cout<<"\n";
	}

	vector vector::map(std::function<double(double)> f) const{
		vector r(size());
		FOR(i,SELF) r.data[i]=f(data[i]);
		return r;
	}

vector operator+(vector a, const vector& b){ a+=b ; return a; }
vector operator-(vector a)                 { a*=-1; return a; }
vector operator-(vector a, const vector& b){ a-=b ; return a; }
vector operator*(vector a, const double c) { a*=c ; return a; }
vector operator*(const double c, vector a) { a*=c ; return a; }
vector operator/(vector a, const double c) { a/=c ; return a; }

bool approx
(double x, double y, double acc, double eps){
	if(std::abs(x-y) < acc) return true;
	if(std::abs(x-y) < eps*std::max(std::abs(x),std::abs(y))) return true;
	return false;
	}

bool approx
(const vector& a, const vector& b, double acc, double eps){
	if(a.size() != b.size()) return false;
	for(int i=0;i<a.size();i++)
		if(!approx(a[i],b[i],acc,eps)) return false;
	return true;
	}

	void matrix::setid(){
		assert(size1()==size2());
		for(int i=0;i<size1();i++){
			SELF[i,i]=1;
			for(int j=i+1;j<size1();j++)SELF[i,j]=SELF[j,i]=0;
			}
		}

	matrix matrix::transpose() const{
		matrix R(size2(),size1());
		FOR1(i,SELF)
		FOR2(j,SELF)
			R[j,i]=SELF[i,j];
		return R;
	}

	matrix& matrix::operator+=(const matrix& B){
		for(int i=0;i<size2();i++)SELF[i]+=B[i];
		return *this;
		}
	matrix& matrix::operator-=(const matrix& B){
		for(int i=0;i<size2();i++)SELF[i]-=B[i];
		return *this;
		}
	matrix& matrix::operator*=(const double c){
		for(int i=0;i<size2();i++)SELF[i]*=c;
		return *this;
		}
	matrix& matrix::operator/=(const double c){
		for(int i=0;i<size2();i++)SELF[i]/=c;
		return *this;
		}
//	matrix& matrix::operator*=(const matrix&){}
//	matrix  matrix::operator^(int){}

	void matrix::print(std::string s) const {
		printf("%s\n",s.c_str());
		for(int i=0;i<size1();i++){
			for(int j=0;j<size2();j++)printf("%10.3g ",SELF[i,j]);
			printf("\n");
		}
	}

matrix operator+(matrix A, const matrix& B){
	for(int i=0;i<A.size2();i++)A[i]+=B[i];
	return A;
	}

matrix operator-(matrix A, const matrix& B){
	for(int i=0;i<A.size2();i++)A[i]-=B[i];
	return A;
	}

matrix operator*(const matrix& A, const matrix& B){
	if(A.size2()!=B.size1()) throw std::invalid_argument("size mismatch");
	matrix R(A.size1(),B.size2());
	for(int k=0;k<A.size2();k++)
	for(int j=0;j<B.size2();j++) {
		double Bkj=B(k,j);
		for(int i=0;i<A.size1();i++)R[i,j]+=A(i,k)*Bkj;
		}
	return R;
	}

matrix operator*(matrix A, const double c){
	for(auto &col : A.cols) col*=c;
	return A;
	}

matrix operator*(const double c, matrix A){
	for(auto &col : A.cols) col*=c;
	return A;
	}

matrix operator/(matrix A, const double c){
	for(auto &col : A.cols) col/=c;
	return A;
	}

vector operator*(const matrix& A, const vector& v){
	vector r(A.size1());
	FOR2(j,A){
		double vj=v[j];
		FOR1(i,A) r[i] += A(i,j) * vj;
		}
	return r;
	}

}//pp