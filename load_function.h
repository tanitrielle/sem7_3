#ifndef LOAD_FUNCTION_INCLUDED
#define LOAD_FUNCTION_INCLUDED


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>

using namespace cv;

Mat load_image(string dir_arg, string filename);


#endif // LOAD_FUNCTION_INCLUDED
