#include <iostream>
#include <stdio.h>
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

const int N=100010;
const int BIT_LENGTH = 32;
typedef unsigned int uint;

struct Node{
	Node * a[2];
	Node(){
		a[0]=a[1]=NULL;
	}
};

Node pool[N*BIT_LENGTH+10];
Node *ptr = pool;

Node * newnode(){
	return ptr++;
}
Node *root =newnode();

void insert(Node *root,uint x,uint mask = 0x80000000){
	if(mask==0) return;
	uint key = (x&mask) !=0;
	if(root->a[key]==NULL) {
		root->a[key]=newnode();
	}
	insert(root->a[key],x,mask>>1);
}

uint lookup(Node *root,uint x,uint current = 0,uint mask = 0x80000000){
	if(mask==0) return current;
	uint key = (x&mask) !=0;
	if(root->a[key^1]!=NULL) {
		return lookup(root->a[key^1],x,current+mask,mask>>1);
	}else{
		return lookup(root->a[key],x,current,mask>>1);
	}
}


int n;
uint a[N];

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%u",&a[i]),insert(root,a[i]);

	uint ans = 0;
	for(int i=0;i<n;i++){
		ans = max(ans,lookup(root,a[i]));
	}
	printf("%u\n",ans);

	return 0;
}
