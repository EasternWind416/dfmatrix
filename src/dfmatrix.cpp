#include "../include/dfmatrix.h"

using namespace std;

void DFMatrix::initEmpty(){
	rows = cols = _size = 0;
	data = nullptr;
	refcount = nullptr;
}

void DFMatrix::create(int _rows, int _cols){
	_log_("Matrix create.");

	rows = _rows;
	cols = _cols;
	_size = rows * cols;

	release();

	data = new double[_rows * _cols];
	refcount = new int(1);
}

int DFMatrix::refAdd(int *addr, int delta){
	int temp = *addr;
	*addr += delta;
	return temp;
}

void DFMatrix::release(){
	if(refcount && refAdd(refcount, -1)==1){
		delete[] data;
		data = nullptr;
		delete refcount;
		refcount = nullptr;
		_log_("Matrix release.");
	}
}

DFMatrix::DFMatrix(){
	_log_("Matrix construct without params.");
	initEmpty();
}

DFMatrix::DFMatrix(int _rows, int _cols){
	_log_("Matrix construct without params.");
	initEmpty();
	create(_rows, _cols);
}

DFMatrix::DFMatrix(const DFMatrix& m) : rows(m.rows),cols(m.cols),data(m.data),refcount(m.refcount),_size(m._size){
	_log_("Matrix copying fucntion.");
	if(refcount) refAdd(refcount, 1);
}

void DFMatrix::zeros(){
	for(int i=0; i<_size; i++){
		data[i] = 0;
	}
}
void DFMatrix::zeros(int _rows, int _cols){
	create(_rows, _cols);
	for(int i=0; i<_size; i++)
		data[i] = 0;
}
void DFMatrix::ones(){
	for(int i=0; i<_size; i++)
		data[i] = 1;
}
void DFMatrix::ones(int _rows, int _cols){
	create(_rows, _cols);
	for(int i=0; i<_size; i++)
		data[i] = 1;
}
void DFMatrix::eye(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			if(i==j)
				data[i*cols+j] = 1;
			else
				data[i*cols+j] = 0;
		}
	}
}
void DFMatrix::eye(int _rows, int _cols){
	create(_rows, _cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			if(i==j)
				data[i*cols+j] = 1;
			else
				data[i*cols+j] = 0;
		}
	}
}

void DFMatrix::copyTo(DFMatrix& outputMatrix) const{
	outputMatrix.create(rows, cols);
	memcpy(outputMatrix.data, data, _size*sizeof(double));
}

DFMatrix DFMatrix::clone() const{
	DFMatrix m;
	copyTo(m);
	return m;
}

DFMatrix::~DFMatrix(){
	release();
}

DFMatrix& DFMatrix::operator=(const DFMatrix& m){
	_log_("Matrix assignment function.");
	if(this!=&m){
		if(m.refcount) refAdd(m.refcount, 1);
		release();

		data = m.data;
		refcount = m.refcount;
		rows = m.rows;
		cols = m.cols;
	}
	return *this;
}

DFMatrix& DFMatrix::operator=(std::initializer_list<double> li){
	if(rows!=0 && cols!=0)
		create(rows, cols);
	else
		create(1,li.size());

	auto index = li.begin();
	auto end = li.end();
	for(int i=0; i<_size; ++i,++index){
		if(index<end)
			data[i] = *index;
		else
			data[i] = 0.0f;
	}
	return *this;
}

DFMatrix& DFMatrix::operator()(double* InputArray, size_t _size){
	create(1,_size);
	for(int i=0; i<_size; ++i)
		data[i] = InputArray[i];
	return *this;
}

DFMatrix& DFMatrix::operator()(double* InputArray, int _rows, int _cols){
	create(_rows, _cols);
	for(int i=0; i<_size; ++i)
		data[i] = InputArray[i];
	return *this;
}

double DFMatrix::rank(){
	double temp = 0.0f;
	int min_m_n = rows < cols ? rows:cols;
	for(int i=0; i<min_m_n; ++i)
		for(int j=0; j<min_m_n; ++j)
			if(i==j)
				temp += data[i*cols+j];
	return temp;
}

DFMatrix DFMatrix::inv(){
	DFMatrix m(cols, rows);

	return m;
}

DFMatrix DFMatrix::t(){
	try{
		if(rows!=cols) throw;
	}
	catch(exception){
		_log_("rows!=cols");
		return DFMatrix();
	}

	DFMatrix m(cols, rows);
	for(int i=0; i<m.rows; ++i)
		for(int j=0; j<m.cols; ++j)
			m[i][j] = (*this)[j][i];
	return m;
}

