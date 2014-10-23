#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


const int N=1000010;
class Stack{
private:
	int a[N];
	int n;
public:
	Stack(){n=0;}
	bool empty(){return n==0;}
	void push(int x){a[n++]=x;}
	int pop(){return a[--n];}
	int top(){return a[n-1];}
};

class Queue{
private:
	Stack s1,s2;
	void maintain(){if(s2.empty()){while(!s1.empty()) s2.push(s1.pop());}}
public:
	Queue(){}
	void enqueue(int x){s1.push(x);}
	int dequeue(){maintain(); return s2.pop();}
	int front(){maintain(); return s2.top();}
};


class Queap{
	Queue q1,q2;
public:
	Queap();
	void enqueap(int);
	int dequeap();
	int min();
private:
};


int main()
{
	return 0;
}
