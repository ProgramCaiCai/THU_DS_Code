#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int N=200010;
namespace algo {
    template<class T>
    void swap(T *a, T *b) {
        T t = *a;
        *a = *b;
        *b = t;
    }

    template<class T>
    void sort(T *begin, T *end) {
        int n = end - begin;
        if (n <= 1) return;
        else {
            swap(begin, begin + rand() % n);
            T *l = begin, *r = end;
            T p = *l;
            while (true) {
                while (*(++l) < p) if (l == end) break;
                while (p < *(--r)) if (r == begin) break;
                if (l >= r) break;
                swap(l, r);
            }
            swap(begin, r);
            sort(begin, r);
            sort(l, end);
        }
    }
};
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
const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

int x[N],y[N];
Line l[N];
int n,m;

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

int main() {

    srand(time(0));
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&x[i]);
    for(int i=0;i<n;i++) scanf("%d",&y[i]);
    algo::sort(x,x+n);
    algo::sort(y,y+n);
    for(int i=0;i<n;i++) l[i].x=x[i],l[i].y=y[i];

    scanf("%d",&m);
    while(m--){
        Point tmp;
        scanf("%d %d",&tmp.x,&tmp.y);
        printf("%d\n",getid(tmp));
    }

    return 0;
}