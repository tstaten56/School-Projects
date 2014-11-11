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
}

SeamCarving::~SeamCarving()
{
}

int minimum(int a, int b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
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
}

void SeamCarving::readFile(string fileName, int vertSeams, int horzSeams)
{
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
		myFile.get(ch);
		if (ch == '#')
		{
			comment = "#";
			getline(myFile, line);
			comment += line;
			getline(myFile, line, ' ');
			col = line;
		}
		else
		{
			comment = "#Created by IfranView";
			line = "";
			line += ch;
			bool notEnd = true;
			while (notEnd)
			{
				myFile.get(ch);
				if (ch != ' ')
				{
					line += ch;
				}
				else
				{
					notEnd = false;
					col = line;
				}
			}
		}
		getline(myFile, line, '\n');
		row = line;
		getline(myFile, line);
		maxNum = line;

		setDimensions(row, col);
		//Fill image with space
		image = new int*[cols];
		for (int i = 0; i < cols; i++)
		{
			image[i] = new int[rows];
		}
		setHeaderInfo(type, comment, maxNum);
		pic.reserve(rows * cols);
		for (int rowNum = 0; rowNum < rows; rowNum++)
		{
			bool notEnd = true;

			vector<int> picRow;
			for (int colNum = 0; colNum < cols; colNum++)
			{
				bool partialNum = true;
				while (partialNum)
				{
					myFile.get(ch);
					if ((ch != ' ') && (ch != '\n') && (ch !='\t') && (!myFile.eof()))
					{
						buildNum += ch; //add the character
					}
					else if ((ch == ' ') || (ch == '\t') || (ch == '\n') || (myFile.eof()))
					{
						int num = atoi(buildNum.c_str());
						partialNum = false;
						pic.push_back(num);
						buildNum = ""; //reset the buildNum
					}
				}
			}
		}
	}
	myFile.close();
	//Fill image with content stored in vector
	int picIt = 0;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			image[x][y] = pic[picIt];
			picIt++;
		}
	}
	//Testing
	//this->outputPic();
	this->carving(vertSeams, horzSeams);
	this->outputFile(fileName, horzSeams);
}

void SeamCarving::outputFile(string filename, int horzSeams)
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
		myFile << type << "\n" << comment << "\n" << rows << " " << cols << "\n" << max << endl;

		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				myFile << image[x][y] << " ";

			}
			myFile << "\n";
		}
	}
}

void SeamCarving::buildEnergy()
{
	if (energy != NULL)
	{
		for (int i = 0; i < cols - 1; i++)
		{
			delete[] energy[i];
		}
		delete[] energy;
	}
	energy = new int*[cols];
	for (int i = 0; i < cols; i++)
	{
		energy[i] = new int[rows];
	}

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			energy[x][y] = calcEnergy(x, y);
		}
	}
}

int SeamCarving::calcEnergy(int x, int y)
{
	//e(i, j) = | v(i, j) - v(i - 1, j) | +| v(i, j) - v(i + 1, j) | +| v(i, j) - v(i, j - 1) | +| v(i, j) - v(i, j + 1) | ,
	int num = 0;
	if (x != 0) { 
		num = abs(image[x][y] - image[x - 1][y]);
	}
	if ((x + 1) < cols) {
		num += abs(image[x][y] - image[x + 1][y]);
	}
	if (y != 0) {
		num += abs(image[x][y] - image[x][y - 1]);
	}
	if ((y + 1) < rows) {
		num += abs(image[x][y] - image[x][y + 1]);
	}
	return num;
}

void SeamCarving::carving(int vertSeams, int horzSeams)
{
	for (int vertSeamsLoop = 0; vertSeamsLoop < vertSeams; vertSeamsLoop++)
	{
		this->buildEnergy();
		this->calcTotalVertEnergy();
		this->rebuildImageFromVertSeam();
	}
	for (int horzSeamsLoop = 0; horzSeamsLoop < horzSeams; horzSeamsLoop++)
	{
		this->buildEnergy();
		this->calcTotalHorzEnergy();
		this->rebuildImageFromHorzSeam();
	}
}


