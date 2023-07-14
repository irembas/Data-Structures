#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int value;
  struct Node *Next;
} NODE;

NODE *createNode() {
  NODE *p;
  p = (NODE *)malloc(sizeof(NODE));
  if (p == NULL) {
    exit(0);
  }
  p->Next = NULL;
  return p;
}
int numbers_check(int n, int m){
int max = 2*(n-1),flag=1;
if((3*m)>max){
    flag=0;
}
return flag;
}

void insertNode(int value, NODE *NewNode, NODE **head) {
NODE *ptr = (NODE *)malloc(sizeof(NODE));
NODE*temp;
if(ptr == NULL) {
    printf("\nOVERFLOW");
} else {
    ptr ->value = value;
    if(*head == NULL) {
        *head = ptr;
        ptr -> Next = *head;
    } else {
        temp = *head;
        while(temp->Next != *head) {
            temp = temp->Next;
        }
        ptr->Next = *head;
        temp -> Next = ptr;
        *head = ptr;
    }
}
}
void printList(NODE *head) {
NODE *temp = head;
if (temp == NULL) {
    printf("List is empty.\n");
    return;
}
do {
    printf("%d ", temp->value);
    temp = temp->Next;
} while (temp != head);
printf("\n");
}
void insertAtRandIndex(int index, int ortak_sayi, NODE **head) {
NODE *temp = *head;
NODE *prev;
NODE *new_node = createNode();
new_node->value = ortak_sayi;
if (index == 0) {
    while (temp->Next != *head) {
        temp = temp->Next;
    }
    temp->Next = new_node;
    new_node->Next = *head;
    *head = new_node;
} else {
    for (int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->Next;
    }
    prev->Next = new_node;
    new_node->Next = temp;
}
}
int random_number(int n) {
static int initialized = 0;
if (!initialized) {
srand(time(NULL));
initialized = 1;
}
return rand() % n + 1;
}

int fill_carks(int n,int m, int *repeated1,int *repeated2, int count) {
int i,key = 0, num = 0, random_num = 0;
do {
    if(count %m ==0){
        for (i = 0; i < n;i++) {
            repeated1[i] = 0;
        }
    }
    num = rand() % n + 1;
    if ((repeated1[num - 1] < 1) && (repeated2[num-1]<2)){
        random_num = num;
        key = 1;
        repeated1[random_num - 1]++;
        repeated2[random_num - 1]++;
    } else {
        key = 0;
    }
} while (key == 0);
return random_num;
}

int find_common_num(int n, int *repeated2 ){
int num;
do{
    num =random_number(n);
}while(repeated2[num-1]>0);

return num;
}

void findCommon(NODE *cark1, NODE *cark2, NODE *cark3, int m, int n, int*repeated3, int *rotate1, int *rotate2) {
NODE* current1 = cark1;
NODE* current2 = cark2;
NODE* current3 = cark3;
int index1=0, index2=0, index3=0;
int common_number=0;
for(int i=0;i<m;i++){
    repeated3[current1->value-1]++;
    current1 = current1->Next;
    repeated3[current2->value-1]++;
    current2 = current2->Next;
    repeated3[current3->value-1]++;
    current3 = current3->Next;
}

for(int i=0;i<n;i++){
    if(repeated3[i]>2){
        common_number = i+1;
    }
}
for(int i=0;i<m;i++){
    if(current1->value==common_number){
        index1=i+1;
    }
    current1=current1->Next;
}
for(int i=0;i<m;i++){
    if(current2->value==common_number){
        index2=i+1;
    }
    current2=current2->Next;
}
for(int i=0;i<m;i++){
    if(current3->value==common_number){
        index3=i+1;
    }
    current3=current3->Next;
}
printf("Common number is : %d\n", common_number);
printf("Index of common number in cark1: %d\nIndex of common number in cark2: %d\nIndex of common number in cark3: %d\n", index1, index2, index3);
if(index1>=index2){
    if((index1-index2)<=(m-(index1-index2))){
        *rotate1=index2-index1;
    }
    else{
        *rotate1=m-(index1-index2);
    }
}
else{
    if((index2-index1)<=(m-(index2-index1))){
        *rotate1=index2-index1;
    }
    else{
        *rotate1=(index2-index1)-m;
    }
    
}
if(index1>=index3){
    if((index1-index3)<=(m-(index1-index3))){
        *rotate2=index3-index1;
    }
    else{
        *rotate2=m-(index1-index3);
    }
}
else{
    if((index3-index1)<=(m-(index3-index1))){
        *rotate2=index3-index1;
    }
    else{
        *rotate2=(index3-index1)-m;
    }
    
}
if(*rotate1>0){
    printf("Rotate of the çark2 %d numbers to clocwise\n",abs(*rotate1));
}
else{
    printf("Rotate of the çark2 %d numbers to anticlocwise\n",abs(*rotate1));
}
if(*rotate2>0){
    printf("Rotate of the çark3 %d numbers to clocwise\n",abs(*rotate2));
}
else{
    printf("Rotate of the çark3 %d numbers to anticlocwise\n",abs(*rotate2));
}
}

