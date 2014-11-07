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
	int **picture;
	int *original;
	vector< vector<int> > pic;
	vector< vector<int> > energy;
	vector< vector<int> > totalEnergy;
public:
	SeamCarving();
	SeamCarving(int numRow, int numCol);
	~SeamCarving();
	void readFile(string filename, int vertSeams, int horzSeams);
	void setHeaderInfo(string typ, string comnt, string maxNum);
	void setDimensions(string numRow, string numCol);
	void outputPic(); //displays the picture in command line for testing
	void outputEnergy(); //displays the energy in command line for testing
	void outputTotalEnergy(); //displays the totalEnergy for testing
	void buildEnergy(); //initializes energy vector
	void buildTotalEnergy(); //initializes total energy vector
	int calcEnergy(int i, int j);// calcs the energy value of a cell[i][j]
	int calcTotalEnergy(int i, int j); //calcs the total energy of a cell[i][j]
	void carveVert(); //Carve a vertical seam
	int removeVert(int i, int j); //remove the vertical seam/calc the parents for removal
	int pickMin(int a, int b, int c);
	void carveHorz(); //Carve a horizontal seam
	void removeHorz(); //remove the horizontal seam/calc the parents for removal
	void outputFile(string filename); //outputs the current picture into a new file with the same filename, but with _processed

	//void FreeDynamicArray(int** dArray)
	//{
	//	delete[] *dArray;
	//	delete[] dArray;
	//}
};
#endif
