//created by Hu Kun on 10 Jan 2013
#include <iostream>
#include <stdlib.h>
#include <math.h>

#ifndef MATRIX_H
#define MATRIX_H

namespace utilities {
	class Matrix {

		public:
			Matrix(int rows, int cols);
			Matrix();
			~Matrix();

			Matrix MatrixProduct(Matrix m1, Matrix m2);
			Matrix MatrixPlus(Matrix m1, Matrix m2);
			Matrix MatrixMinus(Matrix m1, Matrix m2);
			
			double getMatrixElement(Matrix m, int row, int col);
			void setMatrixElement(Matrix m, double value, int row, int col);
			Matrix inverseMatrix(Matrix m);
			Matrix transposeMatrix(Matrix m);

			int getMatrixNumOfRows();
			int getMatrixNumOfCols();
			void setMatrixNumOfRows(int rows);
			void setMatrixNumOfCols(int cols);

			Matrix regress(Matrix X, Matrix Y);
			void printMatrix();

		private:
			int cols;
			int rows;
			double* matrixEntry;


	};
}
#endif