void rotateList(NODE** head, int rotate_num, int m)
{
if (*head == NULL)
    return;

NODE* current = *head;

while (current->Next != *head)
    current = current->Next;

current->Next = (*head);

if (rotate_num > 0)
    rotate_num = rotate_num % m +1;

else
    rotate_num = m + (rotate_num % m+1);

for (int i = 0; i < rotate_num; i++)
    current = current->Next;

*head = current;
}

int main(void) {
int i,count=0,num, index1, index2,index3, N, M, rotate1, rotate2, flag;
int *repeated1, *repeated2, *repeated3;
NODE *head1=NULL, *head2=NULL, *head3 =NULL;
NODE *cark1, *cark2, *cark3;
cark1 = createNode();
cark2 = createNode();
cark3 = createNode();
do{
    printf("Please write the length of the carks:\n");
    scanf("%d", &M);
    printf("Please write the max number used: \n");
    scanf("%d", &N);
    flag=numbers_check(N, M);
    if(flag==0){
        printf("Please give numbers appropriate:\n");
    }
}while(flag==0);
M=M-1;
repeated1 = (int *)malloc(N * sizeof(int));
for (i = 0; i < N; i++) {
    repeated1[i] = 0;}
      
repeated2 = (int *)malloc(N * sizeof(int));
for (i = 0; i < N; i++) {
repeated2[i] = 0;
}
repeated3 = (int *)malloc(N * sizeof(int));
for (i = 0; i < N; i++) {
repeated3[i] = 0;
}

for (int i = 0; i < M; i++) {
    insertNode(fill_carks(N,M, repeated1,repeated2, count), cark1, &head1);
    count++;
  }
for (int i = 0; i < M; i++) {
    insertNode(fill_carks(N,M, repeated1,repeated2, count), cark2, &head2);
    count++;
  }
for (int i = 0; i < M; i++) {
    insertNode(fill_carks(N,M, repeated1,repeated2, count), cark3, &head3);
    count++;
}
int ort_sayi = find_common_num(N, repeated2);
index1 = random_number(M);
do{
    num= random_number(M);
}while(index1==num);
index2=num;
    
do{
    num= random_number(M);
}while((index1==num) || index2==num);
index3=num;
insertAtRandIndex(index1, ort_sayi, &head1);
insertAtRandIndex(index2, ort_sayi, &head2);
insertAtRandIndex(index3, ort_sayi, &head3);

printf("Initial state of the carks: \n");
printf("Çark1: ");
printList(head1);
printf("\n");
printf("Çark2: ");
printList(head2);
printf("\n");
printf("Çark3: ");
printList(head3);
printf("\n");

findCommon(head1, head2, head3, M+1, N, repeated3, &rotate1, &rotate2);
rotateList(&head2, rotate1,M+1);
rotateList(&head3, rotate2,M+1);

printf("Last state of the carks: \n");
printf("Çark1: ");
printList(head1);
printf("\n");
printf("Çark2: ");
printList(head2);
printf("\n");
printf("Çark3: ");
printList(head3);
printf("\n");

free(repeated1);
free(repeated2);
free(repeated3);
  return 0;
}
