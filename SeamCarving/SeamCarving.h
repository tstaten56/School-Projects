#pragma once
#ifndef SEAMCARVING_H
#include <vector>
using namespace std;

class SeamCarving
{
private:
	int rows = 0;
	int cols = 0;
	string type;
	string comment;
	int max;
	int **image;
	int **energy;
	vector<int> pic;
public:
	SeamCarving();
	SeamCarving(int numRow, int numCol);
	~SeamCarving();
	void readFile(string filename, int vertSeams, int horzSeams);
	void setHeaderInfo(string typ, string comnt, string maxNum);
	void setDimensions(string numRow, string numCol);
	void outputPic(); //displays the picture in command line for testing
	void buildEnergy(); //initializes energy vector
	int calcEnergy(int x, int y); //Calcs the energy of a cell
	void calcTotalVertEnergy(); //calcs the total energy vertically
	void calcTotalHorzEnergy(); //calcs the total energy horizontally
	void outputFile(string filename, int horzSeams); //outputs the current picture into a new file with the same filename, but with _processed
	void carving(int verticalSeams, int horzSeams); //calls carveVert/carveHorz a specified number of times
	void rebuildImageFromVertSeam(); //Exactly what the name says, removes the -1's from the array
	void rebuildImageFromHorzSeam(); //Not used anymore but just in case, for future
	void rotateImage();  //For horizontal seam carving
	int minimum(int a, int b); //Minimum between two numbers (trivial)
};
#endif
