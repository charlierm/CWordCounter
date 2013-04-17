
#include <stdio.h>
#include "WordCounter.h"
#include <stdlib.h>

#define ANSI_RED    "\x1b[31m"
#define ANSI_RESET  "\x1b[0m"
#define ANSI_GREEN   "\x1b[32m"

int main(int argc, char *argv[])
{
    const char* INPUT_PATH = argv[1];
    const char* OUTPUT_PATH = argv[2];
    const char* QUIET = argv[3];
    
    /* Check arugments are present */
    if (!INPUT_PATH || !OUTPUT_PATH) {
        printf(ANSI_RED "WordCounter: Arguments Missing.\n" ANSI_RESET);
        printf("Usage: WordCounter input-path output-path [-q]\n");
        exit(EXIT_FAILURE);
    }
    
    /* Try and open file */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf(ANSI_RED "Failed to open file: %s\n" ANSI_RESET, argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /* Iterate text file adding words */
    WordList *wl = WordList_new();
    while(!feof(fp)){
        char *word = malloc(sizeof(char));
        fscanf(fp, "%s", word);
        remove_punc(word);
        if(!wl->increment(wl, word)){
            wl->add(wl, word);
        }
    }
    fclose(fp);
    
    wl->sort(wl, true);
    
    /* If not quiet then print the results */
    if (!QUIET) {
        wl->print(wl);
    }
    wl->save(wl, argv[2]);
    
    /* Free memory */
    for (int i=0; i<wl->used; i++) {
        free(wl->words[i].chars);
    }
    free(wl->words);
    free(wl);
    
    printf(ANSI_GREEN "Completed, %d words saved to '%s'\n" ANSI_RESET, wl->used, argv[2]);
    
}


