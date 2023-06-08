/*
Author: Wei Chieh Huang
Date:	8/Apr/2020
Description: 	aoinosafaiefoia\\\\
*/
#include "HuangWeiChiehhw4.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void EncryptFile(char[], char[], char[]);
void DecryptFile(char[], char[], char[]);
void CleanBuffer(char*);
int fun1(int, int&);
int main();

char opName[10];

int main(void)
{
Parent* item = new Child();
item->method();
delete item;
return 0;
}

int mains (int argc, char *argv[])
{
	main();

	int menuOption;
	int keySize;

	char encryptIF[11];
	char encryptOF[11];
	char decryptIF[11];
	char decryptOF[11];
	char cipherKey[128];

	bool checkFinish = false;

	cout << "Please enter the cipher key:" << endl;
	cin >> cipherKey;

	while(checkFinish == false)
	{
		cout << "What would you like to do?" << endl;
		cout << "0 - Encrypt a file" << endl;
		cout << "1 - Decrypt a file" << endl;
		cout << "2 - Exit" << endl;
		cin >> menuOption;

		if(menuOption == 0)
		{
			//EncryptFile(encryptIF, encryptOF);

			cout << "what is the file name you want to encrypt?" << endl;
			cin >> encryptIF;

			cout << "What is the output file name?" << endl;
			cin >> encryptOF;

			EncryptFile(encryptIF, encryptOF,cipherKey);
		}
		else if( menuOption == 1)
		{
			cout << "what is the file name for the decryption" << endl;
			cin >> decryptIF;

			cout << "What is the output file name?" << endl;
			cin >> decryptOF;

			DecryptFile(decryptIF, decryptOF,cipherKey);

		}
		else if(menuOption == 2)
		{
			checkFinish = true;
		}
		else
		{
			cout << "Please enter a valid option" << endl;
			cin >> menuOption;
		}
	}
}
void EncryptFile(char encryptIF[], char encryptOF[], char cipherKey[])										// Encrypt File
{
	int i, row, col;
	int keyAdd = 0;
	int repeatCount = 0;
	int elementCount = 1024;
	char buffer[1024];
	char copy;
	char** vTable;
	// above declaring above

	cout << cipherKey << endl;

	FILE *infile;										// pointer to file
	infile = fopen(encryptIF,"r");						// open file


	if(infile != NULL)									// check if file open
	{
		cout << "The file did open" << endl;			// check if file open than tell user
	}
	else
	{
		cout << "The " << encryptIF << " file did not open" << endl;
	}

	//making 2d Array
	vTable = new char* [sizeof(buffer)];									// make the first array
	for(i = 0; i < sizeof(buffer); i++)										// make the second array
	{
		vTable[i] = new char [95];											// ascii from 33 ~ 126
	}

	for(i = 0; i < sizeof(cipherKey); i++)
	{
		if(cipherKey[repeatCount] != NULL)									// if cipherkey == null go back to char 0
		{
			repeatCount++;
		}
		else
		{
			repeatCount = 0;
		}
	}
	// vtable
	for(col = 0; col < sizeof(buffer); col++)								// making the vignere table
	{
		if(cipherKey[keyAdd] == NULL)
		{
			keyAdd = 0;
		}
		for(row = 0; row < 95; row++)										// only allow char from ascii 33 ~ 126
		{
			if(cipherKey[keyAdd] + row >= 127)
			{
				vTable[row][col] = (cipherKey[keyAdd] + row) - 95;
				cout << vTable[row][col];
			}
			else
			{
				vTable[row][col] = cipherKey[keyAdd] + row;
				cout << vTable[row][col];
			}
		}
		cout << endl;
		keyAdd++;
	}

	// encrypt
	FILE *outfile;
	outfile = fopen(encryptOF,"wt");
	keyAdd = 0;
	int check = 0;
	char hello;

	if(outfile != NULL)
	{
		fread(buffer, sizeof(char),sizeof(buffer), infile);
		cout << "\n"<< encryptOF << " did open" << endl;
		for(col = 0; col < sizeof(buffer); col++)
		{
			fwrite(buffer, sizeof(char),sizeof(buffer), infile);
			if(cipherKey[keyAdd] == NULL)						// if cipherkey finds empty char go back to start
			{
				keyAdd = 0;
				//cout << " keyadd = 0" << endl;
			}

//				check = buffer[col] - 32;						// find the difference
//				cout << "Bufferkey: "<< buffer[col] << " cipherkEY: " << cipherKey[keyAdd]<< endl;
//				cout << "check: " << check << endl;
//				cout << "col: " << col << endl;
//				buffer[col] = vTable[check][col];							// encrypt the code from vignere table
//				cout << "vtable " << vTable[check][col] << endl;

				check = buffer[col] + cipherKey[keyAdd] - 127;
				if(check <= 32)
				{
					check = check + 95;
				}
				//cout << buffer[col] << " " << cipherKey[keyAdd] << " " << check << endl;
				buffer[col] = check;

				//cout << buffer << endl;

			    keyAdd++;
			    //CleanBuffer(buffer);

		}
		CleanBuffer(buffer);
	}
		cout << buffer << endl;
		cout << "\nEncode FINISH!" << endl;
//	}
	fclose(infile);
	fclose(outfile);

	//delete
	for(row = 0; row < 95; row++)
	{
			delete[] vTable[row];
	}
	delete[] vTable;
}


