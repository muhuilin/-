/*************************************************************************
	> File Name: doubleTrie.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年02月24日 星期六 11时04分18秒
 ************************************************************************/

#include "haffman.h"

typedef struct TrieNode {
    int flag;
    struct TrieNode *next[2];
}TrieNode, *Trie;

TrieNode *getTrienode() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->next[0] = p->next[1] = NULL;
    return p;
}

int inserttoTrie(Trie tree, const unsigned char *str, int *encode) {
    TrieNode *p = tree;
    #ifdef DEBUG
    printf("**************************\n");
    #endif
    while(*str) {
        int val = encode[str[0]];
        if(val == -1) return 0;
        int code[16], n = 0;
        #ifdef DEBUG
        printf("val = %d  :",val);
    #endif
        while(val) {
            code[n++] = val % 2;
            val /= 2;
        }
        for(int i = n - 2; i >= 0; i--) {
            #ifdef DEBUG
            printf("%d", code[i]);
    #endif
            if(p->next[code[i]] == NULL) {
                p->next[code[i]] = getTrienode();
            }
            p = p->next[code[i]];
        }
        #ifdef DEBUG
        printf("\n");
    #endif
        p->flag = 1;
        str++;
    } 
    #ifdef DEBUG
    printf("**************************\n");
    #endif
    p->flag = 2;
    return 1;
}

int search(Trie tree, const  unsigned char *str, int *encode) {
    TrieNode *p = tree;
    printf("********************************\n");
    while(*str) {
        int val = encode[str[0]];
        if(val == -1) return 0;
        int code[16], n = 0;
        #ifdef DEBUG
        printf("val = %d :", val);
        #endif
        while(val) {
            code[n++] = val & 1;
            val >>= 1;
        }
        for(int i = n - 2; i >= 0; i--) {
            #ifdef DEBUG
            printf("%d", code[i]);
            #endif
            if(p->next[code[i]] == NULL) {
                return 0;
            }
            p = p->next[code[i]];
        }
        #ifdef DEBUG
        printf("\n");
        #endif 
        str++;
    }
    printf("********************************\n");
    return p->flag == 2;
}

int main()
{

    Heap *heap = init(10000);
    //printf("heap is ok\n");
    //fflush(stdout);
    unsigned char *str = (unsigned char *)malloc(sizeof(unsigned char ) * 10000);
    //printf("str is ok\n");
    //fflush(stdout);
    int *freq = (int *)calloc(256 , sizeof(int));
    int *hashtable = (int *)malloc(sizeof(int ) * 65536);
    int *encode = (int *)malloc(sizeof(int ) * 256);
    char *str1 = (char *)malloc(sizeof(char ) * 256);
    memset(encode, -1, sizeof(int ) * 256);
    memset(hashtable, -1, sizeof(int) * 65536);
    char *stra[20];
    //printf("mem is ok\n");
    //fflush(stdout);
    FILE *fin = fopen("./data", "r");
    //printf("file is ok\n");
    //fflush(stdout);
    /*for(int i = 0; i < 20; i++) {
        stra[i] = (char *)malloc(sizeof(char ) * 1000);
    }*/
    while(fscanf(fin, "%s", str) != EOF) {
        for(int i = 0; str[i]; i++)  
        freq[str[i]] ++;
    }
    //printf("freq is ok\n");
    //fflush(stdout);
    /*
    for(int times = 0; times < 3; times++) {
    scanf("%s", stra[times]);
        for(int j = 0; stra[times][j];j++) {
            printf("%d",(unsigned int)stra[times][j]);
        }
        printf("\n");
    printf("%s\n", stra[times]);
    for(int i = 0; stra[times][i]; i++) {
        freq[(unsigned int)stra[times][i]]++;
    }
    }*/
    rewind(fin); /// 指针回到文件头部 
    for(int i = 0; i < 256; i++) {
        if(!freq[i]) continue;
        Node *p = getnewnode();
        p->data = (char)(i);
        p->val = freq[i];
        insert(heap, p);
    }
    Node *root;
    root = build(heap);
    //printf("%p\n", root);
    getEncode(root, 1, 1, hashtable, encode, 0,str1);
    #ifdef DEBUG
    for(int i = 0; i < 256; i++) {
        if(i % 16 == 0) printf("\n");
        printf("%d ",encode[i]);
    }
    printf("\n");
    #endif
    Trie tree = getTrienode();
    /*
    for(int i = 0; i < 3; i++) {
        inserttoTrie(tree, stra[i], encode);
    }*/
    while(fscanf(fin, "%s", str) != EOF) {
        inserttoTrie(tree, str, encode);
    }
    fclose(fin);
    int n;
    scanf("%d", &n);
    for(int i = 0;i < n; i++) {
        scanf("%s", str);
        printf("FIND %s : %d\n", str, search(tree,str, encode));
    }

}
