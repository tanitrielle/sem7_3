#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>
#include "GeneratorN.h"

using namespace std;

string generationFor(string &dir, string filename, int compression_rate)
{

    string ext = ".jpg";
    return dir+MyToString(compression_rate)+filename+ext;

}

string MyToString(int numb)
{
    std::ostringstream oss;
    oss << numb;
    return oss.str();
}

char* generationForData(string dir, string filename)
{
    string ext= "data.txt";
    string res = dir+filename+ext;
    return (char*)res.c_str();
}

char* generationForDataF1(string dir, string filename)
{
    string ext= "f1data.txt";
    string res = dir+filename+ext;
    return (char*)res.c_str();
}

