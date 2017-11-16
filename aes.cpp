#include <iostream>
#include <string>
#include <iomanip> //for precision printing

using namespace std;

/* Global Variables */

/* Functions */
void printArrayInHex(int (&array)[4][4])
{
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        cout << setfill('0') << setw(2) << std::hex << array[i][j] << " "; //because 0x00 prints as 0 instead of 00
                }
                cout << endl;
        }
}

bool isUpperCase(char part)
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
                                if (plainText.length() == 1) //else only handles 2+ length, needed to account for key sizes of 1
                                {
                                        part1 = plainText[0];
                                        plainTextTraversal++;
                                        part1Int = checks(part1);
                                        plainTextInt[j][i] = part1Int * 1; //multiplying by 1 makes it work for some reason
                                }
                                else
                                {
                                        part1 = plainText[plainTextTraversal++];
                                        part2 = plainText[plainTextTraversal++];

                                        part1Int = checks(part1);
                                        part2Int = checks(part2);

                                        part1Int *= 16; //turns it into proper hexadecimal for the first number
                                        part2Int *= 1; //same logic as above
                                        plainTextInt[j][i] = part1Int + part2Int; //not supposed to be i,j the way I had it before because the string is supposed to go column-by-column according to the video (and is how all the encryptors I found online do it)
                                }
                        }
                        else
                                plainTextInt[j][i] = 0x00; //0x00, fill in rest with 0s until it is 128-bits
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
                0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
        };
        return sBox [value];
}