void DecryptFile(char decryptIF[], char decryptOF[], char cipherKey[])					// decrypt File
{
	int i, row, col;
	int keyAdd = 0;
	int repeatCount = 0;
	char buffer[1024];
	char copy;
	char** vTable;
	// above declaring variable

	FILE *infile;										// pointer to file
	infile = fopen(decryptIF,"r");


	if(infile != NULL)									// check if file open
	{
		cout << "The file did open" << endl;			// check if file open than tell user

	}
	vTable = new char* [sizeof(buffer)];										// make the first array
		for(i = 0; i < sizeof(buffer); i++)										// make the second array
		{
			vTable[i] = new char [95];											// ascii from 33 ~ 126
		}

		for(i = 0; i < sizeof(cipherKey); i++)
		{
			if(cipherKey[repeatCount] != NULL)									// if cipherkey == null go back to char 0
			{
				repeatCount++;
			}
			else
			{
				repeatCount = 0;
			}
		}

		for(col = 0; col < sizeof(buffer); col++)								// making the vignere table
		{
			if(cipherKey[keyAdd] == NULL)
			{
				keyAdd = 0;
			}
			for(row = 0; row < 95; row++)										// only allow char from ascii 33 ~ 126
			{
				if((int)cipherKey[keyAdd] + row >= 127)
				{
					vTable[row][col] = ((int)cipherKey[keyAdd] + row) - 95;
					cout << vTable[row][col];
				}
				else
				{
					vTable[row][col] = (int)cipherKey[keyAdd] + row;
					cout << vTable[row][col];
				}
			}
			cout << endl;
			keyAdd++;
		}




		FILE *outfile;
		outfile = fopen(decryptOF,"wt");
		keyAdd = 0;
		int check = 0;
		int outputCount = 0;
		//decrypt
		// write into file
		if(outfile != NULL)
		{
			cout << "\n"<< decryptOF << " did open" << endl;

			for(col = 0; col < sizeof(buffer); col++)
			{

				outputCount = fwrite(buffer, sizeof(char),sizeof(buffer), outfile);

				if(cipherKey[keyAdd] == NULL)						// if cipherkey finds empty char go back to start
				{
					keyAdd = 0;
					//cout << " keyadd = 0" << endl;
				}

				check = buffer[col] - cipherKey[keyAdd] + 95 + 32;
				if(check >= 127)
				{
					check = check - 95;
				}
				//cout << buffer[col] << " " << cipherKey[keyAdd] << " " << check << endl;

				buffer[col] = check;
				//cout << buffer << endl;

//
//					check = buffer[col] - 32;						// find the difference
//					cout << "Bufferkey: "<< buffer[col] << " cipherkEY: " << cipherKey[keyAdd]<< endl;
//
//					cout << "check: " << check << endl;
//					cout << "col: " << col << endl;
//
//					buffer[col] = vTable[check][col];							// encrypt the code from vignere table
//
//					cout << "vtable " << vTable[check][col] << endl;
//					cout << buffer << endl;
				    keyAdd++;
				   // CleanBuffer(buffer);

			}
			cout << buffer << endl;
			cout << "\nrewrite FINISH!" << endl;

		}
		fclose(infile);
		fclose(outfile);


		//delete
		for(row = 0; row < 95; row++)
		{
			delete[] vTable[row];
		}
		delete[] vTable;

}

void CleanBuffer(char* buffer)
{
	int i;
	for(i = 0; i < 1024; i++)
	{
		buffer[i] = '\0';
	}
}






