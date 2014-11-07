#include "SeamCarving.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

SeamCarving::SeamCarving()
{
}

SeamCarving::SeamCarving(int numRow, int numCol)
{
	rows = numRow;
	cols = numCol;
	//picture = new int*[numRow];
	//for (int i = 0; i < numRow; i++)
	//{
	//	picture[i] = new int[numCol];
	//}
}

SeamCarving::~SeamCarving()
{
	//for (int i = 0; i < rows; i++)
	//{
	//	delete[] picture[i];
	//}
	//delete[] picture;

}

void SeamCarving::setHeaderInfo(string typ, string comnt, string maxNum)
{
	type = typ;
	comment = comnt;
	max = atoi(maxNum.c_str());
}

void SeamCarving::setDimensions(string numRow, string numCol)
{
	rows = atoi(numRow.c_str());
	cols = atoi(numCol.c_str());
	//original = new int[rows*cols];
}

int SeamCarving::pickMin(int left, int mid, int right)
{
	if ((left <= mid) && (left <= right))
	{
		return left;
	}
	else if ((mid < left) && (mid <= right))
	{
		return mid;
	}
	else
	{
		return right;
	}
}

void SeamCarving::readFile(string fileName)
{
	//string filename2 = fileName;
	ifstream myFile;
	int k = 0;
	cout << "Opening file..." << endl;
	myFile.open(fileName, ios::in);
	if (!myFile.good())
	{
		cout << "There was an error opening: " << fileName;
	}
	if (myFile.is_open())
	{
		cout << "File: " << fileName << " opened!" << endl;
		string line, type, comment, row, col, maxNum;
		string buildNum = "";
		char ch;
		getline(myFile, line);
		type = line;
		getline(myFile, line);
		comment = line;
		getline(myFile, line, ' ');
		row = line;
		getline(myFile, line, '\n');
		col = line;
		getline(myFile, line);
		maxNum = line;

		setDimensions(row, col);
		setHeaderInfo(type, comment, maxNum);
		for (int rowNum = 0; rowNum < rows; rowNum++)
		{
			bool notEnd = true;
			//int rowNumb = 0;
			int colNum = 0;
			//picture = new int*[rows];
			//for (int i = 0; i < rows; ++i)
			//{
			//	picture[i] = new int[cols];
			//}
			//original = new int[rows*cols];

			vector<int> picRow;
			picRow.reserve(cols);
			pic.reserve(rows);
			while (notEnd)
			{
				myFile.get(ch);
				if ((ch != ' ') && (ch != '\n') && (!myFile.eof()))
				{
					buildNum += ch; //add the character
				}
				else if ((ch == ' ') || (ch == '\n') || (myFile.eof()))
				{
					int num = atoi(buildNum.c_str());
					//pic[rowNum][colNum] = num;
					//original[rowNum*rows + colNum] = num;
					
					//picture[rowNum][colNum] = num;
					//cout << picture[rowNum][colNum] << " ";
					picRow.push_back(num);
					buildNum = ""; //reset the buildNum
					if ((ch != ' ') || (myFile.eof()))
					{
						notEnd = false;
					}
					if (ch == ' ')
					{
						colNum++;
					}
				}

			}
			pic.push_back(picRow);
		}
		//outputPic(); //for testing
		//cout << "0,0: " << original[0] << endl;
	}
	myFile.close();
	this->outputPic();
	this->buildEnergy();
	this->outputEnergy();
	this->buildTotalEnergy();
	this->outputTotalEnergy();
	this->carveVert();
}

void SeamCarving::outputFile(string filename)
{
	string t = ".pgm";
	filename = filename.substr(0, filename.length() - 4);
	filename += "_processed.pgm";
	ofstream myFile(filename);
	if (!myFile)
	{
		cout << "Error output file failed. Filename: " << filename << endl;
		exit(1);
	}
	else
	{
		myFile << type << "\n" << comment << "/n" << rows << " " << cols << "\n" << max << endl;

		vector< vector<int> >::const_iterator rowIt;
		vector<int>::const_iterator colIt;
		for (rowIt = pic.begin(); rowIt != pic.end(); ++rowIt)
		{
			for (colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt)
			{
				myFile << *colIt << " ";
			}
			myFile << "\n";
		}
	}
}

void SeamCarving::buildEnergy()
{
	vector<int> energyRow;
	energyRow.reserve(cols);
	energy.reserve(rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{		
			energyRow.push_back(calcEnergy(i, j));
		}
		energy.push_back(energyRow);
		energyRow.clear();
	}
}

int SeamCarving::calcEnergy(int i, int j)
{
	//e(i, j) = | v(i, j) - v(i - 1, j) | +| v(i, j) - v(i + 1, j) | +| v(i, j) - v(i, j - 1) | +| v(i, j) - v(i, j + 1) | ,
	int num = 0;
	if ((i - 1) >= 0) {
		num = abs(pic[i][j] - pic[i - 1][j]);
	}
	if ((i + 1) < rows) {
		num += abs(pic[i][j] - pic[i + 1][j]);
	}
	if ((j - 1) >= 0) {
		num += abs(pic[i][j] - pic[i][j - 1]);
	}
	if ((j + 1) < cols) {
		num += abs(pic[i][j] - pic[i][j + 1]);
	}
	return num;
	return 0; //DELETE
}

