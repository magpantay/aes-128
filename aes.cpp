#include <iostream>
#include <string>

using namespace std;

/* Global Variables */

int RoundKey[176]; //or is it 240?

/* Functions */

void printArrayInHex(int (&array)[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << std::hex << array[i][j];
		}
	}
}

bool isUpperCase (char part)
{
	return ((part - 'A') < 6); //is upperCase (up to F only) [A-F]
}

bool isNumber(char part)
{
	return ((part - '0') <= 9); //returns true if it is, meaning it is a number [0-9]
}

int checks (char part)
{
	if (isNumber(part))
		return part - '0'; //should be a numerical value
	else if (isUpperCase(part))
		return part - 55; //should equal 0xA or 10 if A, 0xF or 15 if F
	else
		return part - 87; //should equal 0xA or 10 if a, 0xF or 15 if f
}

void stringToIntArrays (string plainText, int (&plainTextInt)[4][4])
{
	int plainTextTraversal = 0;
	char part1, part2;
	int part1Int, part2Int;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (plainText.length() > plainTextTraversal)
			{
				if (plainText.length() == 1) //bottom only handles 2+ length
				{
					part1 = plainText[0];
					plainTextTraversal++;
					part1Int = checks(part1);
					plainTextInt[i][j] = part1Int * 1; //multiplying by 1 makes it work for some reason
				}
				else
				{
					part1 = plainText[plainTextTraversal++];
					part2 = plainText[plainTextTraversal++];

					part1Int = checks(part1);
					part2Int = checks(part2);

					part1Int *= 16; //turns it into proper hexadecimal for the first number
					part2Int *= 1; //same logic as above
					plainTextInt[i][j] = part1Int + part2Int;
				}
			}
			else
				plainTextInt[i][j] = 0x00; //0x00, fill in rest with 0s until it is 128-bits
		}
	}
}

int getValueFromSubstitutionBox (int value)
{
	int sBox [256] = {
				0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
				0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
				0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
				0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
				0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
				0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
				0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
				0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
				0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
				0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
				0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
				0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
				0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
				0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
				0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
				0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16	};
	return sBox [value];
}

void substitution (int (&chunks)[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			chunks[i][j] = getValueFromSubstitutionBox (chunks[i][j]);
		}
	}
	/* cout << "In subby: ";
	printArrayInHex(chunks); cout << endl; */
} //works perfectly!

void shiftRows (int (&chunks)[4][4])
{
	int swapTemp = 0;
	//don't do anything to the 0th row

	//shift 1st row once left

	swapTemp = chunks[1][0];
	chunks[1][0] = chunks[1][1];
	chunks[1][1] = chunks[1][2];
	chunks[1][2] = chunks[1][3];
	chunks[1][3] = swapTemp;

	//shift 2nd row twice left

	swapTemp = chunks[2][0];
	chunks[2][0] = chunks[2][2];
	chunks[2][2] = swapTemp;

	swapTemp = chunks[2][1];
	chunks[2][1] = chunks[2][3];
	chunks[2][3] = swapTemp;

	//shift 3rd row three times left

	swapTemp = chunks[3][0];
	chunks[3][0] = chunks[3][3];
	chunks[3][3] = chunks[3][2];
	chunks[3][2] = chunks[3][1];
	chunks[3][1] = swapTemp;

	/* cout << "In shiftRows" << endl;
	printArrayInHex(chunks);
	cout << endl; */
} //working!

void mixColumns (int (&chunks)[4][4])
{
	int mixColumnsWith[4][4] = {	0x02, 0x03, 0x01, 0x01,
					0x01, 0x02, 0x03, 0x01,
					0x01, 0x01, 0x02, 0x03,
					0x03, 0x01, 0x01, 0x02	};

	int results[4] = { 	0,0,0,0	 };
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
				if (mixColumnsWith[i][j] == 1)
				{
					results[k++] = chunks[j][i];
				}
				else if (mixColumnsWith[i][j] == 2)
				{
					results[k] = chunks[j][i] << 1; //left shift to "multiply" by 2 in binary
					if ((chunks[j][i] & 0x80) != 0x00) //special cautions take place since first binary digit would be 1 prior to shifting left 1
						results[k++] ^= 0x1b; //XORs with specifically 0x1b or 0001 1011
				 	//otherwise, continue as normal and just shift without XORing
				 	else
						k++; //need to increment k still
				}
				else //it's 3
				{
					int part1 = chunks[j][i] << 1; //do 2's mixColumns, then XOR it with 1's
					int part2 = chunks[j][i]; //1's mixColumns
					if ((chunks[j][i] & 0x80) != 0x00)
						part1 ^= 0x1b;
					results[k++] = part1 ^ part2;
				}
				chunks[j][i] = results[0] ^ results[1] ^ results[2] ^ results[3]; //not i,j because we are editing column by column, not row by row

				/* how the resulting equations are supposed to end up being from matrix multiplication
				r0 = 2(c0,b0) + 3(c0,b1) + 1(c0,b2) + 1(c0,b3) column 0 (c0)
				r1 = 1(c1,b0) + 2(c1,b1) + 3(c1,b2) + 1(c1,b3) column 1 (c1)
				r2 = 1(c2,b0) + 1(c2,b1) + 2(c2,b2) + 3(c2,b3) column 2 (c2)
				r3 = 3(c3,b0) + 1(c3,b1) + 1(c3,b2) + 2(c3,b3) column 3 (c3)
				The multiplication is a "complicated operation" while the additions are XORs
				*/
		}
	}
	//XOR something
	/* cout << "In mixColumns" << endl;
	printArrayInHex(chunks);
	cout << endl; */
}

