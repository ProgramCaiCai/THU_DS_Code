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


const int N=1600010;
int stk[N];
char oper[N];
int a[N];
int n,m;
int *sp=stk;
char *op=oper;
const char OP_PUSH='p';
const char OP_POP='P';
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    int cur_id=1;
    bool fail=false;
    for(int i=0;i<n;i++){
        while(a[i]>=cur_id) *op++=OP_PUSH,*sp++=cur_id++;
        if(sp==stk||*(sp-1)!=a[i]) {fail=true;break;}
        if(sp-stk<=m) *op++=OP_POP,sp--;
        else {fail=true;break;}
    }

    if(!fail) while(sp!=stk) sp--,*op++=OP_POP;


    if(fail) puts("No");
    else{
        puts("Yes");
    }
    return 0;
}