DFMatrix DFMatrix::dot(DFMatrix &m){
	DFMatrix temp(3,3);

	return temp;
}

DFMatrix DFMatrix::cross(DFMatrix &m){
	try{
		if(rows!=1||cols!=3||m.rows!=1||m.cols!=3)
			throw;
	}
	catch(exception){
		_log_("matrix in wrong calculation rule.");
		return DFMatrix();
	}

	DFMatrix temp(1,3);

	temp[0][0] = data[1] * m.data[2] - data[2] * m.data[1];
	temp[0][1] = data[2] * m.data[0] - data[0] * m.data[2];
	temp[0][2] = data[0] * m.data[1] - data[1] * m.data[0];

	return temp;
}

DFMatrix DFMatrix::conv(DFMatrix& m){
	try{
		if(m.rows!=m.cols||m.rows%2==0)
			throw;
	}
	catch(exception){
		_log_("matrix in wrong calculation rule.");
		return DFMatrix();
	}

	DFMatrix temp(rows, cols);
	int depth = m.rows / 2;
	for(int i=0; i<temp.rows; ++i)
		for(int j=0; j<temp.cols; ++j)
			temp[i][j] = (*this).at(i-1,j-1)*m[0][0]+
				(*this).at(i-1,j)*m[0][j]+
				(*this).at(i-1,j+1)*m[0][2]+
				(*this).at(i,j-1)*m[1][0]+
				(*this).at(i,j)*m[1][1]+
				(*this).at(i,j+1)*m[1][2]+
				(*this).at(i+1,j-1)*m[2][0]+
				(*this).at(i+1,j)*m[2][1]+
				(*this).at(i+1,j+1)*m[2][2];
	return temp;
}

double DFMatrix::at(int _rows, int _cols){
	if(_rows<0||_cols<0||_rows>=rows||_cols>=cols)
		return 0.0;
	else
		return(*this)[_rows][_cols];
}


ostream& operator <<(ostream & os, const DFMatrix& item){
	os << '[';
	for(int i=0; i<item.rows; ++i){
		for(int j=0; j<item.cols; ++j){
			os << item.data[i*item.cols+j];
			if(item.cols !=j+1) os<<',';
		}
		if(item.rows!=i+1)
			os << ';' << endl << ' ';
		else
			os << ']' << endl;
	}
	return os;
}

bool operator==(const DFMatrix& m1, const DFMatrix& m2){
	if(m1.data==nullptr && m1.data == m2.data)
		return true;
	else if(m1.data !=nullptr){
		if(m1.data==m2.data)
			return true;
		else
			if(m1.cols==m2.cols && m1.rows==m2.rows){
				int i = 0;
				for(; i<m1.size(); ++i)
					if (m1.data[i] != m2.data[i]) break;
				if (i==m1.size())
					return true;
			}
	}
	return false;
}

bool operator!=(const DFMatrix& m1, const DFMatrix & m2){
	return !(m1==m2);
}

DFMatrix operator*(DFMatrix &m1, DFMatrix &m2){
	try{
		if(m1.cols!=m2.rows)
			throw;
	}
	catch (exception){
		_log_("matrix a's cols is not equals to matix b's rows");
		return DFMatrix();
	}
	
	DFMatrix m(m1.rows, m2.cols);
	m.zeros();

	for(int i=0; i<m.rows; ++i)
		for(int j=0; j<m.cols; ++j)
			for(int k=0; k<m1.cols; ++k)
				m[i][j] += m1[i][k] *m2[k][j];
	return m;
}

DFMatrix operator+(DFMatrix &m1, DFMatrix &m2){
	try{
		if(m1.cols!=m2.cols||m1.rows!=m2.rows)
			throw;
	}
	catch(exception){
		_log_("m1.cols!=m2.cols || m1.rows!=m2.rows");
		return DFMatrix();
	}

	DFMatrix temp(m1.rows, m2.cols);

	for(int i=0; i<temp.rows; ++i)
		for(int j=0; j<temp.cols; ++j)
			temp[i][j] = m1[i][j] + m2[i][j];
	return temp;
}

DFMatrix operator-(DFMatrix& m1, DFMatrix& m2){
	try{
		if(m1.cols!=m2.cols||m1.rows!=m2.rows)
			throw;
	}
	catch(exception){
		_log_("m1.cols!=m2.cols || m1.rows!=m2.rows");
		return DFMatrix();
	}

	DFMatrix temp(m1.rows, m1.cols);

	for(int i=0; i<temp.rows; ++i)
		for(int j=0; j<temp.cols; ++j)
			temp[i][j] = m1[i][j] - m2[i][j];
	return temp;
}





