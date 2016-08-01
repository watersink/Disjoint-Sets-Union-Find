#include "RectLike.h"
#include "PointLike.h"
#include<ctime>

int main()
{
	int image_width=400;
	int image_height=400;
	Mat image(image_height,image_width,CV_8UC3);
	image.setTo(0);
	int sample_num=3;
	srand(time(0));//保证每次产生的随机数不一样 


//RectLike的测试

	vector<Rect> rects;
	vector<Rect> merge_rects;
	vector<int>labels;

	/*for (size_t i=0;i<sample_num;i++)
	{
	int x=rand()%(image_width-10);
	int y=rand()%(image_height-10);
	int width=abs(rand()%(image_width-x-10));
	int height=abs(rand()%(image_height-y-10));
	rects.push_back(Rect(x,y,width,height));
	labels.push_back(i);
	}*/


	rects.push_back(Rect(80,80,180,120));
	rects.push_back(Rect(130,130,180,120));
	rects.push_back(Rect(300,300,50,50));
	labels.push_back(0);labels.push_back(1);labels.push_back(2);


	RectLike rLike(0.4);
	int count=rLike.Disjoint_set_merge( rects,merge_rects,labels,rLike);

	for(size_t i = 0;i<rects.size();i++)
	{
		cv::rectangle(image,rects[i],Scalar(0,255,255),6);
	}
	for(size_t i = 0;i<merge_rects.size();i++)
	{
		cv::rectangle(image,merge_rects[i],Scalar(0,0,255),2);		
	}





//PointLike的测试
	//PointLike pLike(50);
	//vector<int> labels;
	//vector<Point>pts;
	//for (size_t i=0;i<sample_num;i++)
	//{
	//	pts.push_back(Point(rand()%image_width,rand()%image_height));
	//}

	//int count= pLike.Disjoint_set_merge(pts,labels, pLike);

	//for(size_t i = 0;i<pts.size();i++)
	//{
	//	cv::circle(image,pts[i],2,Scalar(0,0,255),-1);
	//}
	//
	//vector<Scalar> color;
	//for (size_t i=0;i<count;i++)
	//	color.push_back(Scalar(rand()%255,rand()%255,rand()%255));
	//if (count!=labels.size())//说明有合并的
	//for(size_t i = 0;i<pts.size();i++)
	//{
	//	cv::circle(image,pts[i],10,color[labels[i]]);
	//	char text[100];
	//	sprintf(text,"%d",labels[i]);
	//	putText(image,text,pts[i],CV_FONT_HERSHEY_COMPLEX, 1,color[labels[i]] );
	//}




	imshow("image",image);
	cout<<"总区域"<<count<<endl;

	waitKey(0);
	return 0;
}