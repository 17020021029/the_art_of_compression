
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

/* given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

/* given */
twoDtree::~twoDtree(){
	clear();
}

/* given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}

/* given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){ //利用stats及buildTree辅助构建twoDtree
	stats s=stats(imIn);
	width=imIn.width();
	height=imIn.height();
	pair<int,int> ul=make_pair(0,0);
	pair<int,int> lr=make_pair(width-1,height-1);
	buildTree(s,ul,lr);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {//建立twoDTree
	RGBAPixel pix=s.getAvg(ul,lr);	//stats
	Node* tree=new Node(ul,lr,pix);
	int x1=ul.first;
	int x2=lr.first;
	int y1=ul.second;
	int y2=lr.second;//标记矩形的坐标
	if(x1==x2&&y1==y2) return tree;//跳出条件
	
	pair<int,int> min_newlr;
	pair<int,int> min_newul;//新的标记点坐标
	long min_;//最小标记值
	for(int i=x1;i<x2;i++){
		pair<int,int> newlr=make_pair(i,y2);
		pair<int,int> newul=make_pair(i+1,y1);
		long s1=s.getScore(ul,newlr);
		long s2=s.getScore(newul,lr);//stats
		if(s1+s2<min_){
			min_=s1+s2;
			min_newlr=newlr;
			min_newul=newul;
		}
	}
	for(int j=y1;j<y2;j++){
                pair<int,int> newlr=make_pair(x2,j);
                pair<int,int> newul=make_pair(x1,j+1);
                long s1=s.getScore(ul,newlr);
                long s2=s.getScore(newul,lr);
                if(s1+s2<min_){
                        min_=s1+s2;
                        min_newlr=newlr;
                        min_newul=newul;
                }
        }
	tree->left=buildTree(s,ul,min_newlr);
	tree->right=buildTree(s,min_newul,lr);//继续划分小矩形
return tree;
}

PNG twoDtree::render(){//润色图片
	PNG renderPNG=PNG(width,height);
	render_helper(renderPNG,root);
	return renderPNG;
}
void twoDtree::render_helper(PNG & renderPNG,Node* sub_root){//将树重新整合为图片
	if(sub_root==NULL) return ;
	for(int x=sub_root->upLeft.first;x<=sub_root->lowRight.first;x++){//提取像素点
		for(int y=sub_root->upLeft.second;y<sub_root->lowRight.second;y++){
		*renderPNG.getPixel(x,y)=sub_root->avg;
		}
	}
	render_helper(renderPNG,sub_root->left);
	render_helper(renderPNG,sub_root->right);//继续处理下面节点
} 

void twoDtree::prune(double pct, int tol){//剪枝,pct百分比，tol容忍度
	prune_helper(pct,tol,root);
}
void twoDtree::prune_helper(double pct,int tol,Node* sub_root){//prune_helper
	if(sub_root->left==NULL&&sub_root->right==NULL) return;
	long double num_=0;
	long double total_leaves=get_total_leaves(num_,tol,sub_root,sub_root->avg);
	long double num=0;
	long double leaves_num=get_leaves(num,sub_root);//叶节点个数
	long double p=leaves_num/total_leaves;
	if(p>=pct){
		clear(sub_root->left);
		sub_root=NULL;
		clear(sub_root->right);
		sub_root=NULL;
	}
	else{
	prune_helper(pct,tol,sub_root->left);
	prune_helper(pct,tol,sub_root->right);
	}
}
long double twoDtree::get_leaves(long double& num,Node* sub_root){//获得叶节点个数
	if(sub_root==NULL) return num;
	if(sub_root->left==NULL&&sub_root->right==NULL)	
		num+=1;
	num=get_leaves(num,sub_root->left)+get_leaves(num,sub_root->right);	
}
long double twoDtree::get_total_leaves(long double& num_,int tol,Node* sub_root,RGBAPixel sub_avg){
	int r=sub_root->avg.r;
	int g=sub_root->avg.g;
	int b=sub_root->avg.b;
	if(sub_root==NULL) return num_;
	if(sub_root->left==NULL&&sub_root->right==NULL){
		long p=(r-sub_avg.r)*(r-sub_avg.r)+(g-sub_avg.g)*(g-sub_avg.g)+(b-sub_avg.b)*(b-sub_avg.b);
		if(p<=tol) num_+=1;
	}
	num_=get_total_leaves(num_,tol,sub_root->left,sub_avg)+get_total_leaves(num_,tol,sub_root->right,sub_avg);
	
}

void twoDtree::clear(){//清空节点
	clear(root);
	root=NULL;
	height=0;
	width=0;
}
void twoDtree::clear(Node* sub_root){//clear_helper
	if(!sub_root) return;
	clear(sub_root->left);
	clear(sub_root->right);
	sub_root=NULL;
	delete sub_root;
}

void twoDtree::copy(const twoDtree & orig){//复制节点
	height=orig.height;
	width=orig.width;
	root=copy_node(root);
}
twoDtree::Node* twoDtree::copy_node(Node* tmp){//copy_helper
	if(!tmp) return NULL;

	twoDtree::Node* newnode=new Node(tmp->upLeft,tmp->lowRight,tmp->avg);
	newnode->left=copy_node(tmp->left);
	newnode->right=copy_node(tmp->right);
	return newnode;
}



