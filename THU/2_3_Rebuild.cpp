#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const int N=500010;

int pre[N],in[N];
int n;

template<class T>
struct buffer{
	T arr[N];
	int n;
	bool flag;
	buffer(){n=0;flag=false;}
	void append(T x) {arr[n++]=x;}
	void setflag(){flag=true;}
};



void debug(int *begin,int *end,char *prop){
	puts(prop);
	for(int *p = begin;p<end;p++) printf("%d ",*p);
	puts("");
}

void build(buffer<int> &out,int *prebegin,int *preend,int *inbegin,int *inend){

	//debug(prebegin,preend,"pre:");
	//debug(inbegin,inend,"in:");

	if(preend-prebegin<=1) {
		if(preend-prebegin==1) {
           if(*prebegin==*inbegin) out.append(*prebegin);
           else out.setflag();
        }
		return;
	}

	int root = *prebegin;
	int *pos=NULL;
	for(int *p=inbegin;p<inend;p++) if(*p==root) {pos = p;break;}
	if(pos!=NULL){
		int leftlen = pos-inbegin;
		build(out,prebegin+1,prebegin+leftlen+1,inbegin,pos);
		build(out,prebegin+leftlen+1, preend, pos+1,inend);
		out.append(root);
	}else out.setflag();
}

buffer<int> out;

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&pre[i]);
	for(int i=0;i<n;i++) scanf("%d",&in[i]);
	build(out,pre,pre+n,in,in+n);
	if(out.flag) printf("-1\n");
	else{
		for(int i=0;i<n;i++) {
			if(i) putchar(' ');
			printf("%d",out.arr[i]);
		}
		putchar('\n');
	}

}
