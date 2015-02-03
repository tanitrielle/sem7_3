#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>
#include "AddFunct.h"

using namespace cv;
using namespace std;


int low_threshold()
{

    int lowThreshold = 0;

    while(true){
    cin >> lowThreshold;

    if(lowThreshold<0 || lowThreshold > 255){
    cout << "Enter value of Canny's lowThreshold. It should be between  0 and 255" << endl;
    }
    else{
    break;
    }
    }

    return lowThreshold;
}


int upper_threshold(int lowTreshold)
{

    int upperThreshold = 0;

    while(true)
    {
    cin >> upperThreshold;

    if(upperThreshold<0 || upperThreshold > 255 || upperThreshold<lowTreshold)
    {
    cout << "Enter value of Canny's upperThreshold. It should be between  0 and 255. LowThreshold should be " << endl;
    }
    else
    {
    break;
    }
    }

    return upperThreshold;
}


int kernel_size()
{
    int kernel_size = 3;

    while(true)
    {
    cin >> kernel_size;

    if( kernel_size == 3 || kernel_size == 5 || kernel_size == 7 )
    {
    break;
    }
    else
    {
    cout << "Enter kernel's value. It should be 3 or 5 or 7" << endl;
    }
    }

    return kernel_size;
}
