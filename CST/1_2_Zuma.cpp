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

char s[22222];
int lens;
int n;


void insert(int pos,char c){
    for(int i=lens;i>=pos;i--) s[i+1]=s[i];
    lens++;
    s[pos]=c;
}


void coalesce(int l,int r,int ic=1){
    int nl=l,nr=r,c=ic;
    while(nl-1>=0 && s[nl-1]==s[nl]) nl--,c++;
    while(nr+1<lens &&  s[nr+1]==s[nr]) nr++,c++;

    if(c>=3) {
        if(nl>=1 && s[nl-1]==s[nr+1]) {
            coalesce(nl-1, nr+1, 2);
        }else {
            coalesce(nl-1, nr+1, -100);
        }
    }else{

        int gap = r-l-1;
        //printf("l=%d r=%d gap=%d\n",l,r,gap);
        if(gap>0){
            for(int i=r;i<lens;i++) s[i-gap]=s[i];
            lens -= r-l-1;
            s[lens]='\0';
        }
    }

}



int main() {
    gets(s);
    lens=strlen(s);

    if(lens>=1 && s[lens-1]=='\r') s[lens-1]='\0',lens--;
    scanf("%d",&n);

    while(n--){
        int pos;
        char c;
        scanf(" %d %c",&pos,&c);
        insert(pos,c);
        coalesce(pos, pos, 1);
        if(lens!=0) puts(s);
        else puts("-");
    }

    return 0;
}