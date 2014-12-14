#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

typedef long long LL;
const int N=100010;
int w[N];

struct Node{
	Node *l,*r;
	LL sum;
	int num;
	void fix(){
		sum=num=0;
		if(l) sum+=l->sum,num+=l->num;
		if(r) sum+=r->sum,num+=r->num;
	}
};
Node pool[N*150];
Node *ptr=pool;

Node * newnode(){
	//Node *ptr = new Node;
	ptr->l=ptr->r=NULL;
	ptr->sum = 0;
	ptr->num = 0;
	return ptr++;
}

Node * copyof(const Node *oldnode){
	Node *ptr=newnode();
	ptr->l=oldnode->l;
	ptr->r=oldnode->r;
	ptr->sum = oldnode->sum;
	ptr->num = oldnode->num;
	return ptr;
}

Node *nil=newnode();

Node * left_or_nil(const Node *x){
	if(x->l==NULL) return nil;
	return x->l;
}
Node * right_or_nil(const Node *x){
	if(x->r==NULL) return nil;
	return x->r;
}
Node* add(int x,int times,int l,int r,const Node *rt){
	if(l==x && x==r){
		Node *ret=copyof(rt);
		ret->sum += x*times;
		ret->num += times;
		return ret;
	}
	int m = (l+r)>>1;
	if(x<=m) {
		Node *ret = copyof(rt);
		ret->l=add(x,times,l,m,left_or_nil(rt));
		ret->fix();
		return ret;
	}else {
		Node *ret = copyof(rt);
		ret->r = add(x,times,m+1,r,right_or_nil(rt));
		ret->fix();
		return ret;
	}
}
LL ksum(int k,int l,int r,Node *rt){
	//printf("%d [%d %d]\n",k,l,r);
	if(rt->num<=k) return rt->sum;
	if(l==r) {
		return l*min(k,rt->num);
	}
	Node *left = left_or_nil(rt);
	Node *right = right_or_nil(rt);
	int m = (l+r)>>1;
	LL ret = ksum(min(k,left->num),l,m,left);
	if(k-left->num>0) ret+=ksum(k-left->num,m+1,r,right);
	return ret;
}

struct Inteval{
	int l,r,w;
};
bool cmp_interval(const Inteval &a,const Inteval &b){
	return a.l<b.l;
}


template<class T>
struct Vector{
	int *a;
	int n;
	int cap;
	Vector(){
		cap=2;
		a=new int[cap];
		n=0;
	}
	~Vector(){
		delete[] a;
	}
	void resize(int cap2){
		int *b = new int[cap2];
		for(int i=0;i<n;i++) b[i]=a[i];
		delete[] a;
		a=b;
		cap=cap2;
	}
	void push_back(const T &x){
		if(n+1>cap) resize(cap*2);
		a[n++]=x;
	}
	T& operator[](int x){
		return a[x];
	}
};



Node * target[N];
Vector<int> event[N];
int m,n;
int main() {
	scanf("%d %d",&m,&n);
	target[0]=nil;
	int maxx=0;
	for(int i=0;i<m;i++){
		int l,r,x;
		scanf("%d %d %d",&l,&r,&x);
		event[l].push_back(x);
		event[r+1].push_back(-x);
		maxx=max(maxx,x);
	}
	for(int i=1;i<=n;i++) {
		Node *tmp = target[i-1];
		for(int j=0;j<event[i].n;j++) {
			int val = event[i][j];
				if(val>0) tmp=add(val,1,0,maxx,tmp);
				else tmp=add(-val,-1,0,maxx,tmp);
		}
		target[i]=tmp;
	}
	LL pre = 1;
	for(int i=1;i<=n;i++) {
		int x,a,b,c;
		scanf("%d %d %d %d",&x,&a,&b,&c);
		int k = (a*pre+b)%c+1;
		pre = ksum(k,0,maxx,target[x]);
		printf("%lld\n",pre);
	}
}
