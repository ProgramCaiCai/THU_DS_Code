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


const int N=4000010;


int n,pre[N],post[N],out[N];
int *op=out;


void build(int *l1,int *r1,int *l2,int *r2){
    if(r1==l1) {*op++=*l1; return;}
    if(*l1==*r2){
        int M=*l1;
        l1++;
        r2--;
        int L=*l1;
        int R=*r2;
        int *brk1,*brk2;
        for(int *p=l1;p<=r1;p++) if(*p==R) {brk1=p;break;}
        for(int *p=l2;p<=r2;p++) if(*p==L) {brk2=p;break;}
        build(l1,brk1-1,l2,brk2);
        *op++=M;
        build(brk1,r1,brk2+1,r2);
    }
}



int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&pre[i]);
    for(int i=0;i<n;i++) scanf("%d",&post[i]);

    if(pre[0]!=post[n-1]) while(1);


    build(pre,pre+n-1,post,post+n-1);
    for(int *p=out;p<op;p++) {
        if(p!=out) putchar(' ');
        printf("%d",*p);
    }
    putchar('\n');
}
