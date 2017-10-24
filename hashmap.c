#include<stdlib.h>
#define BUCKETS 100000
struct hashmap {
    //A node in a singly-linked list
    struct node {
        int key;
        void* val;
        struct node* nxt;
    } *map[BUCKETS];
}hm;

struct node* create_node(int i,void* v,struct node* n) {
    struct node* nd = (struct node*)malloc(sizeof(struct node));
    nd->key=i;
    nd->val=v;
    nd->nxt=n;
    return nd;
}
void init_hashmap(struct hashmap *hm) {
    for(int i=0;i<BUCKETS;hm->map[i++]=(struct node*)malloc(sizeof(struct node)));
}
int get_bkt(int key) {
    return (key%BUCKETS+BUCKETS)%BUCKETS;
}
void insert(struct hashmap *hm, int key, void* val) {
    int bkt=get_bkt(key);
    struct node **cur=&hm->map[bkt];
    while(*cur&&(*cur)->key!=key) cur=&(*cur)->nxt;
    if(*cur) (*cur)->val=val;
    else *cur=create_node(key,val,0);
}
void* retrieve(struct hashmap *hm, int key) {
    int bkt=get_bkt(key);
    struct node* cur=hm->map[bkt];
    while(cur&&cur->key!=key) cur=cur->nxt;
    return (void*)cur?cur->val:0;
}
void del(struct hashmap *hm, int key) {
    int bkt=get_bkt(key);
    struct node** cur=&hm->map[bkt];
    while((*cur)&&(*cur)->key!=key) cur=&(*cur)->nxt;
    if(*cur) {
        struct node* tmp=*cur;
        cur=&(*cur)->nxt;
        free(tmp);
    }
}
