#ifndef GENERATORN_H_INCLUDED
#define GENERATORN_H_INCLUDED

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>

using namespace std;

string generationFor(string &dir, string filename, int compression_rate);

string MyToString(int numb);

string C_toString(char *dir);



#endif // GENERATORN_H_INCLUDED
