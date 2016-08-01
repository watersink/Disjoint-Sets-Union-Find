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
{	//并查集方法，实现了点集的合并
	//pts为合并前的点，labels为点的标签，p为合并的置信度

	int count = cv::partition(pts,labels,pLike);
	return count;

}