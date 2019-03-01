#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"

using namespace std;
using namespace cv;

int x = 0;

int main()
{
  char* imgs_directory;
  imgs_directory="myimage";
  char* extension;
  extension="jpg";
  int im_width, im_height;
  im_width=640;
  im_height=480;


  VideoCapture cap1(1);//left camera
  VideoCapture cap2(2);//right camera
  Mat img1, img_res1, img2, img_res2;
  while (1) {
    if(x>=60)
      break;
    cap1 >> img1;
    cap2 >> img2;
    resize(img1, img_res1, Size(im_width, im_height));
    resize(img2, img_res2, Size(im_width, im_height));
    imshow("left", img_res1);
    imshow("right", img_res2);
    if (waitKey(60) > 0) {
      printf("%d\n", x);
      x++;
      char filename1[200], filename2[200];
      sprintf(filename1, "left%d.%s",  x, extension);
      sprintf(filename2, "right%d.%s", x, extension);
      cout << "Saving img pair " << x << endl;
      imwrite(filename1, img_res1);
      imwrite(filename2, img_res2);
    }
  }
  return 0;
}
