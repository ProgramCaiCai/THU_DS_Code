#include <stdio.h>

struct Node{
	int value;
	Node *prev,*next;
};

const int N=1010;
int n,m;
Node pool[N];
int a[N];
Node *poolptr=pool;

Node *current;
int main(int argc, char const *argv[]){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	current=poolptr++;
	current->value=a[0];
	current->prev=current;
	current->next=current;

	for(int i=1;i<n;i++){
		int steps = (m-1)%i;
		Node *now = poolptr++;
		now->value = a[i];
		for(int j=0;j<steps;j++) current=current->next;
		Node *p = current->next;
		current->next=now;
		now->prev = current;
		now->next = p ;
		p->prev = now;
		current=now;

	}

	for(int i=0;i<n;i++){
		printf("%d ",current->value);
		current=current->prev;
	}

	return 0;
}