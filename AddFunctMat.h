#ifndef ADDFUNCTMAT_H_INCLUDED
#define ADDFUNCTMAT_H_INCLUDED

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>
#include "GeneratorN.h"

using namespace cv;

Mat MoveDiagonal(Mat img, int numberX, int numberY);
int MetricNumber(Mat Original, Mat Compression);
int Normalizator(Mat original);
Mat GreenToGray(Mat img);
Mat oCanny(Mat img, int lT, int uT, int kS, string savingPath);
Mat SavingCompressedImage(Mat original, int rate, string output_dir);


#endif // ADDFUNCTMAT_H_INCLUDED
