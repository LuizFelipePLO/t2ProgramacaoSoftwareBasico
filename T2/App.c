#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE_WORDS 30
#define MILLION 1000000

//Estruta com a palavra, a quantidade de vezes que apareceu e o ponteiro para a próxima palavra
typedef struct typeword Word;
struct typeword{
    char string[SIZE_WORDS];
    int count;
    Word* next;
};

//Remove caracteres desnecessários da string (como a vírgula e ponto)
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

//Verifica se adiciona uma nova palavra ou se somente soma o contador de uma palavra já existente
Word* CheckWord(char *word, Word *list, int *count_words){
    Word *i;

    //Se a lista for vazia, aloca memória e cria a primeira palavra
    if(list == NULL){
        //Aloca memória
        Word* first_word;
        first_word = (Word*)malloc(sizeof(Word));

        //Passa os valores
        strcpy(first_word->string, word);
        first_word->count = 1;
        *count_words = *count_words + 1;
        first_word->next = NULL;
        list = first_word;
        return list;
    }

    i  = list;
    Word *list_end;

    //Vai percorrendo a lista para ver se acha a palavra na lista
    while(i!=NULL){
        if(strcmp(i->string, word) == 0){
            i->count++;
            return list;
        }
        if(i->next==NULL){
            list_end = i;
        }
        i = i->next;
    }

    //Se não achou a palavra na lista, aloca memória para uma nova palavra
    Word *new_word;
    new_word = (Word*)malloc(sizeof(Word));

    strcpy(new_word->string, word);
    new_word->count = 1;
    new_word->next = NULL;
    list_end->next = new_word;
    *count_words = *count_words + 1;
    return list;

}

//Lê o arquivo
Word* ReadFile(char *filename)
{
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");
    FILE *txt_output = fopen("exit.csv", "w");
    char buffer[MILLION];   //Buffer com a string inteira do .txt
    Word *list_word = NULL;   //Lista Simplesmente Encadeada de palavras
    int count_words = 0;    //Contador de palavras
    int count=0;

    if(!handler){
        printf("Failed to open text file\n");
        return list_word;
    }
    if(!txt_output){
        printf("Failed to open json file\n");
        return list_word;
    }

    //Pega todo o .txt e coloca no buffer
    while(!feof(handler)){
        buffer[count] = fgetc(handler);
        count++;
    }

    char *token = strtok(buffer, " ");

    //Separa a string inteira em substrings
    while(token!=NULL){
        FixString(token);
        list_word = CheckWord(token, list_word, &count_words);
        token = strtok(NULL, " ");
    }

    //Print no arquivo .csv
    fprintf(txt_output,"string;count");

    //Print das palavras e seus contadores no arquivo .csv
    Word* aux;
    if(list_word == NULL){
        printf("Lista vazia");
    }
    else{
        for(aux = list_word; aux != NULL; aux = aux->next){
            fprintf(txt_output,"\n%s;%d", aux->string, aux->count);
        }
    }
    printf("\n");

    return list_word;
}

int main()
{
    Word *list;
    list = ReadFile("entry.txt");

    return 0;
}
