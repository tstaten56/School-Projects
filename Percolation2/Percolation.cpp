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
	//Grid is for open/closed
	for (int i = 0; i < n; i++) {
		vector<bool> row; // Create an empty row
		for (int j = 0; j < n; j++) {
			row.push_back(false); // Add an element (column) to the row
		}
		grid.push_back(row); // Add the row to the main vector
	}
	//Graph holds parent info
	//vector<int> row; //Create an empty row for open/closed
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		row.push_back(1); //Add an element (column) to the row
	//	}
	//	graph.push_back(row); //Add the row to the main vector
	//}
	for (int i = 0; i < (n * n); i++)
	{
		graph.push_back(-1); //Each node has a null parent
	}
}


Percolation::~Percolation()
{
}

void Percolation::open(int i, int j)
{
	grid[i][j] = true;
	//When this is opened we have to figure out parent nodes for surrounding nodes, and this one. so (i, j), (i,j+1), (i,j-1), (i+1,j), (i-1,j)
	//if surrounding node is also true, getParent()
}

int Percolation::getParent(int i)
{
	//Get the parent of this node, i means itself. Get the parent of the parent til we find it is its own parent
	if (graph[i] == -1)
	{

		return i;
	}
	else
	{
		int parent = getParent(graph[i]);
		graph[i] = parent;
		return parent;
	}

}

bool Percolation::differ(int a, int b)
{
	int root1 = getParent(a);
	return false;
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
	bool percolate = false;
	buildGraph();
	for (int k = 0; k < size; k++)
	{
		int parent = getParent(graph[k] + (size * (size - 1))); //Last row parents
		if (parent < size)
		{
			int mod = parent % size;
			if (grid[mod][parent - mod])
			{
				percolate = true;
				break;
			}
		}
	}
	return percolate;
}

void Percolation::buildGraph()
{
	//building the graph, an array that holds a tree having parent-child relationships
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			bool left = false;
			int num = i * size + j;  //Base position in the grid
			//Checking the Up and Left nodes, must make sure they exist first

			if (((j - 1) != -1) && ((j - 1) <= grid.size())) //left node exists
			{
				if (grid[i][j] == grid[i][j - 1])
				{
					graph[num] = getParent(num - 1);
					left = true;
				}
			}
			if (((i - 1) != -1) && ((i-1) <= grid.size())) //up node exists
			{
				if (grid[i][j] == grid[i - 1][j])
				{
					if (left)
					{ //if the two trees are both the same value we have to make sure they're connected
						if (getParent(num - size) == getParent(num - 1))
						{
							graph[num] = getParent(num - size);
						}
						else
						{
							int parent = getParent(num - 1);
							setParent(parent, getParent(num - size));
							graph[num] = parent;
						}
					}
				}
			}
		}
	}
}

void Percolation::setParent(int parent, int child)
{
	graph[child] = parent;
}

void Percolation::unblock(double p)
{
	//Function to unblock the cells based on factor of  p
	srand(time(NULL));
	srand(100); //DELETE THIS AFTER DEBUGGING
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

void Percolation::outputGraph()
{
	for (int i = 0; i < size; i++)
	{
		cout << graph[i] << " ";
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

void GetParentTests()
{
	Percolation ex1(2);
	cout << "Should be 0 1 2 3:   " << ex1.getParent(0) << " " << ex1.getParent(1) << " " << ex1.getParent(2) << " " << ex1.getParent(3) << endl;
	
	Percolation ex2(4);
	ex2.unblock(.5);
	cout << "p = .5 on size 4 grid: \n";
	ex2.outputGrid();
	ex2.percolates();
	cout << "Parent of 0: " << ex2.getParent(0) << "\nParent of 1: " << ex2.getParent(1) << "\nParent of 2: " << ex2.getParent(2);
	cout << "\nParent of 3: " << ex2.getParent(3) << "\nParent of 4: " << ex2.getParent(4) << "\nParent of 5: " << ex2.getParent(5);
	cout << "\nParent of 6: " << ex2.getParent(6) << "\nParent of 7: " << ex2.getParent(7) << "\nParent of 8: " << ex2.getParent(8);
	cout << "\nParent of 9: " << ex2.getParent(9) << "\nParent of 10: " << ex2.getParent(10) << "\nParent of 11: " << ex2.getParent(11);
	cout << "\nParent of 12: " << ex2.getParent(12) << "\nParent of 13: " << ex2.getParent(13) << "\nParent of 14: " << ex2.getParent(14);
	cout << "\nParent of 15: " << ex2.getParent(15);
}

void PercolatesTests()
{
		Percolation ex1(2);
		ex1.unblock(.5);
		ex1.outputGrid();
		cout << ex1.percolates() << endl;

		Percolation ex2(4);
		ex2.unblock(.5);
		ex2.outputGrid();
		cout << ex2.percolates() << endl;

		Percolation ex3(6);
		ex3.unblock(.6);
		ex3.outputGrid();
		cout << ex3.percolates() << endl;
}

void PercolationTests()
{
	//InitializeTests();
	//OpenTests(); 
	//UnblockTests();
	//GetParentTests();
	PercolatesTests();
}

int main()
{
	PercolationTests();
	return 0;
}

