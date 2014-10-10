#include <stdio.h>

#ifdef __linux__
#define putchar putchar_unlocked
#endif

const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;


const int N=2000010;


struct MonElem{
    int x,pos;
};

struct Queue{
    int a[N];
    int lo,hi;
    Queue(){lo=hi=0;}
    void E(int x){a[hi++]=x;}
    int D() {return a[lo++];}
    int M() {int r=a[lo]; for(int i=lo;i<hi;i++) r=a[i]>r?a[i]:r; return r;}
}que;

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


int n;
int main(){
    scanf("%d",&n);
    while(n--){
        char c;
        int x;
        scanf(" %c",&c);

        if(c=='E') scanf(" %d",&x),que.E(x),mque.E(x);
        else if(c=='D') printf("%d\n",que.D()),mque.D();
        else if(c=='M') printf("%d\n",mque.M());
    }

}
