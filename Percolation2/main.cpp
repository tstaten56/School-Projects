//#include <string>
//#include "Percolation.h"
//#include <iostream>
//
//using namespace std;
//
//int main(int argc, char *argv[])
//{
//	/*
//		yourProgram.exe p n s // p - percolation probability; n - # of runs; s – board size; 
//		// your program should output percolation rate
//		yourProgram.exe fname.txt // the game board setting is saved in the file named fname.txt 
//		//click here for a sample input. 1 stands for open site; 0 for closed site.
//		// your program should output the number of clusters on the board
//	*/
//	string temp;
//	//temp = argv[0];
//	temp = argv[1];
//	temp = argv[2];
//	temp = argv[3];
//	//temp = argv[4];
//	if ((argc == 1) || (argc == 3) || (argc > 4))
//	{
//		cout << "Wrong input format!" << endl;
//		exit(1);
//	}
//	if (argc == 4)
//	{
//		double p;
//		int s, n;
//		p = atol(argv[1]); //percolation probability
//		n = atoi(argv[2]); //n # of runs
//		s = atoi(argv[3]); // s - board size
//
//
//		Percolation grid(s);
//		grid.unblock(p);
//	}
//	if (argc == 2)  //yourprogram.exe fname.txt   //game board setting is saved in the file named fname.txt   
//	{				//Program should output the number of clusters on the board
//
//	}
//	return 0;
//}
//
