#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;


const int MAXN = 500000+10;
const int MAXE = 1200000*2 + 10;

template<class T>
struct Pool{
	T pool[MAXE];
	T *ptr;
	Pool(){
		ptr=pool;
	}
	T* getnew(){
		return ptr++;
	}
};
struct Edge{
	int to;
	Edge *next;
};
Pool<Edge> pool;

const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

struct Graph{
	Edge **head;
	int *w;
	int N;
	Graph(int n){
		head = new Edge* [n];
		w = new int [n];
		memset(head,0,sizeof(Edge*)*n);
		memset(w,0,sizeof(int)*n);
		N = n;
	}
	~Graph(){
		delete [] head;
		delete [] w;
	}

	void add_edge(int s,int t){
		Edge *e = pool.getnew();
		e->to=t;
		e->next=head[s];
		head[s] = e;
	}
};
class SCC{
private:
	int *dfn,*low,*stk;
	bool *vis,*instack;
	int *sp;
	int idx,scidx;
	const Graph &g;
	void tarjan(int x){
		vis[x]=1;
		dfn[x]=low[x]=++idx;
		*sp++ = x;
		instack[x]=1;
		for(Edge *e=g.head[x];e;e=e->next){
			int y = e->to;
			if(!vis[y]){
				tarjan(y);
				low[x] = min(low[x],low[y]);
			}else if(instack[y]){
				low[x] = min(low[x],dfn[y]);
			}
		}
		if(dfn[x] == low[x]){
			int y = -1;
			while(x!=y){
				y= *(--sp);
				scc[y]=scidx;
				instack[y]=0;
			}
			scidx++;
		}
	}

public:
	int *scc,*newid;
	SCC(const Graph &g):g(g){
		dfn = new int[g.N];
		low = new int[g.N];
		scc = new int[g.N];
		stk = new int[g.N];
		vis = new bool[g.N];
		instack = new bool[g.N];
		sp = stk;
		idx=0;
		scidx = 0;

		memset(scc,-1,g.N*sizeof(int));
		memset(vis,0,g.N*sizeof(bool));
		memset(instack,0,g.N*sizeof(bool));
		for(int i=0;i<g.N;i++) {
			if(!vis[i]) tarjan(i);
		}

		delete[] dfn;
		delete[] low;
		delete[] stk;
		delete[] vis;
		delete[] instack;
	}
	~SCC(){
		delete[] scc;
	}

	int max_id() const {return scidx;}
	Graph compress() {
		Graph ret(max_id());
		//for(int i=0;i<g.N;i++) printf("%d ",scc[i]);
		//putchar('\n');
		//printf("%d\n",scidx);

		for(int i=0;i<g.N;i++){
			for(Edge *e=g.head[i];e;e=e->next){
				int j = e->to;
				if(scc[i] == scc[j]) continue;
				ret.add_edge(scc[i],scc[j]);
			}
		}
		for(int i=0;i<g.N;i++) ret.w[scc[i]]+=g.w[i];
		return ret;
	}
};
template<class T>
class Queue{
private:
	T *a;
	int n;
	int st,ed;
	int cap;
	int add1(int x){
		if(x<cap-1) return x+1;
		else return 0;
	}
public:
	Queue(int cap):cap(cap){
		a= new T[cap];
		n = 0;
		st = ed = 0;
	}
	void push(int x){
		a[ed] = x;
		ed = add1(ed);
		n++;
	}
	int front(){
		return a[st];
	}
	void pop(){
		st=add1(st);
		n--;
	}
	int size(){return n;}
	bool empty(){return n==0;}
};
class SPFA{
private:
	const Graph &g;
public:
	int *d;
	SPFA(const Graph &g,int s):g(g){
		Queue<int> q(g.N+1);
		bool *vis;
		d = new int [g.N+1];
		vis = new bool [g.N+1];
		memset(d,0x1f,(g.N+1)*sizeof(int));
		memset(vis,0,(g.N+1)*sizeof(bool));
		d[s] = g.w[s];
		q.push(s);
		while(!q.empty()){
			int x = q.front();
			q.pop();
			vis[x]=0;
			for(Edge *e = g.head[x];e;e=e->next){
				int to = e->to;
				if( d[x]+g.w[to]<d[to]){
					d[to]=d[x]+g.w[to];
					if(!vis[to]) q.push(to),vis[to]=1;
				}
			}
		}
		delete[]  vis;
	}
	~SPFA(){
		delete[] d;
	}

};

int n,m;
char moon[MAXN];


int main() {
	scanf("%d %d",&n,&m);
	scanf("%s",moon);
	Graph g(n);
	for(int i=0;i<m;i++){
		int from,to;
		scanf("%d %d",&from,&to);
		g.add_edge(from,to);
	}
	for(int i=0;i<n;i++) if(moon[i]=='M') g.w[i]=1;

	SPFA spfa(g,0);

	int ans1 = spfa.d[n-1];

	for(int i=0;i<n;i++) g.w[i]=0;
	for(int i=0;i<n;i++) if(moon[i]=='m') g.w[i]=-1;
	SCC scc(g);
	Graph gc = scc.compress();
	SPFA spfa2(gc,scc.scc[0]);

	int ans2 = -spfa2.d[scc.scc[n-1]];

	printf("%d\n",ans1);
	printf("%d\n",ans2);
}
