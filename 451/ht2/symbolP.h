/* symbolP.h */
/* aclark */

typedef struct sSymbol 
{ 
    char *name;
    int kind;
}*tSymbol;

const int SYMBOL_SIZE = sizeof(struct sSymbol);
