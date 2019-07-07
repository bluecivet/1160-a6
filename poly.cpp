/*
	this program simulate polynumle is give some function to operate the polynumle function
*/


#include<iostream>
#include<string>
#include<sstream>


using namespace std;

/*
	a polynomile contain the degree which is the highest degree for the funtion
	coeff is an array which represent the number for the polynomile 
	start from 0 which is the lowest degree for the funtion
*/

struct Poly
{
	int degree;
	int* coeff;
};


// the function for polynomile
Poly* readPoly();									// input poly
void outputPoly(const Poly* p, char x);				// output poly

Poly* addPoly(const Poly* a, const Poly* b);		// add two poly
Poly* multPoly(const Poly* a, const Poly* b);		// mutiply two poly
void deletePoly(Poly*& p);							// delete a poly

// helper funtion
bool checkInteger(string inout, bool zero, bool negative);	// check input
void clearArr(int arr[], int n);		// clear  an array
int checkDegree(const Poly* p);			// chck the highest degree for poly



int main()
{
	cout << "please input a" << endl;
	Poly* a = readPoly();
	outputPoly(a, 'x');
	cout << "please input b" << endl << endl;;
	Poly* b = readPoly();
	outputPoly(b, 'x');

	cout << "addition" << endl;
	Poly* c = addPoly(a, b);
	outputPoly(c, 'x');

	cout << endl;

	cout << " multiply" << endl;
	Poly* d = multPoly(a, b);
	outputPoly(d, 'x');

	deletePoly(a);
	deletePoly(b);
	deletePoly(c);
	deletePoly(d);
	cout << "end" << endl;

	return 0;
}


//-------------------------------------------------------------

Poly* readPoly()
{
	string inputDegree;
	string inputNumbers;
	int degree;
	stringstream ss;
	cin.sync_with_stdio(false);
	cout << "please input degree" << endl;
	cin >> inputDegree;

	while (!checkInteger(inputDegree,true,false))
	{
		cin.ignore(INT_MAX, '\n');
		cout << "error degree can only be positive interge" << endl;
		cin >> inputDegree;
	}

	ss << inputDegree;
	ss >> degree;
	
	int* arr = new int[degree + 1];

	cout << "please input the cofficients " << endl;

	bool validNumbers = false;
	for (int i = 0; i <= degree; i++)
	{
		while(true)  // check the inputNumbers
		{
			cin >> inputNumbers;
			validNumbers = true;
			if (!checkInteger(inputNumbers, true, true))
			{
				cout << "error cofficients can only be interge" << endl;
				validNumbers = false;
			}
				
			if (degree != 0 && i == degree)
			{
				if (inputNumbers == "0")
				{
					cout << "last term cannot be 0 if the degree cannot be 0" << endl;
					validNumbers = false;
				}		
			}
			
			if (validNumbers)
				break;
				
			cin.ignore(INT_MAX, '\n');
			clearArr(arr, degree + 1);
			i = 0;    // reset enter from begining 

		}

		cout << "i = " << i << endl;
			arr[i] = stoi(inputNumbers);
	}
	
	Poly* p = new Poly;
	p->degree = degree;
	p->coeff = arr;
	return p;
}


//---------------------------------------------------------------

bool checkInteger(string input, bool zero, bool negative)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '0' && !zero) // accept 0
			return false;

		if (input[i] == '-' && !negative)  // accept negative number
			return false;

		if ((input[i] < '0' || input[i] >'9'))
		{
			if (input[i] == '-' && i == 0)
				continue;
			else
				return false;
		}
			
	}
	return true;
}


//-------------------------------------------------------------

void clearArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = 0;
	}
}

//--------------------------------------------------------------

void outputPoly(const Poly* p, char x)
{
	for(int i = p->degree; i >= 0; i--)
	{
		if (p->coeff[i] == 0)
			continue;

		if (i != p->degree)
		{
			if (p->coeff[i] < 0)
				cout << " ";
			else if (p->coeff[i] > 0)
				cout << " + ";
		}

		
		if (i == 0)
		{
			cout << p->coeff[i];
		}
		else if (i == 1)
		{
			if (p->coeff[i] == 1)
				cout << x;
			else if (p->coeff[i] == -1)
				cout << "-" << x;
			else
				cout << p->coeff[i] << x;
		}
		else
		{
			if (p->coeff[i] == 1)
				cout << x << "^" << i;
			else if (p->coeff[i] == -1)
				cout << "-" << x << "^" << i;
			else
				cout << p->coeff[i] << x << "^" << i;
		}

	}
	cout << endl;
}


//------------------------------------------------------------

Poly* addPoly(const Poly* a, const Poly* b)
{
	double newDegree = a->degree > b->degree ? a->degree : b->degree;
	int* arr = new int[newDegree + 1];

	for (int i = 0; i <= newDegree; i++)
	{
		if (i > a->degree)
			arr[i] = b->coeff[i];
		else if (i > b->degree)
			arr[i] = a->coeff[i];
		else
			arr[i] = a->coeff[i] + b->coeff[i];
	}

	Poly* p = new Poly;
	p->degree = newDegree;
	p->coeff = arr;
	p->degree = checkDegree(p);
	return p;
}

//----------------------------------------------------------------

int checkDegree(const Poly* p)
{
	int actualDegree = p->degree;
	for (int i = p->degree; i >= 0; i--)
	{
		if (p->coeff[i] == 0)
			actualDegree--;
		else
			break;
	}
	return actualDegree;
}
//----------------------------------------------------------------

Poly* multPoly(const Poly* a, const Poly* b)
{ 
	int newDegree = a->degree + b->degree;
	int* arr = new int[newDegree + 1];
	clearArr(arr, newDegree + 1);

	int k = 0;
	for (int i = 0; i <= a->degree; i++)
	{
		k = i;
		for (int j = 0; j <= b->degree; j++)
		{
			arr[k] += a->coeff[i] * b->coeff[j];
			k++;
		}
	}

	Poly* p = new Poly;
	p->degree = newDegree;
	p->coeff = arr;
	return p;
}


//------------------------------------------------------------

void deletePoly(Poly*& p)
{
	if (p == NULL)
		return;

	delete [] p->coeff;

	delete p;

	p = NULL;
}

