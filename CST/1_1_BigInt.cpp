#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

const int C=4;//Packed bit

const int M[]={1,10,100,1000,10000,100000};

const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;



struct Accumulator{
    int x;
    int d;
    Accumulator():x(0),d(0){}
    void append(int y){x+=M[d]*y;d++;}
    void clear(){x=d=0;}
};


struct Formatter{
    char smallbuf[C+5];
    char buf[510];
    int bufn;

    Formatter(){memset(buf,0,sizeof(buf)),bufn=0;}
    void copytobuf(){
        for(int i=0;smallbuf[i];i++) buf[bufn++]=smallbuf[i];
    }
    char * format(const int a[],int n){
        bufn=0;
        sprintf(smallbuf,"%d",a[n-1]);
        copytobuf();
        for(int i=n-2;i>=0;i--) {
            sprintf(smallbuf,"%0*d",C,a[i]);
            copytobuf();
        }
        buf[bufn]='\0';
        return buf;
    }
};

struct BigInteger{
    int a[200];
    int n;
    BigInteger(){memset(a,0,sizeof(a));}
    BigInteger(char *s) {
        n=0;
        int len = strlen(s);
        Accumulator accu;
        for(int i=len-1;i>=0;i--){
            accu.append(s[i]-'0');
            if(accu.d==C) {a[n++]=accu.x;accu.clear();}
        }
        if(accu.x!=0) a[n++]=accu.x;
    }
    BigInteger operator*(const BigInteger &b) {
        BigInteger ret = BigInteger();
        ret.n = n+ b.n;
        for(int i=0;i<n;i++)
            for(int j=0;j<b.n;j++) ret.a[i+j]+=a[i]*b.a[j];
        ret.a[ret.n]=0;
        for(int i=0;i<ret.n;i++) {
            ret.a[i+1]+=ret.a[i]/M[C];
            ret.a[i]%=M[C];
        }
        if(ret.a[ret.n]!=0) ret.n++;
        while(ret.n>1 && ret.a[ret.n-1]==0) ret.n--;
        return ret;
    }

    void print(){
        for(int i=0;i<n;i++)  printf("%d ",a[i]);
        putchar('\n');
    }
};


int n;
char a[222],b[222];
Formatter f;
int main() {

    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%s %s",a,b);
        BigInteger c = BigInteger(a)*BigInteger(b);
        char *out = f.format(c.a,c.n);
        printf("%s\n",out);
    }
    return 0;
}