#include "PointLike.h"

PointLike::PointLike()
{
	thresh=30;
}
PointLike::PointLike(int thresh)
{
	this->thresh = thresh;
}
bool PointLike::operator()(cv::Point p1,cv::Point p2)
{
	int x = p1.x - p2.x;
	int y = p1.y - p2.y;
	return x*x+y*y <=thresh*thresh;
}
int PointLike::Disjoint_set_merge(vector<Point>pts,vector<int>& labels,PointLike pLike)
{	//���鼯������ʵ���˵㼯�ĺϲ�
	//ptsΪ�ϲ�ǰ�ĵ㣬labelsΪ��ı�ǩ��pΪ�ϲ������Ŷ�

	int count = cv::partition(pts,labels,pLike);
	return count;

}