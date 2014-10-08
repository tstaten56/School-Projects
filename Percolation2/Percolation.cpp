#include "Percolation.h"
#include <iostream>
#include <time.h>

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
	grid[i][j] = true;
}

bool Percolation::isOpen(int i, int j)
{
	if (grid[i][j] == true)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	//Function to unblock the cells based on factor of  p
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int rn = rand() % 100;
			if (rn < (p*100))
			{
				open(i, j);
			}
		}
	}
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

void OpenTests()
{ //test isOpen and Open functions
	Percolation ex1(2);
	ex1.open(0, 0);
	cout << "opened 0, 0 \n";
	ex1.outputGrid();
	cout << "isOpen should be true: " << ex1.isOpen(0, 0) << endl;
	cout << "isOpen should be false: " << ex1.isOpen(1, 0) << endl;
	cout << "opened 0, 1 \n";
	ex1.open(0, 1);
	ex1.outputGrid();
	ex1.open(1, 0);
	cout << "opened 1, 0 \n";
	ex1.outputGrid();
	ex1.open(1, 1);
	cout << "opened 1, 1 \n";
	ex1.outputGrid();

}

void UnblockTests()
{
	Percolation ex1(2);
	ex1.unblock(.5);
	cout << "p = .5 on a size 2 grid: \n";
	ex1.outputGrid();
	Percolation ex2(10);
	ex2.unblock(.3);
	cout << "p = .3 on a size 10 grid: \n";
	ex2.outputGrid();
	Percolation ex3(10);
	ex3.unblock(.5);
	cout << "p = .5 on a size 10 grid: \n";
	ex3.outputGrid();
	Percolation ex4(10);
	ex4.unblock(.59);
	cout << "p = .59 on a size 10 grid: \n";
	ex4.outputGrid();
}

void PercolationTests()
{
	//InitializeTests();
	//OpenTests(); 
	//UnblockTests();

}

int main()
{
	PercolationTests();
	return 0;
}

