#include <stdio.h>


const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

typedef long long LL;


struct point{
	LL x,w;
};
LL w[32768+10];
int n;
point p[32768+10];
int pn;



template<class Num>
Num abs(Num x){
	return x>0?x:-x;
}


LL calc(int x){
	LL ret=0;
	for(int i=0;i<pn;i++) ret+=abs(x-p[i].x)*p[i].w;
	return ret;
}



int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		int x,y;
		scanf("%d %d",&x,&y);
		w[x]+=y;
	}
	pn=0;
	for(int i=0;i<=32768;i++) if(w[i]!=0) p[pn].x=i,p[pn].w=w[i],pn++;

	int l=p[0].x,r=p[pn-1].x;
	int maxtime=100;
	while(l<=r && maxtime!=0){
		maxtime--;
		int len = r-l+1;
		int m =  l + len/3;
		int mm = r - len/3;
		LL vm = calc(m);
		LL vmm = calc(mm);
		if(vm<vmm) r=mm;
		else l=m;
	}
	int ansid=l;
	LL ans=calc(l);
	for(int i=ansid+10;i>=ansid-10;i--) {
		LL r=calc(i);
		if(r<=ans) ans=r,ansid=i;
	}

	printf("%d\n%lld\n",ansid,ans);

	return 0;
}
