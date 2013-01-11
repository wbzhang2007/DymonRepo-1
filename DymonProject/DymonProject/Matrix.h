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
			Matrix(){};
			~Matrix();

			void setDimension(int rows, int cols);

			Matrix MatrixProduct(Matrix m2);
			Matrix MatrixPlus(Matrix m2);
			Matrix MatrixMinus(Matrix m2);

			Matrix operator+(Matrix &m2);
			Matrix operator-(Matrix &m2);
			Matrix operator*(Matrix &m2);
			
			double getMatrixElement(int row, int col);
			void setMatrixElement(double value, int row, int col);
			Matrix inverse();
			Matrix transpose();

			int getMatrixNumOfRows();
			int getMatrixNumOfCols();
			void setMatrixNumOfRows(int rows);
			void setMatrixNumOfCols(int cols);

			void printMatrix();

		private:
			int cols;
			int rows;
			double* _matrixEntry;


	};
}
#endif