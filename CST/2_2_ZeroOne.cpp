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

const int N=1000100;
const int BIT_LENGTH = 64;
typedef unsigned int uint;

struct Node{
	bool color;
	Node * a[2];
	Node(){
		a[0]=a[1]=NULL;
		color = 0;
	}
	bool has_white_child() const{
		bool ret = false;
		if(a[0]) ret|=a[0]->color==0;
		if(a[1]) ret|=a[1]->color==0;
		return ret;
	}
};

//Node pool[N*32+10];
//Node *ptr = pool;

Node * newnode(){
	return new Node();
}
Node *root =newnode();


void insert(Node *root,char *s){
	if(*s=='\0') return;
	int key = *s=='1';
	if(root->a[key]==NULL) root->a[key]=newnode();
	insert(root->a[key],s+1);
	root->color=root->has_white_child();
}

void freeTree(Node *root){
	if(root->a[0]) freeTree(root->a[0]);
	if(root->a[1]) freeTree(root->a[1]);
	delete root;
}

int n;

char s[111];
bool result[N];
int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",s);
		insert(root,s);
		result[i]=root->color;
	}

	result[n]=result[n-1]^1;
	int s = 0;
	int r = result[0];
	for(int i=0;i<n+1;i++){
		if(result[i]!=r){
			printf("%s %d %d\n",r?"Adam":"Eve",s+1,i-1+1);
			s=i;
			r=result[i];
		}
	}
	freeTree(root);
	return 0;
}
