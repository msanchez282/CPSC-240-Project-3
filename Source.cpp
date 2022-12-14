#include <iostream>
#include <string>
using namespace std;

// Matthew Sanchez and Alexander Gomez
//
// CPSC 240
//

// Q1 functions

short sodaPrice = 2, waterPrice = 1, sandwichTen = 3, sandwichTwelve = 5;
short numCustomers, totalBill, numDrinks, numSandwiches, sizeSandwich;
char typeDrinks;
void readData() {
	cout << "How many drinks? ";
	cin >> numDrinks;
	cout << "What kind of drink(S=Soda, W = Water)?";
	cin >> typeDrinks;
	cout << "How many sandwiches?";
	cin >> numSandwiches;
	cout << "What size of sandwich(10/12 inches)?";
	cin >> sizeSandwich;
}
void displayBill() {
	cout << "Total bill is $" << totalBill << endl;
}


// Q2 functions and declarations
int score = 0, average = 0, numScores = 0;

void averageStart() {
	cout << "Let's compute your score's average: " << endl;
}
void askScore() {
	cout << "Enter your score (-1) to stop: ";
	cin >> score;
}
void displayAverage() {
	cout << "Your average is: " << average << endl;
}
void displayNumScores() {
	cout << numScores;
}



// Q3 functions and declarations

char charIn;
int capitalCounter = 0, lowerCounter = 0;
void askForSentence() {
	cout << "Enter a sentence: ";
}
void readChar() {
	charIn = cin.get();
}
void displayLetterCounts() {
	cout << "No. of uppercase letters = " << capitalCounter << endl;
	cout << "No. of lowercase letters = " << lowerCounter << endl;
}


// Q4 functions and declarations
short a, b, c, d, e, f, X, Y;
void cramerStart() {
	cout << "This program solves the system" << endl;
	cout << "		aX + bY = c" << endl;
	cout << "   	dX + eY = f" << endl;
	cout << "Enter the values of a, b, and c: ";
	cin >> a >> b >> c;
	cout << "Enter the values of d,e, and f: ";
	cin >> d >> e >> f;
}
void displayCramer() {
	cout << "X = " << X << endl;
	cout << "Y = " << Y << endl;
}

