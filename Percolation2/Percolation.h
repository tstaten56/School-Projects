#pragma once
class Percolation
{
private:

public:
	Percolation(); 
	Percolation(int n);			  // create N-by-N grid, with all sites blocked
	void open(int i, int j);      // open site (row i, col j) if it is not already
	bool isOpen(int i, int j);    // is site (row i, col j) open?
	bool isFull(int i, int j);    // is site (row i, col j) full?
	bool percolates();            // does the system percolate?

	~Percolation();
};

