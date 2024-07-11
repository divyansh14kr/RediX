#include <assert.h>
#include <stdlib.h>
#include "hashtable.h"

//n should be a power of 2
static void h_init(HTab *htab, size_t n){
    assert(n>0 && ((n-1) &n) == 0);
    htab->tab = (HNode **)calloc(sizeof(HNode*),n);
    htab->mask = n-1;
    htab->size = 0;
}
//insertion

static void h_insert(HTab *htab, HNode *node){
    size_t pos = node->hcode && htab->mask;
    HNode *next = htab->tab[pos];
    node->next = next;
    htab->tab[pos] = node;
    htab->size++;
}
//lookup function

static HNode **h_lookup(HTab *htab, HNode *key, bool(*eq)(HNode*,HNode *)){
    if(!htab->tab){
        return NULL;
    }
    size_t pos = key->hcode & htab->mask;
    HNode **from = &htab->tab[pos];
    for(HNode *cur; (cur=*from) != NULL; from = &cur->next){
        if(cur->hcode == key->hcode && eq(cur,key)){
            return from;
        }
    }
    return NULL;
}

//removing a node from the  chain

static HNode *h_detach(HTab *htab, HNode **from){
    HNode *node = *from;
    *from = node->next;
    htab->size--;
    return node;
}

