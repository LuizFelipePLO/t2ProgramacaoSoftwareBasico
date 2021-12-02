#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE_WORDS 30
#define MILLION 1000000

typedef struct typeword Word;
struct typeword{
    char string[SIZE_WORDS];
    int count;
    Word* next;
};

void FixString(char *word){
    word[0] = tolower(word[0]);

    int index = strlen(word) - 1;

    int i;

    for(i=index;i>0;i--){
        if(word[i]<97 || word[i]>122){
            word[i]='\0';
        }
    }
    return;
}
