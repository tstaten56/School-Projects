#include <string>
#include "Percolation.h"
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));
	/*
		yourProgram.exe p n s // p - percolation probability; n - # of runs; s – board size; 
		// your program should output percolation rate
		yourProgram.exe fname.txt // the game board setting is saved in the file named fname.txt 
		//click here for a sample input. 1 stands for open site; 0 for closed site.
		// your program should output the number of clusters on the board
	*/
	if ((argc == 1) || (argc == 3) || (argc > 4))
	{
		cout << "Wrong input format!" << endl;
		exit(1);
	}
	if (argc == 4)
	{
		double p;
		int s, n;
		p = atof(argv[1]); //percolation probability
		n = atoi(argv[2]); //n # of runs
		s = atoi(argv[3]); // s - board size
		Percolation g;
		cout << "p: " << p << ", n: " << n << ", s: " << s << endl;
		cout << "Percolation rate: " << g.percolationRate(p, n, s) << endl;
	}
	if (argc == 2)  //yourprogram.exe fname.txt   //game board setting is saved in the file named fname.txt   
	{				//Program should output the number of clusters on the board
		string fileName = argv[1];
	    Percolation g;
		g.readFile(fileName);
	}
	return 0;
}

