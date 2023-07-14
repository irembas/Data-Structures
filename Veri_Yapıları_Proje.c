#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000

typedef struct WordNode {     // aynı sayı karşılığına sahip kelimeleri trie de tutmak için
    char *word;               // linkli liste yapısı
    struct WordNode *next;
} WordNode;

typedef struct TrieNode {            // trie yapısı için struct, words kelimeleri tutuyor.
    struct TrieNode *children[10];     // children arrayi altına 10 kadar node bağlanabileceğini
    WordNode *words;                 // gösterir.
    bool isWord;                    // kelime sonu kontrolü
} Trie;

Trie* createNode(void) {
    Trie *node = malloc(sizeof(Trie));        // node için yer açmak ve ilk implementastyon
    node->isWord = false;
    node->words = NULL;
    for(int i=0; i<10; i++)
        node->children[i] = NULL;
    return node;
}

WordNode* createWordNode(const char *word) {      // trie de tutulan linkli listedeki nodeları
    WordNode *node = malloc(sizeof(WordNode));     // create etmek için
    node->word = malloc(strlen(word) + 1);
    strcpy(node->word, word);
    node->next = NULL;
    return node;
}

int charToNumber(char c) {         // dict.ten okunan kelimelerin sayı karşılıklarına çevrilmesi
    if (c >= 'a' && c <= 'c')       // ingilizce karakterler ve küçük harfler
        return 2;
    else if (c >= 'd' && c <= 'f')
        return 3;
    else if (c >= 'g' && c <= 'i')
        return 4;
    else if (c >= 'j' && c <= 'l')
        return 5;
    else if (c >= 'm' && c <= 'o')
        return 6;
    else if (c >= 'p' && c <= 's')
        return 7;
    else if (c >= 't' && c <= 'v')
        return 8;
    else
        return 9;
}

void insert(Trie *root, const char *word) {   // trie ağacına node eklemek için
    Trie *tmp = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = charToNumber(word[i]);     // her bir harfin sayı karşılığı için bir node oluşturulur.
        if (tmp->children[index] == NULL)
            tmp->children[index] = createNode();
        tmp = tmp->children[index];
    }

    WordNode *newWord = createWordNode(word);    // kelime sonuna gelindiğinde linkli liste node u oluşturulur.
    newWord->next = tmp->words;               // kelime oraya eklenir
    tmp->words = newWord;
    tmp->isWord = true;
}

void readFile(Trie *root, const char *fileName) {     // filedan dictionary okumak için
    FILE *file = fopen(fileName, "r");
    if(!file) {
        printf("Dosya açılma hatası\n");
        return;
    }
    char line[SIZE];                                      //max 1000 karakter okuyabilir
    while(fgets(line, sizeof(line), file)) {
        char *value = strtok(line, "{\", }\n");           // kelimeler harici işaretlerden kurtulmak için, kelimeleri verilen                                                   //karakterlere göre ayırır
        while(value != NULL) {
            if(strlen(value) > 0) {
                for(int i=0; i<strlen(value); i++)
                    value[i] = tolower((unsigned char)value[i]); // küçük harfe çevrilir.
                insert(root, value);     //arınmış kelimeyi trie ye ekleme işlemi
            }
            value = strtok(NULL, "{\", }\n");  // tekrardan tokenize etme
        }
    }
    fclose(file);
}

void search_Word(Trie *root, int number) {        // verilen sayının trie de karşılık geldiği kelimeleri bulmak için
    int reversed_number = 0;
    while (number != 0) {
        int rakam = number % 10;   // sayının her bir basamağındaki rakamı bulmak için
        number /= 10;
        reversed_number = reversed_number * 10 + rakam;  // her bir rakamı bulup tersine topluyoruz. sayı tersine dönmüş oluyor.
    }

    Trie *tmp = root;
    while (reversed_number != 0) {
        int rakam = reversed_number % 10;   // tersine çevrilen sayının tek tek alınması
        if (tmp->children[rakam] == NULL) {       // sayı sonunda belirtilen node yok ise bu kelime yoktur.
            printf("Sözlükte bu sayının karşılığı bir kelime yoktur.\n");
            return;
        }
        tmp = tmp->children[rakam];
        reversed_number /= 10;
    }

    if(tmp->isWord) {     //kelimenin sonuna gelindi mi kontrolü
        WordNode *wordNode = tmp->words;      // words linkli listesine kelime atılır
        while (wordNode != NULL) {          //word doluysa nexindeki node a atar.
            printf("%s\n", wordNode->word);    //kelimeleri yazdırmak için
            wordNode = wordNode->next;
        }
    } else {
        printf("Sözlükte bu sayının karşılığı bir kelime yoktur.\n");
    }
}

int main(void) {
    Trie *root = createNode();   // trie yapısı için root oluşturuldu
    //readFile(root, "/Users/gulsumirembas/Desktop/dictionary.txt");// dictionary.txtden kelimeler okunur.
    readFile(root, "/Users/gulsumirembas/Desktop/dictionary 2.txt");

    char input[100];         // kullanıcı "q" ya basana kadar döner
    while (true) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';           // girdinin sonundaki enter ı silmek için

        if(strcmp(input, "q") == 0) {
            printf("Çıkılıyor...\n");
            break;
        }
        
        int number = atoi(input); // girdiği integera çevirmek için
        if (number != 0) {
            search_Word(root, number);    // girilen sayıyı trie de aramak için
        }
        else {
            printf("Geçersiz değer! Lütfen bir sayı girin veya çıkmak için 'q'ya basın.\n");
        }
    }
    
    return 0;
}
