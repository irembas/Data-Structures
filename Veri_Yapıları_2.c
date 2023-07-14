//
//  main.c
//  ödev3
//
//  Created by G.İrem Baş on 15.05.2023.
//


#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex; // ders kodu
    int indegree; // ön koşul ders sayısı
    struct node *next;
};

struct graph{
    int  numVertices; // ders sayısı
    struct node **adjLists; // komşuluk listesi
};

struct node *createNode(int v){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex= v + 1;  // 1 tabanlı olsun diye
    newNode->indegree=0;
    newNode->next = NULL;
    return newNode;
}

struct graph *createGraph(int vertices){
    int i;
    struct graph *graph= malloc(sizeof(struct graph));
    graph->numVertices=vertices; // toplam ders sayısı
    graph->adjLists= malloc(vertices*sizeof(struct node*));
    for(i=0;i<vertices;i++){
        graph->adjLists[i]= createNode(i+1);  // toplam ders sayısı kadar node create ediliyor.
    }
    return graph;
}

void addEdge(struct graph *graph, int src, int dest){
    struct node * newNode = createNode(dest);    // yönlü bir graph olduğu için koşul dersten ön koşulu olan derse doğru
    newNode->next= graph->adjLists[src]->next;   // aralarındaki bağlantıya göre komşuluk listesine ekliyor.
    graph->adjLists[src]->next = newNode;
}

void calculateIndegrees(struct graph* graph) {   // her bir dersin kaç önkoşulu olduğunu hesaplıyor.
    
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v]->next;
        while (temp) {
            graph->adjLists[temp->vertex - 1]->indegree++;  // listeyi tekrar dolanarak ön koşulları sayıp indegree değerini arttırıyor.
            temp = temp->next;
        }
    }
}

void printGraph(struct graph* graph) {  // komşuluk listesini yazdırmak için
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v]->next;
        printf("%d -> ", v+1);
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
            if(temp) printf("-> ");
        }
        printf("\n");
    }
}

void printIndegrees(struct graph* graph) {   // her dersin kaç ön koşulu olduğunu yazdırmak için
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        printf("Ders %d'in  %d adet ön şartı vardır. \n" , v+1, graph->adjLists[v]->indegree);
    }
}

void findSemester(struct graph* graph) {
    int semesterCount = 0;
    int totalCourses = graph->numVertices;

    while (totalCourses > 0) {
        semesterCount++;
        int coursesTaken = 0;
        int coursesThisSemester[graph->numVertices];     // ders sayısı boyutunda bir liste tutuyoruz
        int numCoursesThisSemester = 0;

        
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjLists[v]->indegree == 0) {
                coursesThisSemester[numCoursesThisSemester++] = v; // listeye bu dönem alınan dersleri kaydediyoruz
                graph->adjLists[v]->indegree = -1;   // aldığımız derslerin indegree değerini -1 yapıyoruz
                coursesTaken++; // toplam sayıyı tutuyor
            }
        }

        printf("Dönem %d: ", semesterCount);
        for (int i = 0; i < numCoursesThisSemester; i++) {
            printf("Ders %d ", coursesThisSemester[i] + 1);

            struct node* temp = graph->adjLists[coursesThisSemester[i]]->next;
            while (temp) {
               
                if (graph->adjLists[temp->vertex - 1]->indegree > 0) {
                    graph->adjLists[temp->vertex - 1]->indegree--;
                }
                temp = temp->next;
            }
        }
        printf("alındı\n");

        totalCourses -= coursesTaken;
    }

    printf("Tüm dersler %d dönemde bitmiştir.\n", semesterCount);
}


    
int main(int argc, const char * argv[]) {
    
    int N, E;
        printf("Ders sayısını giriniz: ");
        scanf("%d", &N);

        struct graph *graph = createGraph(N);

        printf("Ön şart sayısını giriniz: ");
        scanf("%d", &E);

        printf("Ön şartlar için komşuluk matrisini giriniz:\n");
        int adjacencyMatrix[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &adjacencyMatrix[i][j]);
                if (adjacencyMatrix[i][j] == 1) {
                    addEdge(graph, i, j);
                }
            }
        }

    printGraph(graph);
    calculateIndegrees(graph);
    printIndegrees(graph);
    findSemester(graph);

  
    return 0;
}
