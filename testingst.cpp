#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <string.h>
#include <cstring>
#include <vector>

using namespace std;

char binary_list[501][501]; // This is the array where the byte (8 bit) arrays are stored.

void text_to_binary(const char* input) {
	int ascii; // Used to store the ASCII number of a character
	int length = strlen(input); // Find the length of the user's input
	cout << " ";

	for (int x = 0; x < length; x++)
	{ // Repeat until user's input have all been read
		// x < length because the last character is "\0"
		ascii = input[x]; // Store a character in its ASCII number

		char* binary_reverse = new char[9]; // Dynamic memory allocation
		char* binary = new char [9];

		int y = 0; // Counter used for arrays

		while (ascii != 1)
		{ // Continue until ASCII == 1
			if (ascii % 2 == 0)
			{ // if ASCII is divisible by 2
				binary_reverse[y] = '0'; // Then put a zero
			}
			else if (ascii % 2 == 1)
			{ // If not divisible by 2
				binary_reverse[y] = '1'; // Then put a 1
			}
			ascii /= 2; // Find quotient of ASCII / 2
			y++; // add 1 to y for next loop
		}
		if (ascii == 1)
		{ // When ASCII is 1, we have to add 1 to the beginning
			binary_reverse[y] = '1';
			y++;
		}
		if (y < 7)
		{ // Add zeros to the end of string if not 8 characters (1 byte)
			for (; y < 8; y++)
			{ // Add until binary_reverse[7] (8th element)
				binary_reverse[y] = 0;
			}
		}
		for (int z = 0; z < 8; z++)
		{ // Our array is reversed, put the number in the right order.
			binary[z] = binary_reverse[7 - z];
		}
		for (int i = 0; i < 9; i++){ // This will store each 8 bits in an array within the binary list.
			// This will store the 8 bits in row x and column i.
			// x is the same value as that characters position in the input char array.
			// So, if a is the second letter in the input, x = 2, and i = 0, 1, 2, 3, 4, 5, 6, 7
			binary_list[x][i] = binary[i]; // This will store the 8 bits in row x and column i.
			binary_list[x][0] = '0'; // This guarantees that the start of a new character will start with 0.
		}
		delete [] binary_reverse; // Frees data for next iteration
		delete [] binary; // Frees data for next iteration. This is important.
	}

	cout << endl;
}

int main() {
	// This is the character array for storing the input.
	// It will be passed as the argument for the text_to_binary function.
	char text[501];

	cout << "Enter text: ";
	cin >> text;

	// This will call the function and generate the binary_list
	text_to_binary(text);

	// This iterates through the finished binary_list
	// The strlen(text) is necessary so the computer doesn't iterate through 501 array slots.
	for (int i = 0; i < strlen(text); i++)
	{
		for (int j = 0; j < 9; j++)  // Since each byte array is only 8 bits long
		{
			if (j == 8) // This will create a space between each characters binary output
			{
				cout << endl;
				continue;
			}
		cout << "Element at x[" << i << "][" << j << "]: ";
		cout << binary_list[i][j]<< endl;

		}
	}

	return 0;
}

