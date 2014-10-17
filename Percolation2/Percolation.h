#pragma once
#ifndef PERCOLATION_H
#include <vector>
using namespace std;
class Percolation
{
private:
	vector< vector<bool> > grid; //building the open/closed board, closed to start
	vector<int> graph;           //building trees of parent/child relationship
	int size = 0;                //stores the size of grid, Size X Size is the 2d array
public:
	Percolation();
	Percolation(int n);			    // create N-by-N grid, with all sites blocked
	void open(int i, int j);        // open site (row i, col j) if it is not already add to the path array
	bool isOpen(int i, int j);      // is site (row i, col j) open?
	bool isFull(int i, int j);      // is site (row i, col j) full?
	bool percolates();              // does the system percolate?
	void unblock(double p);		    //Unblock cells with probability p
	void setGrid(int i, int j, char open); //When inputing a text file, sets a position in the grid to true (since all grids start filled with falses)
	void outputGrid();		        //For testing
	void outputGraph();			    //For testing
	int getParent(int i);		    //returns the HIGHEST level parent possible
	bool differ(int a, int b);      //DELETE?
	void buildGraph();              //builds the parent/child relationship graph, tries to keep the top level parents as parents for consistancy
	void setParent(int parent, int child);
	double percolationRate(double p, int n, int s); //returns the percolation rate/Number of runs through randomizing/percolates() the grids[][]
	void readFile(string fileName); //reads files and builds a grid[][] out of them for testing
	int countClusters();
	~Percolation();
};

#endif
