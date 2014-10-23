#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point{
	int x,y;
	Point():x(0),y(0){}
	Point(int x_,int y_):x(x_),y(y_){}
	Point operator-(const Point &b) const{
		return Point(x-b.x,y-b.y);
	}
	bool cross(const Point &b) const {
		long long tmp1 = (long long)x*b.y;
		long long tmp2 = (long long)y*b.x;
		return (tmp1-tmp2)>0;
	}
};
struct Line{
	int x,y;
	bool judge(const Point &c) const{
		Point a = Point(x,0);
		Point b = Point(0,y);
		Point ca = a - c;
		Point cb = b - c;
		return ca.cross(cb);
	}
};

const int N=100010;
const int M=1000010;

Line l[N];
int n,m;

const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;


int getid(Point p){
	int left=0,right=n-1;
	int mid;
	int ret=0;

	if(l[0].judge(p)) return 0;
	if(!l[n-1].judge(p)) return n;

	while(left<=right){
		mid=(left+right)>>1;
		if(l[mid].judge(p)){
			right=mid-1;
		}else ret=mid+1,left=mid+1;
	}
	return ret;
}



int main(){

	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d %d",&l[i].x,&l[i].y);
	for(int i=0;i<m;i++){
		Point p;
		scanf("%d %d",&p.x,&p.y);
		printf("%d\n",getid(p));
	}
}