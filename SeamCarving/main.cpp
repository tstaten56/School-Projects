#include <iostream>
#include "SeamCarving.h"
using namespace std;

int main (int argc, char *argv[])
{
	if (argc == 4)
	{
		string file;
		int vert, horz;
		file = argv[1];
		vert = atoi(argv[2]);
		horz = atoi(argv[3]);
		SeamCarving ex;
		ex.readFile(file, vert, horz);
	}
	else
	{
		cout << "Wrong input format!" << endl;
		return 1;
	}

	return 0;
}
