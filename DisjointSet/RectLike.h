#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class  RectLike{

public:
	double p;//����������ռ�İٷֱȣ������ñ�����ϲ�
	float start_x,start_y,end_x,end_y;//�ϲ��󹫹��������ʼ��
	float w,h;//r1��r2��������ĳ�����

public:
	RectLike();
	RectLike(double p);
	void overlap(Rect &r1,Rect &r2);
	float overlap_area(Rect r1,Rect r2);//�жϿ��ͼ����ص����
	bool operator()(cv::Rect r1,cv::Rect r2);
	Rect merge(cv::Rect r1,cv::Rect r2);
	int Disjoint_set_merge(vector<Rect> rects,vector<Rect>& merge_rects,vector<int>& labels,RectLike rLike);
	//���鼯������ֻ��ʵ������ĺϲ�


};
