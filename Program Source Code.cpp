#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

//************
// CONSTANTS *
//************

//num of states
const int STATES = 14;

//num of years
const int YEARS = 10;

//pointer declaration for later use to point at "output.txt"
fstream* out;

//constant array containing values of years
const int years[YEARS] = { 2006, 2007, 2008, 2009, 2010,
						   2011, 2012, 2013, 2014, 2015 };

//indexing variables used in loops
int i, j; 

//***********************
// FUNCTIONS AND STRUCT *
//***********************

struct dataAcc
{
	int numAcc[YEARS] = {}; // number of road accidents from 2006-2015

	string state;

	float avg = 0.0; // avg number of road accidents from 2006-2015
};

//function to calculate the average of accident numbers
//*requires 1 function call per state*
float cal_Avg(int arrayAcc[], int size)//put array here
{
	
	float sum = 0,
		   avg = 0;

	for (j = 0; j < size; j++)
	{
		sum += arrayAcc[j];
	}

	avg = sum / size;

	return avg;
}

//to display lines using 98 characters of ‘-’ in the output file using a loop
void displayLine()
{
	*out << endl;

	for (int i = 0; i < 98; i++)
	{
		*out << "-";

	}

	*out << endl;
}

//to find and display the highest number among road accidents,
//and display year and state of incidence of the hgihest number
void find_HighLow(dataAcc stateList[], int size)
{
	int incidenceYear = 0,
		largest = 0;

	string state;

	for (j = 0; j < STATES; j++)
	{
		for (i = 0; i < YEARS; i++)
		{
			if (stateList[j].numAcc[i] > largest)
			{
				largest = stateList[j].numAcc[i];

				incidenceYear = years[i];

				state = stateList[j].state;

			}

		}
	}

	displayLine();

	*out << "The highest number of road accidents = " << largest << " at " << state << " in " << incidenceYear;

	displayLine();
}


//Start of program
int main()
{
	fstream infile, outfile;

	infile.open("input.txt", ios::in);

	outfile.open("output.txt", ios::out);
	
	out = & outfile;
	

	//Array for all 14 states
	dataAcc stateList[STATES];


	//Making sure infile is open
	if (infile.is_open())
	{
		/*nested for loop to insert
		number of accidents for each state from infile*/

		for (j = 0; !(infile.eof()); j++) //rows
		{
			for (i = 0; i < YEARS; i++)   //columns
			{
				infile >> stateList[j].numAcc[i];

			}

			getline(infile, stateList[j].state);

		}

	}

	else
	{
		cout << "Error. input file not found\n";

		system("pause");
		exit(EXIT_FAILURE);
	}

	//Calculating the average for each state
	for (i = 0; i < STATES; i++)
	{
		stateList[i].avg = cal_Avg(stateList[i].numAcc, YEARS);
	}


	//Now, displaying everything in output.txt

	displayLine();

	*out << right;
	
	*out << setw(10) << "State";



	*out << setw(13) << years[0];

	for (i = 1; i < YEARS; i++)
	{
		*out << setw(7) << years[i];

	}



	*out << setw(12) << "AVERAGE";

	displayLine();



	for (j = 0; j < STATES; j++)
	{
		*out << left;
		
		*out << setw(16) << stateList[j].state;;
		
		for (i = 0; i < YEARS; i++)
		{
			*out << right;
			
			*out << setw(7) << stateList[j].numAcc[i];

		}

		*out << right  << setw(12) << stateList[j].avg << endl;
	}



	find_HighLow(stateList, STATES);



	//Thanks message
	cout << right;

	cout << setw(80) << "****************************************************************\n";

	cout << setw(80) << "Operation executed successfully. Thanks for using our program <3\n";

	cout << setw(80) << "****************************************************************\n";

	system("pause");
}
