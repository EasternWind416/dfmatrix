#include <iostream>

#include "include/config_default.h"
#include "include/dfmatrix.h"

using namespace std;

DFMatrix test0() {
	//DFMatrix mat1(3,2);
	//mat1.eye();
	//cout << mat1;
	//mat1.ones(5,4);
	//cout << mat1;
	//DFMatrix mat2(mat1);
	//DFMatrix mat3 = mat1;
	//mat1.eye();
	//cout << mat1;
	//DFMatrix mat2 = mat1.clone();

	//if(mat1==mat2) cout << mat2;

	//DFMatrix mat2 = {1,2,3};
	//cout << mat2;

	//double a[2] = {1,2};
	//mat2(a, sizeof(a)/sizeof(double));

	//if(mat1 == mat2)
	//	cout << "==" << endl;
	//else
	//	cout << "!=" << endl;

	DFMatrix mm1(2, 2);
	mm1.eye();
	cout << mm1;
	mm1.ones(5, 4);
	cout << mm1;
	DFMatrix mm2(mm1);
	DFMatrix mm3 = mm1;
	mm1.eye();
	cout << mm1;



	DFMatrix mat1(1, 3);
	mat1 = { 2,2,3 };
	DFMatrix mat2(1, 3);
	mat2 = { 3,2,2 };
	cout << mat1.cross(mat2);

	DFMatrix m3(3, 3);
	m3 = { 2,3,5,1,6,3,7,2,8 };
	cout << m3;
	cout << m3.t();

	DFMatrix m4(2, 3);
	m4 = { 2,3,4,2,5,4 };
	DFMatrix m5(3, 2);
	m5 = { 3,5,4,6,2,6 };
	cout << m4 * m5;

	DFMatrix m6(2, 2);
	m6 = { 3,2,52,4 };
	DFMatrix m7(2, 2);
	m7 = { 2,6,3,8 };
	cout << m6 - m7;

	DFMatrix m8(2, 2);
	m8 = { 1,2,3,4 };
	DFMatrix m9(2, 2);
	m9 = { 1,2,3,4 };
	m9 += m8;
	cout << m9 << endl;

	return mat1;
}
// test odd kernel convolution function
DFMatrix test1() {
	DFMatrix m1(5, 5);
	m1 = { 1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25 };
	DFMatrix m2(5, 5);
	m2 = {
			1,1,1,1,1,
			1,1,1,1,1,
			1,1,24,1,1,
			1,1,1,1,1,
			1,1,1,1,1 };

	DFMatrix m3(3, 3);
	m3 = {
		1,1,1,
		1,8,1,
		1,1,1 };
	DFMatrix core33(3, 3);
	core33 = {
		1,1,1,
		1,-1,1,
		1,1,1 };

	DFMatrix core55(5, 5);
	core55 = {
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,-1,1,1,
		1,1,1,1,1,
		1,1,1,1,1 };

	cout << "m1= " << endl << m1;
	cout << "m2= " << endl << m2;
	cout << "core33= " << endl << core33;
	cout << "core55= " << endl << core55;
	cout << "m1.conv(core33)= " << endl << m1.conv(core33);
	cout << "m2.conv(core33)= " << endl << m2.conv(core33);
	cout << "m1.conv(core55)= " << endl << m1.conv(core55);
	cout << "m2.conv(core55)= " << endl << m2.conv(core55);
	cout << "m3.conv(core33)= " << endl << m3.conv(core33);
	cout << "m3.conv(core55)= " << endl << m3.conv(core55);
	return m1;
}

DFMatrix test2() {
	DFMatrix m1(5, 5);
	m1 = { 1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25 };
	cout << m1 << endl;
	int delta = 2;

	DFMatrix m1_r(5, 5);
	m1_r = m1 - delta;
	cout << m1_r << endl;
	m1_r = delta - m1;
	cout << m1_r << endl;

	m1_r = m1 * delta;
	cout << m1_r << endl;
	m1_r = delta * m1;
	cout << m1_r << endl;

	m1_r = m1 + delta;
	cout << m1_r << endl;
	m1_r = delta + m1;
	cout << m1_r << endl;

	return m1;
}

// test dot function
void test3(){
	DFMatrix m1(2, 2);
	m1 = { 1,0,-1,3 };
	DFMatrix m2(2, 2);
	m2 = { 3,1,2,1 };

	cout << "m1.*m2" << endl << m1.dot(m2) << endl;
}

// test two 2d array convolution
void test_temp() {
	int arr[5][5] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };
	int kl[3][3] = { 1,1,1,1,-1,1,1,1,1 };

	int res[5][5] = { 0 };

	for (size_t i = 0; i < 5; i++) {
		for (size_t j = 0; j < 5; j++) {

			for (size_t ii = 0; ii < 3; ii++) {
				for (size_t jj = 0; jj < 3; jj++) {
					int x = i-3/2+ii, y = j-3/2+jj;
					int temp = 0;
					if (x < 0 || y < 0 || x >= 5 || y >= 5)
						temp = 0;
					else
						temp = arr[x][y];
					res[i][j] += temp * kl[ii][jj];
				}
			}
		}
	}

	for (size_t i = 0; i < 5; i++) {
		for (size_t j = 0; j < 5; j++) {
			cout << res[i][j] << ",";
		}
		cout << endl;
	}
}



int main(int argc, char* argv[]){
	test3();
	
	system("pause");
	return 0;
}
