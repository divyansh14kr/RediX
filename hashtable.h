// creating a chaining hashtable
#include <cstddef>   
#include <cstdint>   
#include<assert.h>
#include <cstdlib>   

struct HNode{
    HNode *next = NULL;
    uint64_t hcode = 0; //cached hash value
};
struct HTab{
    HNode **tab = NULL;
    size_t mask =0;
    size_t size =0;
};
struct HMap{
    HTab ht1;
    HTab ht2;
    size_t 
}