void SeamCarving::buildTotalEnergy()
{
	vector<int> energyRow;
	energyRow.reserve(cols);
	totalEnergy.reserve(rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			energyRow.push_back(calcTotalEnergy(i, j));
		}
		totalEnergy.push_back(energyRow);
		energyRow.clear();
	}
}

int SeamCarving::calcTotalEnergy(int i, int j)
{
	//M(i,j) = e(i,j)+min(M(i-1,j-1),M(i-1,j),M(i-1,j+1)
	int num = energy[i][j];
	int left, mid, right;
	if ((i - 1) > -1)
	{
		//Determine left/mid/right nodes that are a level above this
		mid = totalEnergy[i - 1][j];
		if ((j - 1) > -1)
		{
			left = totalEnergy[i - 1][j - 1];
		}
		else
		{
			left = mid*mid;
		}
		if ((j + 1) < cols)
		{
			right = totalEnergy[i - 1][j + 1];
		}
		else
		{
			right = mid*mid;
		}

		//Pic the minimum from left/mid/right, or the leftmost if two values are equal
		if ((left <= mid) && (left <= right))
		{
			return num + left;
		}
		else if ((mid < left) && (mid <= right))
		{
			return num + mid;
		}
		else
		{
			return num + right;
		}
		//return num + pickMin(left, mid, right);
	}
	else
	{ //the row above does not exist
		return num;
	}
}

void SeamCarving::carveVert()
{ //start from the lowest row and go up
	//Find minimum in last row
	int smallest = totalEnergy[rows - 1][0];
	int position = 0;
	for (int i = 0; i < cols; i++)
	{
		if (smallest > totalEnergy[rows - 1][i])
		{
			position = i;
			smallest = totalEnergy[rows - 1][i];
		}
	}
	cout << "Smallest in last row: " << smallest << "Position: " << position << endl; //For testing
	int backwardsIt = rows - 1;
	for (int i = rows - 1; i > -1; i--) //top row wont do this
	{
		position = this->removeVert(i, position);
	}
	//Building the new picture
	vector< vector<int> > temp;
	vector<int> tempRow;
	temp.reserve(rows);
	tempRow.reserve(cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int num = pic[i][j];
			if (num != -5)
			{
				tempRow.push_back(num);
			}
		}
		temp.push_back(tempRow);
		tempRow.clear();
	}
	pic.clear(); //We have a new picture now, clear everything
	energy.clear();
	totalEnergy.clear();
	pic = temp;
	cols--;
	cout << "We are reborn!!! pic: " << endl;
	this->outputPic();
	this->buildEnergy();
	this->outputEnergy();
	this->buildTotalEnergy();
	this->outputTotalEnergy();
}

int SeamCarving::removeVert(int i, int j)
{
	pic[i][j] = -5; //-5 to be re-written later in carveVert() through deletion
	if (i == 0)
	{
		return -1;
	}
	//Determine what nodes exist
	int left, mid, right;
	mid = totalEnergy[i - 1][j];
	if ((j - 1) > -1)
	{
		left = totalEnergy[i - 1][j - 1];
	}
	else
	{
		left = mid*mid;
	}
	if ((j + 1) < cols)
	{
		right = totalEnergy[i - 1][j + 1];
	}
	else
	{
		right = mid*mid;
	}

	if ((left <= mid) && (left <= right))
	{
		return j - 1;
	}
	else if ((mid < left) && (mid <= right))
	{
		return j;
	}
	else
	{
		return j + 1;
	}
	//totalEnergy.swap()
}

void SeamCarving::carveHorz()
{ //Start from the leftmost column and go to the right

}

void SeamCarving::outputPic()
{
	cout << "Picture's colors: \n";
	vector< vector<int> >::const_iterator rowIt;
	vector<int>::const_iterator colIt;
	for (rowIt = pic.begin(); rowIt != pic.end(); ++rowIt)
	{
		for (colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt)
		{
			cout << *colIt << " ";
		}
		cout << "\n";
	}

	//cout << "Picture's colors as array: \n";
	//for (int i = 0; i < rows; ++i)
	//{
	//	for (int j = 0; j < cols; ++j)
	//	{
	//		//cout << *(*(picture+i)+j) << " ";
	//		//cout << picture[i][j] << " ";
	//		cout << original[i*rows + cols] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << "Random: " << picture[4][0];
}

void SeamCarving::outputEnergy()
{
	cout << "Energy: \n";
	vector< vector<int> >::const_iterator rowIt;
	vector<int>::const_iterator colIt;
	for (rowIt = energy.begin(); rowIt != energy.end(); ++rowIt)
	{
		for (colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt)
		{
			cout << *colIt << " ";
		}
		cout << "\n";
	}
}

void SeamCarving::outputTotalEnergy()
{
	cout << "TotalEnergy: \n";
	vector< vector<int> >::const_iterator rowIt;
	vector<int>::const_iterator colIt;
	for (rowIt = totalEnergy.begin(); rowIt != totalEnergy.end(); ++rowIt)
	{
		for (colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt)
		{
			cout << *colIt << " ";
		}
		cout << "\n";
	}
}

void SeamCarvingTests()
{
	SeamCarving ex;
	ex.readFile("readtest.pgm");
	ex.outputFile("readtest.pgm");
	//ex.outputPic();
	//ex.buildEnergy();
	//ex.outputEnergy();
	//ex.buildTotalEnergy();
	//ex.outputTotalEnergy();
	//ex.carveVert();
}

int main()
{
	SeamCarvingTests();
	return 0;
}
