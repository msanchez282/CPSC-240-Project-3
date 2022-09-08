#include <iostream>
#include <string>
using namespace std;

// Matthew Sanchez and Alexander Gomez
//
// CPSC 240
//

// Q1 functions

int sodaPrice = 2, waterPrice = 1, sandwichTen = 3, sandwichTwelve = 5;
int numCustomers, totalBill, numDrinks, numSandwiches, sizeSandwich;
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
int score, average, numScores;

void averageStart() {
	cout << "Let's compute your score's average: " << endl;
}
void askScore() {
	cout << "Enter your score (-1) to stop: ";
	cin >> score;
}
void displayAverage() {
	cout << "Your average is: " << average;
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
		mov eax, numDrinks;		// eax = numDrinks
		cmp typeDrinks, 'S';	// compare typeDrinks to 'S'
		Jne Water;				// if typeDrinks != 'S', jump to water
		imul sodaPrice;			// if typeDrinks == 'S', multiply numDrinks by 2
		mov totalBill, eax;		// store active total in totalBill
		Jmp Sandwiches;
	Water:
		mov totalBill, eax;		// numDrinks * 1 for water is just numDrinks, so move that to active total
	Sandwiches:
		mov eax, numSandwiches; // eax == numSandwiches
		cmp sizeSandwich, 10;	// compare sizeSandwich and 10
		Jne twelveSandwich;		// If sizeSandwich != 10, jump to twelveSandwich
		imul sandwichTen;		// multiply numSandwiches by sandwichTen(price per 10 inch sandwich)
		add totalBill, eax;		// add (numSandwiches * sandwichTen) to totalBill
		Jmp display;			// jump to display
	twelveSandwich:	
		imul sandwichTwelve;	// multiply numSandwiches with price per twelve inch sandwich
		add totalBill, eax;		// add (numSandwiches * sandwichTwelve) to totalBill
	display:
		call displayBill;
		sub numCustomers, 1;	// subtract 1 from the number of customers
		cmp numCustomers, 0;	// compare the number of customers to 0
		Jne start;				// If numCustomers != 0, jump back to the start
	}

	cout << endl << endl << endl;

	// Q2

	_asm {
		call averageStart;
	start2:
		call askScore;
		cmp score, -1;		// compare score to -1
		Je endloop;			// if score == -1, jump to calculate
		inc numScores;		// add 1 to numScores
		add eax, score;		// add score to eax
		Jmp start2;			// loop back to start2
	endloop:
		cdq;				// edx:eax == added all scores
		idiv numScores;		// 
		mov average, eax;	// move quotient to average
		call displayAverage;// displayAverage
	}



	return 0;
}

