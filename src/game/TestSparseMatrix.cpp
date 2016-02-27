#include "SparseMatrix.hpp"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    SparseMatrix matrix(10, 10);
    matrix.insert(2, 3, 40);
    matrix.insert(3, 4, 100);

    for(int i = 0; i < 10; i++)
    {
	for(int j = 0; j < 10; j++)
	{
	    cout << matrix[i][j] << " ";
	}
	cout << endl;
    }

    return 0;
}
