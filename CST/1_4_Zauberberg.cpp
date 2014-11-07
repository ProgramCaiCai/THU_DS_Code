#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace algo {
    template<class T> void swap ( T *a, T *b ) {T t=*a; *a=*b; *b=t;}

    template<class T> void sort(T *begin,T *end) {
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
}

const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

const int N=100010;
struct Animal{
    int h;
    char status;
    bool operator<(const Animal &b) const{return h<b.h;}
}animals[N];




int n,H,m;
int posidx[N],negidx[N];
int posn=0,negn=0;

int main() {
    scanf("%d %d",&n,&H);
    for(int i=0;i<n;i++) scanf(" %d %c",&animals[i].h,&animals[i].status);
    algo::sort(animals,animals+n);

    for(int i=0;i<n;i++) if(animals[i].status=='+') posidx[posn++]=animals[i].h;else negidx[negn++]=animals[i].h;

    scanf("%d",&m);
    while(m--){
        double p_hit,p_miss;
        scanf("%lf %lf",&p_hit,&p_miss);
        int pos_kill = ceil(p_hit*posn);
        int neg_kill = floor(p_miss*negn);
        int lbd,ubd;

        if(pos_kill==0) ubd=H;
        else if(pos_kill==posn) ubd=posidx[0];
        else{
            ubd = posidx[posn-pos_kill];
        }

        if(neg_kill==0) lbd = negidx[negn-1]+1;
        else if(neg_kill==negn) lbd = 0;
        else{
            int p = negn-neg_kill-1;
            lbd=negidx[p]+1;
        }
        if(lbd<=ubd && lbd<=H && ubd<=H) printf("%d %d\n",lbd,ubd);
        else printf("-1\n");
    }
    return 0;
}