#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>
#include "load_function.h"

using namespace cv;
using namespace std;

Mat load_image(string dir_arg, string filename)
{
    Mat img;
    while(true)
    {

    string dir=dir_arg+filename;
    cout << dir << endl;

    img = imread(dir.c_str(), CV_LOAD_IMAGE_COLOR);

    if(img.empty())
    {
    cout << "File's name is incorrect. Please try again" << endl;
    }
    else
    {
    break;
    }
    }
    return img;
}
