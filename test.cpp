#include <iostream>

#include "include/config_default.h"
#include "include/dfmatrix.h"

using namespace std;

DFMatrix test(){
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



	DFMatrix mat1(1,3);
	mat1={2,2,3};
	DFMatrix mat2(1,3);
	mat2={3,2,2};
	cout << mat1.cross(mat2);

	DFMatrix m3(3,3);
	m3 = {2,3,5,1,6,3,7,2,8};
	cout << m3;
	cout << m3.t();

	DFMatrix m4(2,3);
	m4 = {2,3,4,2,5,4};
	DFMatrix m5(3,2);
	m5 = {3,5,4,6,2,6};
	cout << m4*m5;

	DFMatrix m6(2,2);
	m6 = { 3,2,52,4 };
	DFMatrix m7(2,2);
	m7 = {2,6,3,8};
	cout << m6-m7;

	//cout << mat2;
	//cout << mat2.t();
	
	return mat1;
}

int main(int argc, char* argv[]){
	DFMatrix mat = test();
	
	system("pause");
	return 0;
}
