#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>


namespace algo {
    template<class T> void swap ( T *a, T *b ) {T t=*a; *a=*b; *b=t;}

    template<class T>
    void bsort(T* begin,T* end){
        int n= end-begin;
        bool flag=true;
        T *pend = end-1;
        while(flag){
            flag=false;
            for(T* p=begin;p<pend;p++) if(*(p+1)<*p) swap(p,p+1),flag=true;
            pend--;
        }
    };
    template<class T,class C>
    void bsort(T* begin,T* end,C less){
        bool flag=true;
        T *pend = end-1;
        while(flag){
            flag=false;
            for(T* p=begin;p<pend;p++) if(less(*(p+1),*p)) swap(p,p+1),flag=true;
            pend--;
        }
    };


    template<class T> void sort(T *begin,T *end){
        int n = end-begin;
        if(n<=8) bsort(begin,end);
        else{
            swap(begin,begin+rand()%n);
            T *l=begin,*r=end;
            T p =*l;
            while(true){
                while(*(++l)<p) if(l==end) break;
                while(p<*(--r)) if(r==begin) break;
                if(l>=r) break;
                swap(l,r);
            }
            swap(begin,r);
            sort(begin,r);
            sort(l,end);
        }
    };

    template<class T,class C> void sort(T *begin, T *end,C less){
        int n = end-begin;
        if(n<=8) bsort(begin,end,less);
        else{
            swap(begin,begin+rand()%n);
            T *l=begin,*r=end;
            T p =*l;
            while(true){
                while(less(*(++l),p)) if(l==end) break;
                while(less(p,*(--r))) if(r==begin) break;
                if(l>=r) break;
                swap(l,r);
            }
            swap(begin,r);
            sort(begin,r,less);
            sort(l,end,less);
        }
    };

    template<class T> T* lower_bound(T *begin,T *end,T value){
        T* ret=begin;
        while(begin<end){
            int n = end - begin;
            T *mid = begin+(n>>1);
            if(*mid<value) ret=begin=mid+1;
            else end=mid;
        }
        return ret;
    };

    template<class T> T* upper_bound(T *begin, T *end,T value){
        T* ret=begin;
        while(begin<end){
            int n = end-begin;
            T *mid = begin+(n>>1);
            if(!(value<*mid)) ret=begin=mid+1;
            else end=mid,ret=mid;
        }
        return ret;
    }
}
using namespace algo;

const int N =500010;
int n,m;
int a[N];

const int SZ = 1<<20;
struct fastio{

    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}_io;


int main() {
    srand(time(0));
    scanf("%d%d",&n,&m);

    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    sort(a,a+n);

    for(int i=0;i<m;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",upper_bound(a,a+n,r)-lower_bound(a,a+n,l));
    }
    return 0;
}