void generateRoundKeys(int (&roundKeyArray)[4][44])
{
        int RCon[4][10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,
                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

        for (int i = 4; i < 44; i++)
        {
                if (i % 4 == 0)
                {
                        for (int k = 1; k < 4; k++)
                        {
                                roundKeyArray[k-1][i] = roundKeyArray[k][i-1];
                                roundKeyArray[k-1][i] = getValueFromSubstitutionBox(roundKeyArray[k-1][i]);
                        }
                        roundKeyArray[3][i] = roundKeyArray[0][i-1];
                        roundKeyArray[3][i] = getValueFromSubstitutionBox(roundKeyArray[3][i]);
                }
                for (int j = 0; j < 4; j++)
                {
                        if (i % 4 == 0)
                        {
                                roundKeyArray[j][i] = roundKeyArray[j][i] ^ roundKeyArray[j][i-4];
                                roundKeyArray[j][i] = roundKeyArray[j][i] ^ RCon[j][(i/4)-1];
                        }
                        else
                        {
                                roundKeyArray[j][i] = roundKeyArray[j][i-1] ^ roundKeyArray[j][i-4];
                        }
                }
        }
        /* According to the video:
           Take the last column, rotate it (so 9,cf,4f,3c becomes cf,4f,3c,9)
           Do SubBytes on it (use substitution())
           XOR with first column of key
           XOR that result with first column of RCon (then second, third, etc. until 10th)
           This results in the first column of roundKey

           Second, third, fourth column:
           Take second/third/fourth column of key, XOR it with result got earlier from first/second/third column result

           Repeat until 10th roundkey 4x4 matrix is filled

           These 4x4 matrices will be your roundKeys for each round
           All you do is XOR column of chunks with column of roundKey, 1-to-1
         */
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

} //working!

int calculations (int currentRowMCW[4], int currentColumnC[4])
{
        int ret_val_array[4] = {0,0,0,0};
        for (int i = 0; i < 4; i++)
        {
                if (currentRowMCW[i] == 0x01)
                {
                        ret_val_array[i] = currentColumnC[i]; //nothing happens, it's like multiplying by 1
                }
                else if (currentRowMCW[i] == 0x02)
                {
                        //cout << "0x02: " << currentColumnC[i] << endl;
                        ret_val_array[i] = currentColumnC[i] << 1; //left shift 1
                        //cout << "Left shift: " << ret_val_array[i] << endl;
                        if ((currentColumnC[i] & 0x80) == 0x80) //firstmost binary bit is a 1 then
                        {
                                ret_val_array[i] = ret_val_array[i] & 0xff; //to get rid of the leading 1
                                //cout << "And mask: " << ret_val_array[i] << endl;
                                ret_val_array[i] = ret_val_array[i] ^ 0x1b; //XOR with 0001 1011
                                //cout << "XOR 1b: " << ret_val_array[i] << endl;
                        }
                }
                else
                {
                        //cout << "0x03 thing: " << currentColumnC[i] << endl;
                        int p1_ret_val = currentColumnC[i] << 1;
                        //cout << "0x03 P1: " << p1_ret_val << endl;
                        int p2_ret_val = currentColumnC[i];
                        if ((currentColumnC[i] & 0x80) != 0x00) //firstmost binary bit is a 1 then
                        {
                                p1_ret_val = p1_ret_val & 0xff; // to get rid of the leading 1
                                //cout << "And mas: " << p1_ret_val << endl;
                                p1_ret_val = p1_ret_val ^ 0x1b; //XOR with 0001 1011
                                //cout << "XOR thing: " << p1_ret_val << endl;
                        }
                        ret_val_array[i] = p1_ret_val ^ p2_ret_val; //XOR the results, as mentioned earlier
                }
        }
        int ret_val = ret_val_array[0] ^ ret_val_array[1] ^ ret_val_array[2] ^ ret_val_array[3];
        //cout << std::hex << int(ret_val_array[0]) << " " << std::hex << int(ret_val_array[1]) << " " << std::hex << int(ret_val_array[2]) << " " << std::hex << int(ret_val_array[3]) << endl;
        return ret_val;
}

void mixColumns (int (&chunks)[4][4])
{
        int mixColumnsWith[4][4] = {  0x02, 0x03, 0x01, 0x01,
                                      0x01, 0x02, 0x03, 0x01,
                                      0x01, 0x01, 0x02, 0x03,
                                      0x03, 0x01, 0x01, 0x02  };

        int results[4] = {  0,0,0,0  };//may be necessary for XOR operations (since we're actually supposed to be limited to 8-bits)
        int currentRowMCW[4] =  { 0,0,0,0 };
        int currentColumnC[4] = { 0,0,0,0 };

        /* apologies about the horrendous-looking code below, it works and that's all that matters for now
           especially since it took me like 3 days of thinking how to approach this */

        for (int k = 0; k < 4; k++)
        {
                for (int j = 0; j < 4; j++)
                {
                        for (int i = 0; i < 4; i++)
                        {
                                currentColumnC[i] = chunks[i][k]; //currentColumn is k
                                currentRowMCW[i] = mixColumnsWith[j][i]; //currentRow is j
                        }
                        //currentRow++;
                        results[j] = calculations(currentRowMCW, currentColumnC); //fills results with calculations, then will flush later
                }
                /* flush results from results to chunks */
                for (int l = 0; l < 4; l++)
                {
                        chunks[l][k] = results[l]; //currentColumn is k
                }
                //currentColumn++; //increment currentColumn to manipulate the next column in our 4x4 matrix
                //currentRow = 0; //reset currentRow to 0 for manipulation of next column (think: 1x4 (currentColumnC) and 4x4 (mixColumnsWith) matrix multiplication, which leads to a 1x4 (results) matrix
        }
}

void addRoundKey (int (&key)[4][4], int (&chunks)[4][4])
{
        //XOR each column of key with chunks
        //or XOR each row of key with chunks
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        chunks[i][j] = chunks[i][j] ^ key[i][j];
                }
        }
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

        cout << endl << "Plaintext before conversion: " << plainText << " (string)" << endl;
        cout << "Key before conversion: " << key << " (string)" << endl << endl;

        int plainTextInt [4][4];
        stringToIntArrays(plainText, plainTextInt); //need to convert from string to int to perform mathematical operations

        cout << "Plaintext after conversion (from string to int): " << endl; //just as a check
        printArrayInHex(plainTextInt);
        cout << endl;

        cout << "Key after conversion (from string to int): " << endl; //same logic as above
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
        //if input size > 128 then split into 128-bit chunks (will do later, need to get mixColumns and addRoundKey functioning first)

        int roundKeys[4][44];
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        roundKeys[i][j] = keyInt[i][j]; //so we only have to handle one arrary instead of two
                }
        }

        if (argc > 1 && argc < 3) //for debug mode
        {
                if (*argv[1] == 'd')
                {
                        int choice = 0;
                        cout << "Debugger mode: Please select one of the functions to test" << endl;
                        cout << "0. Simulate Substitution, Shift Rows, then Mix Columns" << endl << "1. Substitution" << endl << "2. Shift Rows" << endl << "3. Mix Columns" << endl << "4. Generating Round Keys" << endl << "5. Add Round Key (0th round check only)" << endl;
                        cout << "Choice: ";
                        cin >> choice;
                        if (choice < 0 || choice > 5)
                        {
                                cout << "Incorrect choice." << endl;
                                return 1;
                        }
                        if (choice == 0)
                        {
                                substitution(cipherTextInt);
                                shiftRows(cipherTextInt);
                                mixColumns(cipherTextInt);
                                cout << "Output: ";
                                printArrayInHex(cipherTextInt);
                                cout << endl;
                                return 0;
                        }
                        else if (choice == 1)
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
                        else if (choice == 4)
                        {
                                generateRoundKeys(roundKeys);
                                for (int k = 0; k <= 10; k++)
                                {
                                        for (int i = 0; i < 4; i++)
                                        {
                                                for (int j = k*4; j < (k+1) * 4; j++)
                                                {
                                                        cout << roundKeys[i][j] << " ";
                                                }
                                                cout << endl;
                                        }
                                        cout << endl;
                                        cout << endl;
                                }
                                return 0;
                        }
                        else
                        {
                                cout << "Output: ";
                                addRoundKey(keyInt, cipherTextInt);
                                printArrayInHex(cipherTextInt);
                                cout << endl;
                                return 0;
                        }
                }
        }

        generateRoundKeys(roundKeys); //to generate a 4x40 (44, including first 4x4 matrix of keyInt) array, it's our key scheduler
        //before starting, need to do addRoundKey for round 0

        int currentRoundKey[4][4]; //used in the individual rounds of addRoundKey (populates values from the 4x44 matrix roundKeys)
        addRoundKey(keyInt, cipherTextInt); //0th round

        for (int currentRound = 1; currentRound <= 9; currentRound++) //runs 0-9 times
        {
                substitution (cipherTextInt);
                shiftRows (cipherTextInt);
                mixColumns (cipherTextInt);
                for (int i = currentRound * 4; i < ((currentRound+1)*4); i++)
                {
                        for (int j = 0; j < 4; j++)
                        {
                                currentRoundKey[j][i-(currentRound*4)] = roundKeys[j][i]; //extracting from roundKey, one 4x4 matrix at a time (this is doing it column-by-column)
                        }
                }
                addRoundKey (currentRoundKey, cipherTextInt);
        }

        //10th round skips mixColumns
        substitution (cipherTextInt);
        shiftRows (cipherTextInt);

        for (int i = 40; i < 44; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        currentRoundKey[j][i-40] = roundKeys[j][i];
                }
        }

        addRoundKey (currentRoundKey, cipherTextInt);

        //printing time
        cout << "---------------------------------------------------------------------------------------------------------" << endl;
        cout << endl << "4x4 Matrix Ciphertext: " << endl;
        printArrayInHex(cipherTextInt);
        cout << endl;

        //prints the cipherText in a line (just to be sure)
        cout << "Inline Ciphertext: ";
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        cout << cipherTextInt[j][i];
                }
        }
        cout << endl << endl;

        return 0;
}
