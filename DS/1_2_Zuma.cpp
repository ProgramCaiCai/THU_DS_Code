
#include <cstdio>
#include <cstring>

struct Node{
    char c;
    Node *next;
    Node *prev;
};

const int N = 10010;

Node *head=NULL;

Node pool[N<<1];
Node *poolptr=pool;

char s[N];

void prepend(char c){
    Node *tmp = poolptr++;
    tmp->c = c;
    tmp->next = head;
    tmp->prev = NULL;
    if(head) head->prev=tmp;
    head = tmp;
}
Node* prepend_node(Node *ptr,char c){
    Node *prev = ptr->prev;
    Node *next = ptr;
    Node *cur = poolptr++;
    cur->prev = prev;
    cur->next = next;
    cur->c = c;
    if(prev) prev->next = cur;
    if(next) next->prev = cur;
    return cur;
}

Node* nth(int n){
    Node *ret=head;
    while(n--) ret=ret->next;
    return ret;
}

void coalesce(Node *ptr){
    while(ptr){
        int n=1;
        Node *l=ptr,*r=ptr;
        while(l->prev && l->prev->c==ptr->c) l=l->prev,n++;
        while(r->next && r->next->c==ptr->c) r=r->next,n++;
        if(n>=3){
            Node *prev = l->prev;
            Node *next = r->next;
            if(prev) prev->next = next;
            if(next) next->prev = prev;
            if(prev->c==next->c) {ptr=next;}
            else break;
        }else break;
    }
}

#ifdef __linux__
#define putchar putchar_unlocked
#endif

const int SZ = 1<<22;
struct fastio{

    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}_io;


void output(){
    if(head->next->c=='*') putchar('-');
    else{
        for(Node *cur=head->next;cur->c!='*';cur=cur->next) putchar(cur->c);
    }
}

int main() {
    prepend('*');
    gets(s);
    for(int i=strlen(s)-1;i>=0;i--) {
        prepend(s[i]);
    }
    prepend('.');


    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int p;
        char c;
        scanf(" %d %c ",&p,&c);
        Node *cur=prepend_node(nth(p+1), c);
        coalesce(cur);
        output();
        putchar('\n');
    }
    return 0;
}