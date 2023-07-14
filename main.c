//
//  main.c
//  veri_yapıları_ödev2_19011502
//
//  Created by G.İrem Baş on 15.04.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 100

typedef struct node{
    int value;
    int count;
    struct node *left, *right;
}NODE;

typedef struct{
    int top;
    int items[MAXSIZE];
}STACK;

void initialize(STACK *s){
    s->top=0;
}
int empty(STACK *s){
    if(s->top==0)
        return 1;
    else
        return 0;
}

int full(STACK *s){
    if(s->top==MAXSIZE)
        return 1;
    else
        return 0;
}

int push(int x, STACK *s){
    if(full(s))
        return 0;
    else{
        for(int i=s->top; i>0; i--){
            s->items[i] = s->items[i-1];
        }
        s->items[0] = x;
        s->top++;
        return 1;
    }
}

int pop(STACK *s){
    int x;
    if(empty(s))
        return 0;
    else{
        --s->top;
        x = s->items[s->top];
        return x;
    }
}

void print_fonk(STACK *s){
    printf("Bucket: ");
    for(int i=0;i<s->top;i++){
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

void print_reverse_fonk(STACK *s){
    STACK *temp_stack;
    temp_stack = (STACK*)malloc(sizeof(STACK));
    int temp;

    while(!empty(s)){
        temp = pop(s);
        push(temp, temp_stack);
    }

    printf("Bucket (reverse): ");
    while(!empty(temp_stack)){
        temp = pop(temp_stack);
        printf("%d ", temp);
        push(temp, s);
    }
    printf("\n");
}


NODE * newNode(int x){
    NODE *tmp;
    tmp = (NODE*)malloc(sizeof(NODE));
    tmp->value=x;
    tmp->count=x;
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
}

NODE * insert(NODE* root, int x){
    if(root==NULL){
        return newNode(x);
    }
    if(x < root->value){
        root->left= insert(root->left, x);
    }
    else{
        root->right = insert(root->right, x);
    }
    return root;
}
void traverse(NODE* root){
    if(root==NULL){
        return;
    }
    traverse(root->left);
    printf("%d ", root->value);
    printf("p:(%d) ", root->count);
    traverse(root->right);
}

NODE * max(NODE*root){
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}

NODE * min(NODE*root){
    while(root->left!=NULL){
        root=root->left;
    }
    return root;
}

NODE *deletion(NODE * root,int x){
    if(root==NULL){
        return NULL;
    }
    
    else if(root->value==x){
        if(root->left==NULL && root->right== NULL){
            return NULL;
        }
        else if(root->right!=NULL){
            root->value=min(root->right)->value;
            root->count=min(root->right)->count;
            root->right= deletion(root->right, min(root->right)->value);
            return root;
        }
        else{
            root->value=max(root->left)->value;
            root->count=max(root->left)->count;
            root->left= deletion(root->left,max(root->left)->value);
            return root;
        }
    }
    else{
        if(root->value < x){
            root->right= deletion(root->right,x);
            return root;
        }
        else{
            root->left= deletion(root->left,x);
            return root;
        }
    }
    
}

NODE *search(NODE * root, NODE *real_root, STACK *bucket1, int search_number, int p, int *count){
    if(root == NULL){
        return root;
    }
    else if(root->value == search_number){
           root->count= root->count-p;
        if(root->count<=0){
            (*count)++;
            push(search_number, bucket1);
            deletion(real_root,root->value);
        }
           return root;
    }
    else if(search_number < root->value){
        return search(root->left,real_root, bucket1, search_number, p, count);
    }
    else{
        return search(root->right,real_root, bucket1, search_number, p, count);
    }
}
int random_number(int n, int* repeated) {
    int num=0, random_num=0, key=0;
    do{
        static int initialized = 0;
        if (!initialized) {
            srand(time(NULL));
            initialized = 1;
        }
        num = rand() % n + 1;
        if (repeated[num - 1] < 1){
            random_num = num;
            repeated[random_num - 1]++;
            key=1;
        }
    }while(key==0);
    return random_num;
}

int main(int argc, const char * argv[]) {
    int * repeated, N,M,k, p, key=1, *count;
    count = (int*)malloc(sizeof(int));
    (*count)= 0;
    STACK * bucket1;
    bucket1 = (STACK *)malloc(sizeof(STACK));
    initialize(bucket1);
    printf("Please write the max weight of fruits(N):\n");
    scanf("%d", &N);
    printf("Please write the numbr of fruits(M):\n");
    scanf("%d", &M);
    
    repeated = (int*)malloc(N * sizeof(int));
    for(int i =0;i<N;i++){
        repeated[i]=0;
    }
    NODE * bst=NULL;
    bst = newNode(random_number(N, repeated));
    
    for(int i=0;i<M-1; i++){
        
        insert(bst,random_number(N, repeated));
    }
    
    do{
        printf("Tree: \n");
        traverse(bst);
        printf("\nPlease enter the number of the fruit you want to hit:(k) ");
        scanf("%d", &k);
        printf("Please enter the shooting power:(p) ");
        scanf("%d", &p);
        search(bst,bst, bucket1, k, p, count);
        printf("\n");
        print_fonk(bucket1);
        printf("press 0 if you want to quit- press 1 if you want to resume: ");
        scanf("%d" , &key);
        if((*count)==M){
            printf("There is no fruit in the tree..\n");
            print_reverse_fonk(bucket1);
            key=0;
        }
    }while(key==1);
    
   
    
    free(repeated);
    return 0;
}
