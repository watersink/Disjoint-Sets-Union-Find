#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class  RectLike{

public:
	double p;//公共区域所占的百分比，超过该比例则合并
	float start_x,start_y,end_x,end_y;//合并后公共区域的起始点
	float w,h;//r1和r2公共区域的长，宽

public:
	RectLike();
	RectLike(double p);
	void overlap(Rect &r1,Rect &r2);
	float overlap_area(Rect r1,Rect r2);//判断框出图像的重叠面积
	bool operator()(cv::Rect r1,cv::Rect r2);
	Rect merge(cv::Rect r1,cv::Rect r2);
	int Disjoint_set_merge(vector<Rect> rects,vector<Rect>& merge_rects,vector<int>& labels,RectLike rLike);
	//并查集方法，只现实了区域的合并


};