void SeamCarving::calcTotalHorzEnergy()
{
	//Build the cumulativeHorzEnergy empty array
	int** cumulativeHorzEnergy = new int*[cols];
	for (int i = 0; i < cols; i++)
	{
		cumulativeHorzEnergy[i] = new int[rows];
	}
	//M(i,j) = e(i,j)+min(M(i-1,j-1),M(i-1,j),M(i-1,j+1)
	//Fill the cumulativeHorzEnergy array by looking at each of the right 3 parents and taking the minimum of the numbers
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			if (x == 0) //First col stays same here
			{
				cumulativeHorzEnergy[x][y] = energy[x][y];
			}
			else
			{
				int minLeft;
				if (y == 0) //Row 0, cannot go top right
				{
					minLeft = minimum(cumulativeHorzEnergy[x - 1][y + 1], cumulativeHorzEnergy[x - 1][y]);
				}
				else if (y == (rows - 1)) //Last row, cannot go bottom right
				{
					minLeft = minimum(cumulativeHorzEnergy[x - 1][y], cumulativeHorzEnergy[x - 1][y - 1]);
				}
				else
				{ //In the middle so we can go to all 3 locations
					minLeft = minimum(minimum(cumulativeHorzEnergy[x - 1][y - 1], cumulativeHorzEnergy[x - 1][y]), cumulativeHorzEnergy[x - 1][y + 1]);
				}
				cumulativeHorzEnergy[x][y] = energy[x][y] + minLeft;
			}
		}
	}
	//Find smallest position in the last col
	int smallestPosition = 0;
	for (int i = 0; i < rows; i++)
	{
		if (cumulativeHorzEnergy[cols - 1][i] < cumulativeHorzEnergy[cols - 1][smallestPosition])
		{
			smallestPosition = i;
		}
	}
	image[cols - 1][smallestPosition] = -1; //-1 Means it will be removed in the future, must find the rest of the nodes to remove

	for (int colLoop = cols - 1; colLoop > -1; colLoop--)
	{
		if (colLoop == 0)
		{
			image[0][smallestPosition] = -1;
			break;
		}
		int top = smallestPosition + 1;
		int mid = smallestPosition;
		int bot = smallestPosition - 1;

		if ((top < 0) || (top >= rows))
		{ //Top is out of bounds
			top = mid;
		}
		if ((bot < 0) || (bot >= rows))
		{ //Bot is out of bounds
			bot = mid;
		}
		int minLeft = minimum(minimum(cumulativeHorzEnergy[colLoop][top], cumulativeHorzEnergy[colLoop][mid]), cumulativeHorzEnergy[colLoop][bot]);
		if (cumulativeHorzEnergy[colLoop][top] == minLeft)
		{
			smallestPosition = top; //Top always comes first
		}
		else if (cumulativeHorzEnergy[colLoop][mid] == minLeft)
		{
			smallestPosition = mid; //Mid comes before top
		}
		else
		{
			smallestPosition = bot;
		}
		image[colLoop][smallestPosition] = -1;
	}
}

void SeamCarving::rebuildImageFromHorzSeam()
{
	pic.clear();
	pic.reserve(rows * cols);
	//Save the new image in pic, temporarily
	int e = 0;
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			if (image[x][y] != -1) {
				pic.push_back(image[x][y]);
			}
		}
	}
	int b = 0;
	//Delete the array
	for (int i = 0; i < cols; i++)
	{
		delete[] image[i];
	}
	delete[] image;
	//remove the row from the carved seam
	rows--;
	//re-allocate image
	int c = 0;
	image = new int*[cols];
	for (int i = 0; i < cols; i++)
	{
		image[i] = new int[rows];
	}
	//Rebuild image using pic
	int picIt = 0;
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			image[x][y] = pic[picIt];
			picIt++;

		}
	}
}

