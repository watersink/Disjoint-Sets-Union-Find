#include "RectLike.h"

RectLike::RectLike()
{
	start_x=0;
	end_x=0;
	start_y=0;
	end_y=0;
	p=0.6;
};
RectLike::RectLike(double p)
{this->p = p;}
void RectLike:: overlap(Rect &r1,Rect &r2)
{
	this->end_x=max(r1.x+r1.width,r2.x+r2.width);
	this->start_x=min(r1.x,r2.x);
	this->end_y=max(r1.y+r1.height,r2.y+r2.height);
	this->start_y=min(r1.y,r2.y);
	this->w=r1.width+r2.width-(end_x-start_x);
	this->h=r1.height+r2.height-(end_y-start_y);
}
float RectLike::overlap_area(Rect r1,Rect r2)
{//判断框出图像的重叠面积
	overlap(r1, r2);
	if (w<=0||h<=0)
		return 0;
	else
	{
		float area=this->w*this->h;
		return area;
	}
}
bool RectLike::operator()(cv::Rect r1,cv::Rect r2)
{
	//方法1，opencv hog,Cascade使用的合并方法
	double delta = p*(std::min(r1.width, r2.width) + std::min(r1.height, r2.height))*0.5;
	return std::abs(r1.x - r2.x) <= delta &&
		std::abs(r1.y - r2.y) <= delta &&
		std::abs(r1.x + r1.width - r2.x - r2.width) <= delta &&
		std::abs(r1.y + r1.height - r2.y - r2.height) <= delta;
	//方法2，求面积的合并方法
	//int area1 = r1.area();
	//int area2 = r2.area();
	//int area = overlap_area(r1,r2);//相交Rect面积
	//return area1<area2?area>=p*area1:area>=p*area2; 
	//方法3，投影法
	/*int xlap=40;int ylap=40;
	int x1=r1.x,x2=r1.x+r1.width,x3=r2.x,x4=r2.x+r2.width;
	int y1=r1.y,y2=r1.y+r1.height,y3=r2.y,y4=r2.y+r2.height;
	if (x1<=x3)
	{
	if ((x2<=x3&&x3-x2<=xlap)||(x1<=x3&&x3<=x2&&x2<=x4)||(x1<=x3&&x3<=x4&&x4<=x2))
	{
	if ((y4<=y1&&y1-y4<=ylap)||(y2<=y3&&y3-y2<=ylap)||(y1<=y3&&y3<=min(y2,y4))||(y3<y1&&y1<=min(y2,y4)))
	{
	return true;
	}

	}
	}else
	{
	if ((x4<=x1&&x1-x4<=xlap)||(x3<=x1&&x1<=x4&&x4<=x2)||(x3<=x1&&x1<=x2&&x2<=x4))
	{
	if ((y2<=y3&&y3-y2<=ylap)||(y4<=y1&&y1-y4<=ylap)||(y3<=y1&&y1<=min(y4,y2))||(y1<y3&&y3<=min(y4,y2)))
	{
	return true;
	}
	}
	}
	return false;*/
}
Rect RectLike::merge(cv::Rect r1,cv::Rect r2)
{
		overlap(r1, r2);
		Rect rect(start_x,start_y,end_x-start_x,end_y-start_y);
		return rect;
}
int RectLike::Disjoint_set_merge(vector<Rect> rects,vector<Rect>& merge_rects,vector<int>& labels,RectLike rLike)
{	//并查集方法，只现实了区域的合并
	//rects为合并前的矩形框，merge_rects为合并后矩形框，labels为矩形框的标签，p为合并的置信度
	vector<int>label_temp;
	for (size_t i=0;i<labels.size();i++)
		label_temp.push_back(1);
	int count = cv::partition(rects,labels,rLike);
	//如果没有合并，还是返回原始的rects,labels，如果合并了，返回以0开始的labels
	if (count!=labels.size())//两者不相等，说明进行了合并
	{
		
		for (size_t i=0;i<labels.size();i++)
		{	
			if (label_temp[i]==0) continue;
			Rect rect_temp=rects[i];
			label_temp[i]=0;
			for(size_t j=i+1;j<labels.size();j++)
			{
				if(labels[i]==labels[j])
				{
					rect_temp=rLike.merge(rect_temp,rects[j]);
					label_temp[j]=0;
				}

			}
			merge_rects.push_back(rect_temp);
		}

	}
	return count;

}


