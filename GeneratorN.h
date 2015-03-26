#ifndef GENERATORN_H_INCLUDED
#define GENERATORN_H_INCLUDED

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>

using namespace std;

string generationFor(string &dir, string filename, int compression_rate);

const char* generationForData(string dir, string filename);
const char* generationForDataF1(string dir, string filename);
string MyToString(int numb);

string C_toString(char *dir);



#endif // GENERATORN_H_INCLUDED
