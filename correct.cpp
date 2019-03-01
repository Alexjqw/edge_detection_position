#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <cv.h>
#include <cxmisc.h>
#include <highgui.h>
#include <cvaux.h>
#include <iostream>
#include <ctype.h>
//#include <unistd.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

#include <stdio.h>

using namespace cv;
using namespace std;


#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>





#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <cv.h>
#include <cxmisc.h>
#include <highgui.h>
#include <cvaux.h>
#include <iostream>
#include <ctype.h>
//#include <unistd.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

#include <stdio.h>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
using namespace cv;
using namespace std;

#include "popt_pp.h"

using namespace std;
using namespace cv;

int main()
{


  VideoCapture cap1(1);
  VideoCapture cap2(2);


   Mat img1, img_res1, img2, img_res2;

  char* leftimg_filename="left1.jpg";
  char* rightimg_filename="right1.jpg";
  char* calib_file="cam_stereo.yml";
  char* leftout_filename="left.jpg";
  char* rightout_filename="right.jpg";



  Mat R1, R2, P1, P2, Q;
  Mat K1, K2, R;
  Vec3d T;
  Mat D1, D2;


  cv::FileStorage fs1(calib_file, cv::FileStorage::READ);
  fs1["K1"] >> K1;
  fs1["K2"] >> K2;
  fs1["D1"] >> D1;
  fs1["D2"] >> D2;
  fs1["R"] >> R;
  fs1["T"] >> T;

  fs1["R1"] >> R1;
  fs1["R2"] >> R2;
  fs1["P1"] >> P1;
  fs1["P2"] >> P2;
  fs1["Q"] >> Q;

  cv::Mat lmapx, lmapy, rmapx, rmapy;
  cv::Mat imgU1, imgU2;
  CvMat part_p;

  while (1)
  {
    cap1 >> img1;
    cap2 >> img2;
    imshow("left", img1);
    imshow("right", img2);
    imwrite("left1.jpg", img1);
    imwrite("right1.jpg", img2);
    Mat img1 = imread(leftimg_filename, CV_LOAD_IMAGE_COLOR);
    Mat img2 = imread(rightimg_filename, CV_LOAD_IMAGE_COLOR);

    CvMat* img1r = cvCreateMat(480,640, CV_8U );
    CvMat* img2r = cvCreateMat( 480,640, CV_8U );

    cv::initUndistortRectifyMap(K1, D1, R1, P1, img1.size(), CV_32F, lmapx, lmapy);
    cv::initUndistortRectifyMap(K2, D2, R2, P2, img2.size(), CV_32F, rmapx, rmapy);
    cv::remap(img1, imgU1, lmapx, lmapy, cv::INTER_LINEAR);
    cv::remap(img2, imgU2, rmapx, rmapy, cv::INTER_LINEAR);

    CvSize imageSize;
	  imageSize.height=480;
	  imageSize.width=640;



   imwrite(leftout_filename, imgU1);
   imwrite(rightout_filename, imgU2);

   IplImage* c_left=cvLoadImage("left.jpg",0);
	 IplImage* c_right=cvLoadImage("right.jpg",0);

   CvMat* left_mat = cvCreateMat(c_left->height, c_left->width,CV_8U);
   cvConvert (c_left , left_mat );

   CvMat* right_mat = cvCreateMat(c_left->height, c_left->width,CV_8U);
   cvConvert (c_right, right_mat );

   CvSize c_size = cvGetSize(c_left);
   //std::cout << "c_size =" <<c_size.width<<"  "<<c_size.height<< '\n';

   CvMat* pair_p;
   pair_p = cvCreateMat( c_size.height, c_size.width*2,CV_8U);


   cvGetCols( pair_p, &part_p, 0, c_size.width );

   cvCopy( left_mat, &part_p, 0);

   cvGetCols( pair_p, &part_p, c_size.width,c_size.width*2 );
   cvCopy( right_mat, &part_p, 0 );

   for( int j = 0; j < c_size.height; j += 16 )
      cvLine( pair_p, cvPoint(0,j),cvPoint(c_size.width*2,j),CV_RGB(0,255,0));
   cvShowImage( "矫正剪裁的图像", pair_p );
     if (waitKey(3) > 0)
      break;

  cvReleaseImage(&c_left);
  cvReleaseImage(&c_right);
  cvReleaseMat(&pair_p);
  cvReleaseMat(&img1r);
  cvReleaseMat(&img2r);
  cvReleaseMat(&left_mat);
  cvReleaseMat(&right_mat);
  img1.release();
  img2.release();
}
  return 0;
}
