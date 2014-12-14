
#include <stdio.h>
#include <string.h>


const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

const int N=20000010;

struct MonElem{
    int x,pos;
};

struct MonQueue{
    MonElem e[N];
    int lo,hi;
    int lo_no,hi_no;
    MonQueue(){lo=hi=lo_no=hi_no=0;}
    void E(int x){
        while(hi>lo && x>=e[hi-1].x) hi--;
        e[hi].x=x;
        e[hi].pos=hi_no++;
        hi++;
    }
    int M(){
        while(lo<hi&&e[lo].pos<lo_no) lo++;
        return e[lo].x;
    }
    void D(){
        lo_no++;
    }
}mque;

char line[1111];

int n;
int main() {
    scanf("%d",&n);
    getchar();
    long long sum = 0;
    long long sum_t = 0;
    for(int i=0;i<2*n;i++) {
        gets(line);
        int t=0,v=0;
        int o=sscanf(line,"%d %d",&t,&v);
        sum_t+=t;
        if(o==1){
            sum+=(long long)mque.M()*t;
            mque.D();
        }else{
            if(i!=0) sum+=(long long)mque.M()*t;
            mque.E(v);
        }
    }
    printf("%.2lf\n",1.0*sum/sum_t);
    return 0;
}
