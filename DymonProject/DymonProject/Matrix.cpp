//created by Hu Kun on 10 Jan 2013
#include "Matrix.h"

using namespace utilities;
using namespace std;

Matrix::Matrix(int rows, int cols) {

	matrixEntry=new double[rows*cols];
}

Matrix::Matrix() {

}

Matrix::~Matrix() {
	delete [] matrixEntry;
}

Matrix Matrix::MatrixProduct(Matrix m1, Matrix m2) {
	Matrix mP(m1.getMatrixNumOfRows(),m2.getMatrixNumOfCols());

	double tempResult;

	for (int i=0; i<=m1.getMatrixNumOfRows()-1;i++) {
		for (int j=0;j<=m2.getMatrixNumOfCols()-1;j++) {
			tempResult=0;
			for (int k=0;k<=m2.getMatrixNumOfRows()-1;k++) {
				tempResult+=m1.getMatrixElement(m1,i*m1.getMatrixNumOfCols(),k)*m2.getMatrixElement(m2,k*m2.getMatrixNumOfCols(),j);

			}
			mP.setMatrixElement(mP,tempResult,i,j);
		}
	}
	return mP;

}

Matrix Matrix::MatrixPlus(Matrix m1, Matrix m2) {
	Matrix mPlus;
	
	return mPlus;
}


Matrix Matrix::MatrixMinus(Matrix m1, Matrix m2) {
	Matrix mMinus;

	return mMinus;
}


double Matrix::getMatrixElement(Matrix m, int row, int col) {

	return m.matrixEntry[row*m.getMatrixNumOfCols()+col];
}
			

void Matrix::setMatrixElement(Matrix m,double value, int row, int col) {
	m.matrixEntry[row*m.getMatrixNumOfCols()+col]=value;
}

Matrix Matrix::inverseMatrix(Matrix m) {
	Matrix mInv;
	 /*   for(i = 0; i < n; i++){
	        for(j = n; j < 2*n; j++){
	            if(i==(j-n))
	                matrix[i][j] = 1.0;
	            else
	                matrix[i][j] = 0.0;
			}
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i!=j){
                ratio = matrix[j][i]/matrix[i][i];
                for(k = 0; k < 2*n; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
    for(i = 0; i < n; i++){
        a = matrix[i][i];
        for(j = 0; j < 2*n; j++){
            matrix[i][j] /= a;
        }
    }*/

	return mInv;
}
			

Matrix Matrix::transposeMatrix(Matrix m) {
	Matrix mT(m.getMatrixNumOfCols(),m.getMatrixNumOfRows());
	
	for (int i=0; i<=mT.getMatrixNumOfRows()-1;i++) {
		for (int j=0;j<=mT.getMatrixNumOfCols()-1;j++) {
			mT.setMatrixElement(mT,m.getMatrixElement(m,j,i),i,j);	

		}
	}
	return mT;
}

int Matrix::getMatrixNumOfRows() {
	return rows;
}
			
int Matrix::getMatrixNumOfCols() {
	return cols;
}
			
void Matrix::setMatrixNumOfRows(int rowsValue) {
	rows=rowsValue;
}
			

void Matrix::setMatrixNumOfCols(int colsValue) {
	cols=colsValue;
}

Matrix Matrix::regress(Matrix X, Matrix Y) {
	
	Matrix tmp(X.getMatrixNumOfCols(),X.getMatrixNumOfCols());
	Matrix tmp1(X.getMatrixNumOfCols(),Y.getMatrixNumOfCols());
	tmp1=tmp1.MatrixProduct(X.transposeMatrix(X),Y);

	tmp=tmp.inverseMatrix(tmp.MatrixProduct(X.transposeMatrix(X),X));

	Matrix betas(tmp.getMatrixNumOfRows(),tmp1.getMatrixNumOfCols());

	betas=betas.MatrixProduct(tmp,tmp1);

	return betas;
}
			
void Matrix::printMatrix() {
	for (int i=0; i<=rows-1;i++) {
		for (int j=0;j<=cols-1;j++) {
			cout<<matrixEntry[i*cols+j]<<" ";
		}
		cout<<endl;
	}

}