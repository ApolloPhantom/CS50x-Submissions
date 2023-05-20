// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int x = hash(word);
    node * ptr=table[x];
    while(ptr!=NULL){
        if(strcasecmp(word,ptr->word)==0){
            return true;
        }
        else{
            ptr=ptr->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // func:- sum of weights of characters of the word with each character having weights according to the english alphabet divided by length of the
    // word
    int k=0;
    for(int i=0;word[i]!='\0';i++){
        int x = (int)word[i];
        if(x>=65 && x<=90){
            k+= x%65 + 1;
        }
        else if(x>=97 && x<=122){
            k+= x%97 + 1;
        }
        else if(x==96){
            k+=0;
        }
    }
    k = round(k/(double)LENGTH);
    //if(strcasecmp(word,"the")==0){k=27;}
    //else if(strcasecmp(word,"and")==0){k=28;}
    //else if(strcasecmp(word,"a")==0){k=29;}
    //else if(strcasecmp(word,"to")==0){k=30;}
    //else if(strcasecmp(word,"in")==0){k=31;}
    //else if(strcasecmp(word,"that")==0){k=32;}
    //else if(strcasecmp(word,"is")==0){k=33;}
    //else if(strcasecmp(word,"I")==0){k=34;}
    //else if(strcasecmp(word,"it")==0){k=35;}
    //else if(strcasecmp(word,"of")==0){k=36;}
    //else if(strcasecmp(word,"for")==0){k=37;}
    //else if(strcasecmp(word,"with")==0){k=38;}
    //else if(strcasecmp(word,"you")==0){k=39;}
    //else if(strcasecmp(word,"have")==0){k=40;}
    //else if(strcasecmp(word,"be")==0){k=41;}
    //else if(strcasecmp(word,"on")==0){k=42;}
    //else if(strcasecmp(word,"not")==0){k=43;}
    //else if(strcasecmp(word,"are")==0){k=44;}
    //else if(strcasecmp(word,"this")==0){k=45;}
    //else if(strcasecmp(word,"they")==0){k=46;}
    return k;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f;
    f = fopen(dictionary,"r");
    if(f==NULL){
        return false;
    }
    char str[LENGTH+1];
    while(fscanf(f,"%s",str)!=EOF){
        int x = hash(str);
        node *ptr = (node *)malloc(sizeof(node));
        if(ptr==NULL){
            return false;
        }
        node *temp = ptr;
        strcpy(ptr->word,str);
        ptr->next = NULL;
        if(table[x]==NULL){
            table[x]=ptr;
        }
        //else if(table[x]==NULL && x>26){
        //    table[x]=ptr;
        //}
        //else if(table[x]!=NULL && x>26){

        //}
        else{
            table[x] = temp;
            ptr->next = temp;
           table[x] = ptr;
        }
    }
    fclose(f);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int x=0;
    for(int i=0;i<N;i++){
        node * ptr;
        ptr=table[i];
        while(ptr!=NULL){
            x++;
            ptr=ptr->next;
        }
    }
    return x;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i=0;i<N;i++){
        node * ptr,*tmp;
        ptr=table[i];
        while(ptr!=NULL){
            tmp=ptr;
            ptr=ptr->next;
            free(tmp);
        }

    }
    return true;
}
