#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>



struct node
{
    unsigned char* data;
    struct node* right_child; 
    struct node* left_child;  
    int count;
};


struct node* insert(struct node* p, unsigned char* word)
{
    if (p == NULL)
    {
        p = (struct node*)malloc(sizeof(struct node));
        /*  p->data = (char*)malloc(sizeof(word));
          p->data = word; */
        p->data = _strdup(word);
        p->left_child = NULL;
        p->right_child = NULL;
        p->count = 1;
    }
    else if ((strcmp(word, p->data)) == 0)
        p->count++;
    else if ((strcmp(word, p->data)) < 0)
        p->left_child = insert(p->left_child, word);
    else
        p->right_child = insert(p->right_child, word);
    return p;
}


struct node* readFromFile(struct node* p)
{
    FILE* file;
    unsigned char* fname = "1.txt";
    unsigned char c;
    unsigned char temp[255];
    int j = 0;
    file = fopen(fname, "r");

    if (file == 0) {
        printf("Cant open file '%s'", fname);
        return 0;
    }
    while (!feof(file)) {
        c = fgetc(file);
        if (c == '\0')
            break;
        if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)) || ((c >= 192) && (c <= 255))) {
            temp[j] = c;
            temp[j + 1] = '\0';
            j++;
        }
        else if (strcmp(temp, "\0")) {
            p = insert(p, temp);
            temp[0] = '\0';
            j = 0;
        }
    }
    fclose(file);
    return p;
}

struct node* searchWord(struct node* p, unsigned char* word)
{
    if ((p == NULL) || (strcmp(p->data,word)==0)) 
        return p;
    else if (strcmp(p->data, word) > 0) 
        return searchWord(p->left_child, word);

    else if (strcmp(p->data, word) < 0)
        return searchWord(p->right_child, word);
}

void deleteTreeNode(struct node* tree) {
    if (tree != NULL) {
        deleteTreeNode(tree->left_child);
        deleteTreeNode(tree->right_child);
        free(tree->data);
        free(tree);
    }
}

void printFrequencyOrder(struct node* p)
{
    if (p != NULL)
    {
        printFrequencyOrder(p->left_child);
        printf("%s %d\n", p->data, p->count);
        printFrequencyOrder(p->right_child);
    }
}

void printAlphabetOrder(struct node* p)
{
    if (p != NULL)
    {
        printAlphabetOrder(p->left_child);
        printf("%s %d\n", p->data, p->count);
        printAlphabetOrder(p->right_child);
    }
}




struct node* deleteAllExcept(struct node* p,  int wordSize)
{
    static struct node* tmp = NULL;
    if (p != NULL)
    {
        deleteAllExcept(p->left_child, wordSize);
        deleteAllExcept(p->right_child, wordSize);
        if (strlen(p->data) == wordSize)
            if (p->count > 1)
            {
                for (int i = 0; i < p->count; i++)
                    tmp = insert(tmp, p->data);
            }
            else if(p->count == 1)
            {
                tmp = insert(tmp, p->data);
            }
            //printf("%s  ", p->data);
        
    }
    return tmp;

}

struct node* deleteAllExcept2(struct node* p, int wordSize)
{
    struct node* tmp1 = NULL;
    tmp1 = deleteAllExcept(p, wordSize);
    deleteTreeNode(p);
    //p = tmp1;
    return tmp1;

}




int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    struct node* rootTree1;
    rootTree1 = NULL;
    rootTree1 = readFromFile(rootTree1);
    printAlphabetOrder(rootTree1);
    printf("\nСлова длиной 5:\n");
    rootTree1 = deleteAllExcept(rootTree1, 5);
    /*struct node* tmp1 = NULL;
    tmp1 = deleteAllExcept(rootTree1, 2);*/
    //printf("%s",rootTree1->data);
    printAlphabetOrder(rootTree1);
    return 0;

}


