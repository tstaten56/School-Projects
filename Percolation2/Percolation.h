#pragma once
#ifndef PERCOLATION_H
#include <vector>
using namespace std;
class Percolation
{
private:
	vector< vector<bool> > grid; //building the open/closed graph
	vector< vector<int> > graph; //building trees
	int size = 0;
public:
	Percolation();
	Percolation(int n);			  // create N-by-N grid, with all sites blocked
	void open(int i, int j);      // open site (row i, col j) if it is not already add to the path array
	bool isOpen(int i, int j);    // is site (row i, col j) open?
	bool isFull(int i, int j);    // is site (row i, col j) full?
	bool percolates();            // does the system percolate?
	void unblock(double p);		  //Unblock cells with probability p
	void outputGrid();
	int getParent(int i, int j);

	~Percolation();
};

#endif
