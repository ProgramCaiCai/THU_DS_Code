#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;


const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

const int N=10000+10;
int n;

int a[N],s[N],m[N],o[N];
char vis[N];
int *sp=s,*op=o;
int mx;

int main() {
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    mx=n;

    m[n-1]=n-1;
    for(int i=n-2;i>=0;i--) m[i]=a[i]>a[m[i+1]]?i:m[i+1];

    int p=0;
    while(p<n){
        while(sp!=s && a[m[p]]<*(sp-1)) *op++=*--sp;
        *op++=a[m[p]];
        for(int i=p;i<m[p];i++) *sp++=a[i];
        p=m[p]+1;
    }
    while(sp!=s) *op++=*--sp;

    for(int i=0;i<n;i++){
        if(i) putchar(' ');
        printf("%d",o[i]);
    }
    putchar('\n');

    return 0;
}