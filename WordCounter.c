#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Word{
    char *chars;
    int count;
} Word;

typedef struct WordList{
    int length;
    int used;
    Word *words;
    void (*add)(struct WordList *wl, char *word);
    bool (*exists)(struct WordList *wl, char *word);
    bool (*increment)(struct WordList *wl, char *word);
    void (*sort)(struct WordList *wl, bool desc);
    void (*save)(struct WordList *wl, char *filepath);
    void (*print)(struct WordList *wl);
} WordList;

/**
 Compare function for sorting Word structs in descending order.
 Using c qsort() function.
 **/
int Word_compare_descending (const void* a, const void* b)
{
    const Word *w1 = a;
    const Word *w2 = b;
    if (w1->count > w2->count) {
        return -1;
    }
    if (w1->count < w2->count) {
        return 1;
    }
    else{
        return 0;
    }
}


/**
 Compare function for sorting Word structs in ascending order.
 Using c qsort() function.
 **/
int Word_compare_ascending (const void* a, const void* b)
{
    const Word *w1 = a;
    const Word *w2 = b;
    if (w1->count < w2->count) {
        return -1;
    }
    if (w1->count > w2->count) {
        return 1;
    }
    else{
        return 0;
    }
}

/**
 Function to sort the WordList in either ascending or
 descending order.
 **/
void WordList_sort(WordList *wl, bool descending){
    if (descending) {
        qsort(wl->words,
              wl->used,
              sizeof(Word),
              Word_compare_descending);
    }
    else{
        qsort(wl->words,
              wl->used,
              sizeof(Word),
              Word_compare_ascending);
    }
}


/**
 Creates and initialises a new Word struct.
 **/
Word* Word_new(){
    Word* word = malloc(sizeof(Word));
    word->chars = malloc(50 * sizeof(char));
    word->count = 1;
    return word;
}


/**
 Adds an item to the WordList collection. Reallocates memory
 if required.
 **/
void WordList_add_word(WordList *wl, char *word){
    if (wl->length == wl->used) {
        //Increase the length by 10
        wl->length *= 2;
        
        Word *tmp = realloc(wl->words, wl->length * sizeof(Word));
        if (tmp == NULL) {
            printf("Failed to increase word list size (Realloc)");
            exit(EXIT_FAILURE);
        }
        wl->words = tmp;
    }
    Word *w = Word_new();
    strcpy(w->chars, word);
    wl->words[wl->used] = *w;
    wl->used++;
}

/**
 Checks whether the word exists in the WordList.
 **/
bool WordList_exists(WordList *wl, char *word){
    int i;
    for (i=0; i<wl->used; i++) {
        if (!strcmp(word, wl->words[i].chars)) {
            return true;
        }
    }
    return false;
}

/**
 Increments the count for the word. Returns false/0 if the 
 word is not in the list.
 **/
bool WordList_increment(WordList* wl, char *word){
    for (int i=0; i<wl->used; i++) {
        if (!strcmp(word, wl->words[i].chars)) {
            wl->words[i].count++;
            return true;
        }
    }
    return false;
}

/**
 Saves the WordList data to a comma seperated file
 **/
void WordList_save(WordList *wl, char *filepath){
    FILE *fp = fopen(filepath, "a+");
    if (!fp) {
        printf("\x1b[31mFailed to save csv to: %s\x1b[0m\n", filepath);
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<wl->used; i++) {
        fprintf(fp, "%s, %d\n", wl->words[i].chars, wl->words[i].count);
    }
    fclose(fp);
}

/**
 Prints the contents of the WordList to the command line.
 **/
void WordList_print(WordList *wl){
    for (int i=0; i<wl->used; i++) {
        printf("%30s - \t%4d\n", wl->words[i].chars, wl->words[i].count);
    }
}

/**
 Creates and inits a new WordList struct.
 **/
WordList* WordList_new(){
    WordList* wl = malloc(sizeof(WordList));
    wl->words = malloc(10 * sizeof(Word));
    wl->length = 10;
    wl->used = 0;
    wl->increment = &WordList_increment;
    wl->add = &WordList_add_word;
    wl->exists = &WordList_exists;
    wl->sort = &WordList_sort;
    wl->save = &WordList_save;
    wl->print = &WordList_print;
    return wl;
}

/**
 Removes punctuation from the string, and
 sets to be lower case
 **/
void remove_punc(char *p)
{
    char *src = p, *dst = p;
    while (*src)
    {
        if (ispunct((char)*src))
        {
            src++;
        }
        else if (isdigit((char)*src)){
            src++;
        }
        else if (isupper((char)*src))
        {
            *dst++ = tolower((char)*src);
            src++;
        }
        else if (src == dst)
        {
            src++;
            dst++;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = 0;
}