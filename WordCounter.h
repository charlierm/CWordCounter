
#ifndef WordCounter_WordCounter_h
#define WordCounter_WordCounter_h
#include <stdbool.h>

/**
 Structure for storing individual words.
 **/
typedef struct Word{
    /**
     Word char array.
     **/
    char *chars;
    
    /**
     The frequency count.
     **/
    int count;
} Word;

/**
 Collection of Word structures.
 **/
typedef struct WordList{
    /**
     The current capacity of the array.
     **/
    int length;
    
    /**
     How many Word structures are held in the array.
     **/
    int used;
    
    /**
     The array of Word structs.
     **/
    Word *words;
    
    /**
     Adds an item to the WordList collection. Reallocates memory
     to dynamically size the array.
     @param WordList The WordList to add to.
     @param char* The string to add.
     
     @code
        wl->add(wl, "cake");
     @endcode
     **/
    void (*add)(struct WordList *wl, char *word);
    
    /**
     Checks whether the word exists in the WordList.
     @param WordList The WordList to check.
     @param char* The char array to search for.
     @returns bool True if found.
     **/
    bool (*exists)(struct WordList *wl, char *word);
    
    /**
     Increments the frequency count for the word.
     @param WordList The WordList to use.
     @param char* The string to increment
     
     @code
        wl->increment(wl, "cake");
     @endcode

     **/
    bool (*increment)(struct WordList *wl, char *word);
    
    /**
     Function to sort the WordList in either ascending or
     descending order.
     
     @param WordList The WordList structure to sort.
     @param bool True if sorting in descending order.
     
     @code
        wl->sort(wl, true);
        wl->sort(wl, 1);
     @endcode
     **/
    void (*sort)(struct WordList *wl, bool desc);
    
     /**
      Saves the WordList data to a comma seperated file
      @param WordList The WordList struct to save.
      @param char* The filepath to save the file to.
      
      @code
        wl->save(wl, "/path/to/file.csv");
      @endcode
     **/
    void (*save)(struct WordList *wl, char *filepath);
    
    /**
     Prints the contents of the WordList to the command line.
     @param WordList The WordList to save
     
     @code
        wl->print(wl);
     @endcode
     **/
    void (*print)(struct WordList *wl);
    
} WordList;

/**
 Creates and initialises a new Word struct.
 For storing letters of a word and the frequency count.
 **/
Word* Word_new();

/**
 Creates and inits a new WordList struct, for storing
 multiple Word structures.
 **/
WordList* WordList_new();

/**
 Removes punctuation/numbers from a char array and makes the string
 lower case.
 **/
void remove_punc(char *p);

#endif
