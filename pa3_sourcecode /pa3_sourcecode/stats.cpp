#include"stats.h"
using namespace std;
using namespace cs221util;

long stats::getSum(char channel,pair<int,int> ul,pair<int,int> lr){
	long sum;
	if(channel=='r'){
		if(ul.first!=0&&ul.second!=0)//中间点
		sum=sumRed[lr.first][lr.second]+sumRed[ul.first-1][ul.second-1]-sumRed[lr.first][ul.second-1]-sumRed[ul.first-1][lr.second];
		else if(ul.first!=0&&ul.second==0)//上边界点
		sum=sumRed[lr.first][lr.second]-sumRed[ul.first-1][lr.second];
		else if(ul.first==0&&ul.second!=0)//左边界点
		sum=sumRed[lr.first][lr.second]-sumRed[lr.first][ul.second-1];
		else if(ul.first==0&&ul.second==0)//origin点
		sum=sumRed[ul.first][ul.second];
		}
	else if(channel=='g'){
		if(ul.first!=0&&ul.second!=0)
                sum=sumGreen[lr.first][lr.second]+sumGreen[ul.first-1][ul.second-1]-sumGreen[lr.first][ul.second-1]-sumGreen[ul.first-1][lr.second];
                else if(ul.first!=0&&ul.second==0)
                sum=sumGreen[lr.first][lr.second]-sumGreen[ul.first-1][lr.second];
                else if(ul.first==0&&ul.second!=0)
                sum=sumGreen[lr.first][lr.second]-sumGreen[lr.first][ul.second-1];
                else if(ul.first==0&&ul.second==0)
                sum=sumGreen[ul.first][ul.second];
                }
	else if(channel=='b'){
		if(ul.first!=0&&ul.second!=0)
                sum=sumBlue[lr.first][lr.second]+sumBlue[ul.first-1][ul.second-1]-sumBlue[lr.first][ul.second-1]-sumBlue[ul.first-1][lr.second];
                else if(ul.first!=0&&ul.second==0)
                sum=sumBlue[lr.first][lr.second]-sumBlue[ul.first-1][lr.second];
                else if(ul.first==0&&ul.second!=0)
                sum=sumBlue[lr.first][lr.second]-sumBlue[lr.first][ul.second-1];
                else if(ul.first==0&&ul.second==0)
                sum=sumBlue[ul.first][ul.second];
	}
	return sum;	
}

long stats::getSumSq(char channel, pair<int,int> ul,pair<int,int> lr){
        long sum;
        if(channel=='r'){
                if(ul.first!=0&&ul.second!=0)
                sum=sumsqRed[lr.first][lr.second]+sumsqRed[ul.first-1][ul.second-1]-sumsqRed[lr.first][ul.second-1]-sumsqRed[ul.first-1][lr.second];
                else if(ul.first!=0&&ul.second==0)
                sum=sumsqRed[lr.first][lr.second]-sumsqRed[ul.first-1][lr.second];
                else if(ul.first==0&&ul.second!=0)
                sum=sumsqRed[lr.first][lr.second]-sumsqRed[lr.first][ul.second-1];
                else if(ul.first==0&&ul.second==0)
                sum=sumsqRed[ul.first][ul.second];
                }
        else if(channel=='g'){
                if(ul.first!=0&&ul.second!=0)
                sum=sumsqGreen[lr.first][lr.second]+sumsqGreen[ul.first-1][ul.second-1]-sumsqGreen[lr.first][ul.second-1]-sumsqGreen[ul.first-1][lr.second];
                else if(ul.first!=0&&ul.second==0)
                sum=sumsqGreen[lr.first][lr.second]-sumsqGreen[ul.first-1][lr.second];
                else if(ul.first==0&&ul.second!=0)
                sum=sumsqGreen[lr.first][lr.second]-sumsqGreen[lr.first][ul.second-1];
                else if(ul.first==0&&ul.second==0)
                sum=sumsqGreen[ul.first][ul.second];
                }
        else if(channel=='b'){
                if(ul.first!=0&&ul.second!=0)
                sum=sumsqBlue[lr.first][lr.second]+sumsqBlue[ul.first-1][ul.second-1]-sumsqBlue[lr.first][ul.second-1]-sumsqBlue[ul.first-1][lr.second];
                else if(ul.first!=0&&ul.second==0)
                sum=sumsqBlue[lr.first][lr.second]-sumsqBlue[ul.first-1][lr.second];
                else if(ul.first==0&&ul.second!=0)
                sum=sumsqBlue[lr.first][lr.second]-sumsqBlue[lr.first][ul.second-1];
                else if(ul.first==0&&ul.second==0)
                sum=sumsqBlue[ul.first][ul.second];
        }
        return sum;

}

