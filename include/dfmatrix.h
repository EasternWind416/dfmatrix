#pragma once

#include <stdint.h>
#include <iostream>
#include "config_default.h"

class DFMatrix {
public:
	DFMatrix();
	DFMatrix(int rows, int cols);

	DFMatrix(const DFMatrix& m);

	~DFMatrix();

	DFMatrix& operator=(const DFMatrix& m);
	DFMatrix& operator=(std::initializer_list<double>);
	DFMatrix& operator+=(const DFMatrix& m);
	double* operator[](size_t n);
	const double* operator[](size_t n) const;
	DFMatrix& operator()(double* InputArray, size_t size);
	DFMatrix& operator()(double* InputArray, int rows, int cols);

	double at(int rows, int cols);

	DFMatrix inv();
	DFMatrix t();
	DFMatrix dot(DFMatrix& m);
	DFMatrix cross(DFMatrix& m);
	DFMatrix conv(DFMatrix& m);
	double rank();
	double tr();

	DFMatrix clone() const;

	void copyTo(DFMatrix& outputMatrix) const;

	void zeros();
	void ones();
	void eye();
	void zeros(int rows, int cols);
	void ones(int rows, int cols);
	void eye(int rows, int cols);

	void create(int rows, int cols);

	bool empty() const;
	size_t size() const;

	void release();
	int refAdd(int* addr, int delta);

	int rows, cols;
	double* data;

private:
	size_t _size;

	int* refcount;
	void initEmpty();
};

inline bool DFMatrix::empty() const {return data==nullptr;}
inline size_t DFMatrix::size() const {return rows*cols;}

inline double* DFMatrix::operator[](size_t n){return &data[n*cols];}
inline const double* DFMatrix::operator[](size_t n) const{return &data[n*cols];}

std::ostream &operator<<(std::ostream & os, const DFMatrix & item);

bool operator==(const DFMatrix& m1, const DFMatrix & m2);
bool operator!=(const DFMatrix& m1, const DFMatrix & m2);

DFMatrix operator*(DFMatrix & m1, DFMatrix & m2);
DFMatrix operator*(DFMatrix& m, double delta);
DFMatrix operator*(double delta, DFMatrix& m);

DFMatrix operator+(DFMatrix & m1, DFMatrix & m2);
DFMatrix operator+(DFMatrix& m, double delta);
DFMatrix operator+(double delta, DFMatrix& m);

DFMatrix operator-(DFMatrix & m1, DFMatrix & m2);
DFMatrix operator-(DFMatrix& m, double delta);
DFMatrix operator-(double delta, DFMatrix& m);
