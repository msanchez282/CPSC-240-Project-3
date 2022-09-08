#include <iostream>
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
		add totalBill, eax;
		Jmp display;
	twelveSandwich:
		imul sandwichTwelve;
		add totalBill, eax;
	display:
		call displayBill;
		sub numCustomers, 1;
		cmp numCustomers, 0;
		Jne start;
	}

	return 0;
}

