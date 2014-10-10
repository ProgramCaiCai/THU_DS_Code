#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#ifdef __linux__
#define getchar getchar_unlocked
#endif

const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
    inline void readint(int &x){
        register int c = getchar();
        x = 0;
        int neg = 0;
        for(; ((c<48 || c>57) && c != '-'); c = getchar());
        if(c=='-') {
            neg = 1;
            c = getchar();
        }
        for(; c>47 && c<58 ; c = getchar()) {
            x = (x<<1) + (x<<3) + c - 48;
        }
        if(neg) x = -x;
    }
}io;

namespace algo {
    template<class T> void swap ( T *a, T *b ) {T t=*a; *a=*b; *b=t;}
    template<class T,class C> void sort(T *begin, T *end,C less){
        int n = end-begin;
        if(n<=1) return;
        else{
            swap(begin,begin+rand()%n);
            T *l=begin,*r=end;
            T p =*l;
            while(true){
                while(less(*(++l),p)) if(l==end) break;
                while(less(p,*(--r))) if(r==begin) break;
                if(l>=r) break;
                swap(l,r);
            }
            swap(begin,r);
            sort(begin,r,less);
            sort(l,end,less);
        }
    };
}
using namespace algo;

struct point{int x,y;};

bool cmp_by_x(const point &p1,const point &p2){
    return p1.x<p2.x;
}

typedef long long LL;

LL solve(int *p,int *aux,int n){
    if(n<=1) return 0;
    int piv=rand()%n;
    LL ret=0;
    LL cnt_below=0;
    for(int i=0;i<piv;i++) {
        if(p[i]<p[piv]) cnt_below++,ret++;
        else ret+=cnt_below;
    }
    for(int i=piv+1;i<n;i++) {
        if(p[i]<p[piv]) cnt_below++;
        else ret+=cnt_below,ret++;
    }

    int *s=aux,*e=aux+cnt_below+1;
    for(int i=0;i<piv;i++) if(p[i]<p[piv]) *s++=p[i]; else *e++=p[i];
    for(int i=piv+1;i<n;i++) if(p[i]<p[piv]) *s++=p[i]; else *e++=p[i];


    int nleft = s-aux;
    ret+= solve(aux,p,nleft);
    ret+= solve(aux+nleft+1,p+nleft+1,n-nleft-1);
    return ret;
}

int main() {
    srand(time(0));
    int n;
    scanf("%d",&n);
    point *p = new point[n+1];
    int *ys= new int[n+1];
    int *ysaux = new int[n+1];

    for(int i=0;i<n;i++) {
        io.readint(p[i].x);
        io.readint(p[i].y);
    }
    sort(p,p+n,cmp_by_x);
    for(int i=0;i<n;i++) ys[i]=p[i].y;
    printf("%lld\n",solve(ys,ysaux,n));
}
