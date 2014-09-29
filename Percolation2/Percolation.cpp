#include "Percolation.h"
#include <iostream>

Percolation::Percolation()
{
}

//Create N x N grid full of falses
Percolation::Percolation(int n)
{
	size = n;
	for (int i = 0; i < n; i++) {
		vector<bool> row; // Create an empty row
		for (int j = 0; j < n; j++) {
			row.push_back(false); // Add an element (column) to the row
		}
		grid.push_back(row); // Add the row to the main vector
	}
}


Percolation::~Percolation()
{
}

void Percolation::open(int i, int j)
{

}

bool Percolation::isOpen(int i, int j)
{
	return true;
}

bool Percolation::isFull(int i, int j)
{
	return true;
}

bool Percolation::percolates()
{
	return true;
}

void Percolation::unblock(double p)
{

}

void Percolation::outputGrid()
{
	vector< vector<bool> >::const_iterator row;
	vector<bool>::const_iterator col;
	for (row = grid.begin(); row != grid.end(); ++row)
	{
		for (col = row->begin(); col != row->end(); ++col)
		{
			cout << *col << " ";
		}
		cout << "\n";
	}
}

void InitializeTests()
{
	Percolation ex1(2);
	cout << "2 x 2 initialized false: \n\n";
	ex1.outputGrid();
	Percolation ex2(15);
	cout << "15 x 15 initialized false: \n\n";
	ex2.outputGrid();
	Percolation ex3(30);
	cout << "30 x 30 initialized false: \n\n";
	ex3.outputGrid();

}



void PercolationTests()
{
	//InitializeTests();
}

int main()
{
	PercolationTests();
	return 0;
}

