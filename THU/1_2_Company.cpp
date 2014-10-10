#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template<class K,class V>
struct hashmap{
	K *keys;
	V *values;
	char *vis;
	int size;
	int used;
	int capacity;
	int (*hash)(K);
private:
	void shallowcopy(const hashmap &other){
		keys = other.keys;
		values = other.values;
		vis = other.vis;
		size = other.size;
		used = other.used;
		capacity = other.capacity;
	}
	int locate(int x){int h=(hash(x)&0x7fffffff)%capacity;while(vis[h] && keys[h]!=x) h=(h+1)%capacity; return h;}
	void resize(int n,bool copy=true){
		hashmap<K,V> newtable = hashmap<K,V>(n,hash);
		if(copy) for(int i=0;i<capacity;i++) if(vis[i]==1) newtable.set(keys[i],values[i]);
		delete[] keys;
		delete[] values;
		delete[] vis;
		shallowcopy(newtable);
		newtable.keys=NULL;
	}
public:
	hashmap(int initialcap,int (*_hash)(K)){
		hash=_hash;
		size=used=0;
		capacity=initialcap;
		keys=new K[capacity];
		values=new V[capacity];
		vis=new char[capacity];
		memset(vis,0,sizeof(char)*capacity);
	}

	~hashmap(){
		if(keys){
			delete[] keys;
			delete[] values;
			delete[] vis;
		}
	}
	V get(K key,V _default){
		int p = locate(key);
		if(vis[p]!=1) return _default;
		else return values[p];
	}
	void clear(){
		resize(8,false);
	}
	void del(K key){
		if(size<capacity/6) resize(capacity/2);
		int p=locate(key);
		if(vis[p]==1) {
			vis[p]=2,size--;
		}
	}
	void set(K key,V value){
		if(used>capacity/2) resize(capacity*2-1); 
		int p= locate(key);
		if(!vis[p]) vis[p]=1,keys[p]=key,size++,used++;
		values[p]=value;
	}
};


const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;


int hash(int x){
	return (x<<3)^(x>>2);
}
int n,m;
hashmap<int,int> ht(8,hash);
int main(){

	scanf("%d%d",&n,&m);
	int ans=0;
	while(m--){
		char c;
		scanf(" %c",&c);
		if(c=='I'){
			int x,y;
			scanf("%d%d",&x,&y);
			ht.set(x,y);
		}else if(c=='O'){
			int x;
			scanf("%d",&x);
			ht.del(x);
		}else if(c=='C'){
			ht.clear();
		}else if(c=='N'){
			ans+=ht.size;
		}else if(c=='Q'){
			int x;
			scanf("%d",&x);
			ans+=ht.get(x,-1);
		}
	}
	printf("%d\n",ans);

}
