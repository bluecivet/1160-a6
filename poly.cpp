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


/*
	in the main function user will enter 2 Poly and later the program will show the results fo 
	addtion and mutiply of the 2 poly
*/

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

	cout << "multiply" << endl;
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
/*
  the function will let user input for a poly
  first user will need to enter a degree for the poly
  then user will need to enter the parameter for the poly 
*/

Poly* readPoly()
{
	string inputDegree;		// user input
	string inputNumbers;	// user input
	int degree;				// for converrting user input to number
	stringstream ss;		// the tool use to conver 
	cin.sync_with_stdio(false);		// fro clear up cin 

	cout << "please input degree" << endl;

	/*
		check if it is vaild input for degree
		a degree will allow non-negative number
	*/
	while (true)	// allow 0 but not allow negative
	{
		cin >> inputDegree;
		if (!checkInteger(inputDegree, true, false))
		{
			cin.ignore(INT_MAX, '\n');	// clear cin
			cout << "error degree can only be positive interge" << endl;
		}
		else
			break;
		
	}

	cin.ignore(INT_MAX, '\n');	// clear cin
	// conver string to int
	ss << inputDegree;
	ss >> degree;
	
	int* arr = new int[degree + 1];

	// input parameter for poly
	cout << "please input the cofficients " << endl;

	// check vaild number
	bool validNumbers = false;
	for (int i = 0; i <= degree; i++) // for each parameter
	{
		while(true)  // check the inputNumbers
		{
			cin >> inputNumbers;
			validNumbers = true;
			if (!checkInteger(inputNumbers, true, true)) // allow 0 and negative
			{
				cout << "error cofficients can only be interge" << endl;
				validNumbers = false;
			}
				
			if (degree != 0 && i == degree)	// if 0 check if it is 0 degree
			{
				if (inputNumbers == "0")
				{
					cout << "last term cannot be 0 if the degree cannot be 0" << endl;
					validNumbers = false;
				}		
			}
			
			if (validNumbers)
				break;
				
			cin.ignore(INT_MAX, '\n');		// clear cin
			clearArr(arr, degree + 1);		// clear array
			i = 0;    // reset enter from begining 

		}

			arr[i] = stoi(inputNumbers);
	}
	
	Poly* p = new Poly;
	p->degree = degree;
	p->coeff = arr;
	return p;
}


//---------------------------------------------------------------

/*
  the function is to check if the input if valid or not
  zero represent the input will allow user input 0
  negative represent the program accept negative numbr 
  the user will not allow input anyting other than number and '-'
  return true for number is valid false for not 
*/

bool checkInteger(string input, bool zero, bool negative)
{

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '0' && !zero) // accept 0
			return false;

		if (input[i] == '-' && !negative)  // accept negative number
			return false;

		if ((input[i] < '0' || input[i] >'9'))		// check if user enter non number chara
		{
			// if the character '-' isthe first character it may be a negative number
			if (input[i] == '-' && i == 0)  // check the first character 
				continue;
			else
				return false;
		}
			
	}
	return true;
}


//-------------------------------------------------------------
/*
	the function will set an array from 0 to n - 1 elemet to 0
	arr is te array to set
	n is set until n element
*/

void clearArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = 0;
	}
}

//--------------------------------------------------------------

/*
	the funtion will output a poly to stantard output 
	p is the poly need to ouput 
	x is the character want to represent 
*/

void outputPoly(const Poly* p, char x)
{
	if (p == NULL)
	{
		cout << "output p is null" << endl;
		return;
	}

	for(int i = p->degree; i >= 0; i--)	// for every parameter for the poly 
	{
		if (p->coeff[i] == 0 && p->degree != 0)	// if the parameter is 0 not ouput anything
			continue;

		if (i != p->degree)		// if parameter is not high degree
		{
			if (p->coeff[i] < 0)
				cout << " ";
			else if (p->coeff[i] > 0)
				cout << " + ";
		}

		
		if (i == 0)		// if the loop reach lowest degree
		{
			cout << p->coeff[i];
		}
		else if (i == 1)	// if it reach the second lowest donot oupt character x
		{
			if (p->coeff[i] == 1)
				cout << x;
			else if (p->coeff[i] == -1)
				cout << "-" << x;
			else
				cout << p->coeff[i] << x;
		}
		else	// output everything it need
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

/*
  the funtion add tow poly togerther
  a is the first poly 
  b is the second poly
  return the a new poly which represent the result
*/

Poly* addPoly(const Poly* a, const Poly* b)
{
	if (a == NULL || b == NULL)
	{
		cout << "additon has null poly" << endl;
		return NULL;
	}

	// the new degree will be the larget degree one between a and b
	double newDegree = a->degree > b->degree ? a->degree : b->degree;
	// new degree confirm the length of new array whcih sort the parameter for reselt
	int* arr = new int[newDegree + 1];

	for (int i = 0; i <= newDegree; i++)
	{
		if (i > a->degree)	// new degree larger than a degree copy the rest of b array 
			arr[i] = b->coeff[i];
		else if (i > b->degree)	// conver above
			arr[i] = a->coeff[i];
		else
			arr[i] = a->coeff[i] + b->coeff[i];	//i inside the range of a and b
	}

	Poly* p = new Poly;
	p->degree = newDegree;
	p->coeff = arr;
	p->degree = checkDegree(p);		//to confirm the new degree in case some thing is canceled
	return p;
}

//----------------------------------------------------------------

/*
  the function is to check the extact degree for poly
  p is the poly need to check
  return the actual degree for poly
*/

int checkDegree(const Poly* p)
{
	if (p == NULL)
	{
		cout << "checkDegree has null poly" << endl;
		return -1;
	}

	int actualDegree = p->degree;
	for (int i = p->degree; i > 0; i--)	// start from highest degree
	{
		if (p->coeff[i] == 0)	// if there is 0 from highest to low 
			actualDegree--;
		else		// start from highest to lowest if there is no 0 break
			break;
	}
	return actualDegree;
}
//----------------------------------------------------------------

/*
  the function multply two poly 
  a is the first poly 
  b is the second poly
  return the result poly
*/

Poly* multPoly(const Poly* a, const Poly* b)
{ 
	if (a == NULL || b == NULL)
	{
		cout << "multply has null poly" << endl;
		return NULL;
	}

	int newDegree = a->degree + b->degree;	// new degree is the sum degree of a and b
	int* arr = new int[newDegree + 1];
	clearArr(arr, newDegree + 1);

	int k = 0;	// move index for arr
	for (int i = 0; i <= a->degree; i++) // loop for a
	{
		k = i;
		for (int j = 0; j <= b->degree; j++)	// loop for b
		{
			arr[k] += a->coeff[i] * b->coeff[j];
			k++;
		}
	}

	Poly* p = new Poly;
	p->degree = newDegree;
	p->coeff = arr;
	p->degree = checkDegree(p);
	return p;
}


//------------------------------------------------------------
/*
  the function delete the poly in head
  p is the poly need to delete
*/

void deletePoly(Poly*& p)
{
	if (p == NULL)	// if p = null do nothing 
		return;	

	delete [] p->coeff;		// delete the array first 

	delete p;

	p = NULL;
}