void SeamCarving::calcTotalVertEnergy()
{   //Build the cumulativeVertEnergy empty array
	int** cumulativeVertEnergy = new int*[cols];
	for (int i = 0; i < cols; i++)
	{
		cumulativeVertEnergy[i] = new int[rows];
	}
	//M(i,j) = e(i,j)+min(M(i-1,j-1),M(i-1,j),M(i-1,j+1)
	//Fill the cumulativeVertEnergy array by looking at each of the top 3 parents and taking the minimum of the numbers
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (y == 0) //Top row stays the same here
			{
				cumulativeVertEnergy[x][y] = energy[x][y];
			}
			else
			{
				int minAbove;
				if (x == 0) //Column 0, cannot go top left
				{
					minAbove = minimum(cumulativeVertEnergy[x + 1][y - 1], cumulativeVertEnergy[x][y - 1]);
				}
				else if (x == (cols - 1)) //Last column, cannot go top right
				{
					minAbove = minimum(cumulativeVertEnergy[x - 1][y - 1], cumulativeVertEnergy[x][y - 1]);
				}
				else
				{ //In the middle so we can go to all 3 locations
					minAbove = minimum(minimum(cumulativeVertEnergy[x - 1][y - 1], cumulativeVertEnergy[x + 1][y - 1]), cumulativeVertEnergy[x][y - 1]);
				}
				cumulativeVertEnergy[x][y] = energy[x][y] + minAbove;
			}
		}
	}
	//Find smallest position in the last row
	int smallestPosition = 0;
	for (int i = 0; i < cols; i++)
	{
		if (cumulativeVertEnergy[i][rows - 1] < cumulativeVertEnergy[smallestPosition][rows - 1])
		{
			smallestPosition = i;
		}
	}
	image[smallestPosition][rows - 1] = -1; //It will be removed in the future, must find the rest of the nodes to remove

	for (int rowLoop = rows - 1; rowLoop > -1; rowLoop--)
	{
		if (rowLoop == 0)
		{
			image[smallestPosition][0] = -1;
			break;
		}
		int right = smallestPosition + 1;
		int mid = smallestPosition;
		int left = smallestPosition - 1;

		if ((left < 0) || (left >= cols))
		{ //Left is out of bounds
			left = mid; 
		}
		if ((right < 0) || (right >= cols))
		{ //Right is out of bounds
			right = mid;
		}
		int minAbove = minimum(minimum(cumulativeVertEnergy[right][rowLoop], cumulativeVertEnergy[left][rowLoop]), cumulativeVertEnergy[mid][rowLoop]);
		if (cumulativeVertEnergy[left][rowLoop] == minAbove)
		{
			smallestPosition = left; //Left always comes first
		}
		else if (cumulativeVertEnergy[mid][rowLoop] == minAbove)
		{
			smallestPosition = mid;
		}
		else if (cumulativeVertEnergy[right][rowLoop] == minAbove)
		{
			smallestPosition = right;
		}
		image[smallestPosition][rowLoop] = -1;
	}
}

void SeamCarving::rebuildImageFromVertSeam()
{
	pic.clear();
	vector<int> picTemp;
	pic.reserve(rows*cols);
	//Save the new image in pic, temporarily
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (image[x][y] != -1) {
				pic.push_back(image[x][y]);
			}
		}
	}
	//Delete the array
	for (int i = 0; i < cols; i++)
	{
		delete[] image[i];
	}
	delete[] image;
	//remove the column
	cols--;
	//re-allocate image
	image = new int*[cols];
	for (int i = 0; i < cols; i++)
	{
		image[i] = new int[rows];
	}
	//Rebuild image using pic
	int picIt = 0;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			image[x][y] = pic[picIt];
			picIt++;
		}
	}
}

void SeamCarving::outputPic()
{
	cout << "Picture's colors as array: \n";
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			cout << image[x][y] << " ";
		}
		cout << endl;
	}
}

void SeamCarvingTests()
{
	SeamCarving ex;
	ex.readFile("bug.pgm", 0, 20);
}

int main()
{
	SeamCarvingTests();
	return 0;
}