void addRoundKey (int currentRound, int (&chunks)[4][4])
{
	//XOR currentRound with chunks
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			chunks[j][i] ^= RoundKey[currentRound * 16 + i * 4 + j]; //[currentRound * Nb * 4 + i + Nb + j], Nb = 4
		} // ^ is a bitwise XOR
	}

	for (int i = 0; i < 128; i++) //AES-128 has a 128-bit block size
	{
		ciphertext[i] = plaintext[i]
	}*/
	/* cout << "In addRoundKey, currentRound: " << currentRound << endl;
	printArrayInHex(chunks);
	cout << endl; */
}
int main (int argc, char * argv[])
{
	string plainText = "";
	string key = "";

	cout << "Enter hexadecimal-based plaintext (i.e., 0x1f, 0x2f is inputted as 1f2f): ";
	getline(cin, plainText);

	if (plainText.length() > 32)
	{
		cout << "That's coming up, try something smaller for now, maybe <= 128 bits (32 characters)" << endl;
		return 1;
	}

	cout << "Enter key in a similar way as above: ";
	getline(cin, key);

	if (key.length() > 32)
	{
		cout << "The key is only supposed to be 128-bits long, try again with a 32 character key." << endl;
		return 1;
	}

	//if input size < 128, then fill with 0s until 128-bits, 0x12 (8-bit) becomes 0x12000000000000000000000000000000 (128-bit)
/*
	while (key.length() % 32 == 0)
	{
		key.append("0", 1); //fill with 0s until it is 128-bit
	}

	while (plainText.length() % 32 == 0)
	{
		plainText.append("0", 1); //fill with 0s until it is 128-bit
	}
*/
	cout << "Plaintext before conversion: " << plainText << endl;
	cout << "Key before conversion: " << key << endl;

	int plainTextInt [4][4];
	stringToIntArrays(plainText, plainTextInt);

	cout << "Plaintext after conversion: ";
	printArrayInHex(plainTextInt);
	cout << endl;

	cout << "Key after conversion: ";
	int keyInt[4][4];
	stringToIntArrays(key, keyInt);
	printArrayInHex(keyInt);
	cout << endl;

	int cipherTextInt [4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipherTextInt[i][j] = plainTextInt[i][j]; //in essence, making a copy of plainTextInt array, this will be the one to undergo the transformations
		}
	}

	//if input size > 128 then split into 128-bit chunks

	//before starting, need to do addRoundKey for round 0
	if (argc > 1 && argc < 3)
	{
		if (*argv[1] == 'd')
		{
			int choice = 0;
			cout << "Debugger mode: Please select one of the functions to test" << endl;
			cout << "1. Substitution" << endl << "2. Shift Rows" << endl << "3. Mix Columns" << endl << "4. Add Round Key (0th round simulation only)" << endl;
			cout << "Choice: ";
			cin >> choice;
			if (choice < 1 || choice > 4)
			{
				cout << "Incorrect choice." << endl;
				return 1;
			}
			if (choice == 1)
			{
				substitution (cipherTextInt);
				cout << "Output: ";
				printArrayInHex(cipherTextInt);
				cout << endl;
				return 0;
			}
			else if (choice == 2)
			{
				shiftRows(cipherTextInt);
				cout << "Output: ";
				printArrayInHex(cipherTextInt);
				cout << endl;
				return 0;
			}
			else if (choice == 3)
			{
				mixColumns (cipherTextInt);
				cout << "Output: ";
				printArrayInHex(cipherTextInt);
				cout << endl;
				return 0;
			}
			else
			{
				addRoundKey(0, cipherTextInt);
				cout << "Output: ";
				printArrayInHex(cipherTextInt);
				cout << endl;
				return 0;
			}
		}
	}

	string currentChunksConcatentation = "";
	int cipherText[128];

	addRoundKey(0, cipherTextInt);

	for (int currentRound = 1; currentRound <= 9; currentRound++) //runs 9 times
	{
		substitution (cipherTextInt);
		shiftRows (cipherTextInt);
		mixColumns (cipherTextInt);
		addRoundKey (currentRound, cipherTextInt);
	}

	//10th round skips mixColumns
	substitution (cipherTextInt);
	shiftRows (cipherTextInt);
	addRoundKey (10, cipherTextInt);

	printArrayInHex(plainTextInt);
	cout << " encrypted in AES-128 is ";
	printArrayInHex(cipherTextInt);
	cout << endl;
	return 0;

}
