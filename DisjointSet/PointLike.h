#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class PointLike
{
public:
	int thresh;
public:
	PointLike();
	PointLike(int thresh);
	bool operator()(cv::Point p1,cv::Point p2);
	int Disjoint_set_merge(vector<Point>pts,vector<int>& labels,PointLike rLike);
	
};