stats::stats(PNG & im){//构造函数
	//设定统计数组的大小
	int width=im.width();
	int height=im.height();
	sumRed.resize(width,vector<long>(height,0));
	sumGreen.resize(width,vector<long>(height,0));
	sumBlue.resize(width,vector<long>(height,0));

	sumsqRed.resize(width,vector<long>(height,0));
        sumsqGreen.resize(width,vector<long>(height,0));
        sumsqBlue.resize(width,vector<long>(height,0));	
	//设置初始点
	RGBAPixel* pixel=im.getPixel(0,0);
	sumRed[0][0]=pixel->r;
	sumBlue[0][0]=pixel->b;
	sumGreen[0][0]=pixel->g;
	sumsqRed[0][0]=(pixel->r)*(pixel->r);
        sumsqBlue[0][0]=(pixel->b)*(pixel->b);
        sumsqGreen[0][0]=(pixel->g)*(pixel->g);
	
	for(int i=1;i<width;i++){//上边界点
		RGBAPixel* pixel=im.getPixel(i,0);
		sumRed[i][0]=pixel->r+sumRed[i-1][0];
		sumBlue[i][0]=pixel->b+sumBlue[i-1][0];
		sumGreen[i][0]=pixel->g+sumGreen[i-1][0];
		sumRed[i][0]=(pixel->r)*(pixel->r)+sumRed[i-1][0];
                sumBlue[i][0]=(pixel->b)*(pixel->b)+sumBlue[i-1][0];
                sumGreen[i][0]=(pixel->g)*(pixel->g)+sumGreen[i-1][0];
	}
	for(int j=1;j<height;j++){//左边界点
		RGBAPixel* pixel=im.getPixel(0,j);	
		sumRed[0][j]=pixel->r+sumRed[0][j-1];
		sumGreen[0][j]=pixel->g+sumGreen[0][j-1];
		sumBlue[0][j]=pixel->b+sumGreen[0][j-1];
		sumsqRed[0][j]=(pixel->r)*(pixel->r)+sumsqRed[0][j-1];
                sumsqGreen[0][j]=(pixel->g)*(pixel->g)+sumsqGreen[0][j-1];
                sumsqBlue[0][j]=(pixel->b)*(pixel->b)+sumsqGreen[0][j-1];
	}
	for(int i=1;i<width;i++){//中间点
		for(int j=1;j<height;j++){
		RGBAPixel* pixel=im.getPixel(i,j);	
		sumRed[i][j]=sumRed[i-1][j]+sumRed[i][j-1]-sumRed[i-1][j-1]+pixel->r;	
		sumBlue[i][j]=sumBlue[i-1][j]+sumBlue[i][j-1]-sumBlue[i-1][j-1]+pixel->b;
		sumGreen[i][j]=sumGreen[i-1][j]+sumGreen[i][j-1]-sumGreen[i-1][j-1]+pixel->g;
		sumsqRed[i][j]=sumsqRed[i-1][j]+sumsqRed[i][j-1]-sumsqRed[i-1][j-1]+(pixel->r)*(pixel->r);
                sumsqBlue[i][j]=sumsqBlue[i-1][j]+sumsqBlue[i][j-1]-sumsqBlue[i-1][j-1]+(pixel->b)*(pixel->b);
                sumsqGreen[i][j]=sumsqGreen[i-1][j]+sumsqGreen[i][j-1]-sumsqGreen[i-1][j-1]+(pixel->g)*(pixel->g);
		}
	}
}

long stats::getScore(pair<int,int> ul,pair<int,int> lr){
	long double area=rectArea(ul,lr);
	long double diff;
	
	long double sumR=getSum('r',ul,lr);
	long double sumB=getSum('b',ul,lr);
	long double sumG=getSum('g',ul,lr);
	long double sumsqR=getSumSq('r',ul,lr);
	long double sumsqB=getSumSq('b',ul,lr);
	long double sumsqG=getSumSq('g',ul,lr);
	long double diffR=sumsqR-((sumR*sumR)/area);
	long double diffB=sumsqB-((sumB*sumB)/area);
	long double diffG=sumsqG-((sumG*sumG)/area);	
	diff=diffR+diffB+diffG;
	return diff;
}

RGBAPixel stats::getAvg(pair<int,int> ul,pair<int,int> lr){
	long sumR=getSum('r',ul,lr);
	long sumB=getSum('b',ul,lr);
	long sumG=getSum('g',ul,lr);
	long area=rectArea(ul,lr);
	long double redAvg=(double)sumR/(double)area;
	long double greenAvg=(double)sumG/(double)area;
	long double blueAvg=(double)sumB/(double)area;
	
	return RGBAPixel(redAvg,greenAvg,blueAvg);
}

long stats::rectArea(pair<int,int> ul,pair<int,int> lr){
	return (lr.first-ul.first+1)*(lr.second-ul.second+1);
}
