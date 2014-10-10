#include <stdio.h>
#include <stdlib.h>
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

const int N=500010;
int a[3][N];
int n;
int ans[N];

int main(){
	memset(ans,-1,sizeof(ans));
	scanf("%d",&n);
	for(int i=0;i<3;i++)
		for(int j=0;j<n;j++) scanf("%d",&a[i][j]);

	int p[3]={0,0,0};
    int alloced=0;
	while(alloced<n){
		for(int i=0;i<3;i++){
			while(p[i]<n && ans[a[i][p[i]]] != -1) p[i]++;
			if(p[i]<n) alloced++,ans[a[i][p[i]]]=i;
		}
	}

	int q;
	scanf("%d",&q);
	printf("%c\n",'A'+ans[q]);
}