int main() {

	// Q1

	cout << "-------------------- 7-11 Convenient Store --------------------" << endl;
	cout << "Drinks" << endl;
	cout << "    Soda(S)..................................................$2" << endl;
	cout << "    Water(W).................................................$1" << endl;
	cout << "Sandwiches" << endl;
	cout << "	 10 inches................................................$3" << endl;
	cout << "	 12 inches................................................$5" << endl;

	cout << "Enter the number of customers: ";
	cin >> numCustomers;


	_asm {
	start:
		call readData;
		mov ax, numDrinks;		// ax = numDrinks
		cmp typeDrinks, 'S';	// compare typeDrinks to 'S'
		Jne Water;				// if typeDrinks != 'S', jump to water
		imul sodaPrice;			// if typeDrinks == 'S', multiply numDrinks by 2
		mov totalBill, ax;		// store active total in totalBill
		Jmp Sandwiches;
	Water:
		mov totalBill, ax;		// numDrinks * 1 for water is just numDrinks, so move that to active total
	Sandwiches:
		mov ax, numSandwiches;  // ax == numSandwiches
		cmp sizeSandwich, 10;	// compare sizeSandwich and 10
		Jne twelveSandwich;		// If sizeSandwich != 10, jump to twelveSandwich
		imul sandwichTen;		// multiply numSandwiches by sandwichTen(price per 10 inch sandwich)
		add totalBill, ax;		// add (numSandwiches * sandwichTen) to totalBill
		Jmp display;			// jump to display
	twelveSandwich:	
		imul sandwichTwelve;	// multiply numSandwiches with price per twelve inch sandwich
		add totalBill, ax;		// add (numSandwiches * sandwichTwelve) to totalBill
	display:
		call displayBill;
		sub numCustomers, 1;	// subtract 1 from the number of customers
		cmp numCustomers, 0;	// compare the number of customers to 0
		Jne start;				// If numCustomers != 0, jump back to the start
	}

	cout << endl << endl;

	// Q2

	_asm {
		call averageStart;
		mov ebx, 0;
	start2:
		call askScore;
		cmp score, -1;		// compare score to -1
		Je calculate;		// if score == -1, jump to calculate
		inc numScores;		// add 1 to numScores
		add ebx, score;		// add score to ebx
		Jmp start2;			// loop back to start2
	calculate:
		mov eax, ebx;
		cdq;				// edx:eax == added all scores
		idiv numScores;		//
		mov average, eax;	// move quotient to average
		call displayAverage;// displayAverage
		call displayNumScores;
	}
		cout << endl << endl;
	// Q3

	_asm{
		call askForSentence;
	q3start:
		call readChar;
		cmp charIn, '\n';			// if charIn == new line
		Je displayLetterCounts;		// jump to display
		cmp charIn, ' ';			// if charIn == ' '
		Je readNextChar;			// jump to readNextChar section
		cmp charIn, 65;				// if character is less than 65 (ASCII code for first capital letter)
		Jl readNextChar;			// jump to readNextChar because it's not a letter
		cmp charIn, 90;				// compare character to 90 (ASCII code for last capital letter)
		Jle isCapital;				// jump to isCapital because it is in the range (65, 90)
		cmp charIn, 97;				// compare character to 97 (ASCII code for first lower case letter)
		Jl readNextChar;			// Jump to readNextChar
		cmp charIn, 122;			// compare to 122 (ASCII code for last lower case letter)
		Jle isLowerCase;			// is a lower case number, jump to isLowerCase
		cmp charIn, 123;			// see if it's greater than all the other ASCIIs we need
		Jge readNextChar;			// not a letter so read next character

	readNextChar:
		Jmp q3start;				// jumps back to read next char
	isCapital:
		inc capitalCounter;			// increase capital counter
		Jmp q3start;				// jump to start
	isLowerCase:
		inc lowerCounter;			// increase lower counter
		Jmp q3start;				// jump to start
	displayCounts:
		call displayLetterCounts;
	} 

	// Q4
	_asm {
		call cramerStart;
		
		// calculate Y
		mov ax, b;			// ax = b
		imul d;				// ax = b * d
		mov bx, ax;			// bx = b * d
		mov ax, a;			// ax = a
		imul e;				// ax = a * e
		sub ax, bx;			// ax = (a * e) - (b * d)
		mov cx, ax;			// cx = (a * e) - (b * d)
		mov ax, c;			// ax = c
		imul d;				// ax = c * d
		mov bx, ax;			// bx = c* d
		mov ax, a;			// ax = a
		imul f;				// ax = a * f
		sub ax, bx;			// ax = (a * f) - (c * d)
		cwd;				// dx:ax = (a * f) - (c * d)
		idiv cx;			// ax = quotient, dx = remainder
		mov Y, ax;

		// Calculate X
		mov ax, b;			// ax = b
		imul d;				// ax = b * d
		mov bx, ax;			// bx = b * d
		mov ax, a;			// ax = a
		imul e;				// ax = a * e
		sub ax, bx;			// ax = (a * e) - (b * d)
		mov cx, ax;			// cx = (a * e) - (b * d)
		mov ax, b;			// ax = b
		imul f;				// ax = b * f
		mov bx, ax;			// bx = b * f
		mov ax, c;			// ax = c
		imul e;				// ax = c * e
		sub ax, bx;			// ax = (c * e) - (b * f)
		cwd;				// dx:ax = (c * e) - (b * f)
		idiv cx;			// ax = quotient, dx = remainder
		mov X, ax;

		call displayCramer;
	}

	return 0;
}

