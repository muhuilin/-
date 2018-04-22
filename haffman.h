/*************************************************************************
	> File Name: haffman.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 11时58分56秒
    ┏┳━━━━━━━━━━┓
    ┃┃██████████┃
    ┣┫██████┏━┓█┃
    ┃┃█████┃陈┃█┃
    ┣┫█████┃独┃█┃
    ┃┃█████┃秀┃█┃
    ┣┫█████┃传┃█┃
    ┃┃██████┗━┛█┃
    ┣┫██████████┃
    ┃┃██████████┃ 
    ┗┻━━━━━━━━━━┛
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a,b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct Node {
    char data;
    int val;
    struct Node *lchild, *rchild;
}Node, *Tree;

typedef struct Heap {
    Node **data;
    int n, size;
}Heap;

Node *getnewnode() {
    Node * p = (Node *)malloc(sizeof(Node) * 1);
    p->data =  p->val = 0;
    p->lchild = p->rchild = NULL;
    return p;
}

Heap *init(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap) * 1);
    h->data = (Node **)malloc(sizeof(Node*) * n);
    h->n = 0;
    h->size = n;
    return h;
}

int insert(Heap *h, Node *p) {
    h->size += 1;
    h->data[h->size] = p;
    int loc = h->size, father = loc / 2;
    while(father > 0 && h->data[father]->val > h->data[loc]->val) {
        swap(h->data[father],h->data[loc]);
        loc = father;
        father = loc / 2;
    }
    return 1;
}

int pop(Heap *h) {
    swap(h->data[1],h->data[h->size]);
    h->size -= 1;
    int loc = 1;
    while(loc * 2 <= h->size) {
        int l = loc * 2;
        int r = l + 1;
        int pos = loc;
        if(l <= h->size && h->data[pos]->val > h->data[l]->val) {
            pos = l;
        }
        if(r <= h->size && h->data[pos]->val > h->data[r]->val) {
            pos = r;
        }
        if(pos == loc) break;
        swap(h->data[pos], h->data[loc]);
        loc = pos;
    }

} 

int empty(Heap *h) {
    return h->size == 0;
}

Node *top(Heap *h) {
    return h->data[1];
}

int heapsize(Heap *heap) {
    return heap->size;
}

// 只能编码小频率的
Node *build(Heap *heap) {
    Node *root;
    while(heapsize(heap) > 1) {
        root = getnewnode();
        Node *tempa = top(heap);
        pop(heap);
        #ifdef DEBUG
        printf("l = %d ", tempa->val);
        #endif
        root->lchild = tempa;
        //if(empty(heap)) continue;
        Node *tempb = top(heap);
        pop(heap);
        #ifdef DEBUG
        printf("r = %d size = %d\n", tempb->val, heap->size);
        #endif
        root->rchild = tempb;
        root->val = tempa->val + tempb->val;
        insert(heap, root);
    }
    root = top(heap);
    pop(heap);
    return root;
}

void getEncode(Node *root, int k, int m,  int *hashtable, int *encode, int now, char * str) {
    if(root == NULL) return ;
    //printf("%p %p\n",root->lchild, root->rchild);
    #ifdef DEBUG
    printf("aa = %d %d\n", k,root->data);
    #endif
    if(root->lchild == NULL) {
        #ifdef DEBUG
        printf("%c %d\n", root->data, k);
        #endif
        str[now] = '\0';
        #ifdef DEBUG
        printf("%s\n", str);
        #endif
        hashtable[k] = root->data;
        encode[root->data] = k;
        return ;
    }
    //printf("AAA\n");
    str[now] = '0';
    getEncode(root->lchild, k * 2, m, hashtable,  encode, now + 1, str);
    str[now] = '1';
    getEncode(root->rchild, k * 2 + 1, m , hashtable, encode,now + 1,  str);
    return ;
}
/*
int main()
{
    Heap *heap = init(10000);
    char *str = (char *)malloc(sizeof(char ) * 10000);
    int *freq = (int *)calloc(256 , sizeof(int));
    int *hashtable = (int *)malloc(sizeof(int ) * 65536);
    int *encode = (int *)malloc(sizeof(int ) * 256);
    char *str1 = (char *)malloc(sizeof(char ) * 256);
    memset(encode, -1, sizeof(int ) * 256);
    memset(hashtable, -1, sizeof(int) * 65536);
    scanf("%s", str);
    printf("%s\n", str);
    for(int i = 0; str[i]; i++) {
        freq[str[i]]++;
    }
    for(int i = 0; i < 256; i++) {
        if(!freq[i]) continue;
        Node *p = getnewnode();
        p->data = (char)(i);
        p->val = freq[i];
        insert(heap, p);
    }
    Node *root;
    root = build(heap);
    printf("%p\n", root);
    getEncode(root, 0, 1, hashtable, encode, 0,str1);
    for(int i = 0; i < 256; i++) {
        if(i % 16 == 0) printf("\n");
        printf("%d ",encode[i]);
    }
    printf("\n");
}
*/
