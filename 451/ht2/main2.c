/* main.c */
#include <stdio.h>
#include "st.h"
#include "symbol.h"

const int MAX_NUMBER_OF_SCOPES = 5;
/*const int SCOPE_HT_SIZE = 4;    not sure here yet... */


main()
{
    tSymbolTable st;
    char command;

/* change to SCOPE_HT_SIZE... maybe...*/

    st = st_initialize(MAX_NUMBER_OF_SCOPES, symbol_compare, symbol_hash);

    while ((command = getchar()) != EOF)
    {
        switch (command)
        {
            case 'a':    
	    {
                char text[255];
                int type;
                tSymbol symbol;

		scanf("%s %d", text, &type);
	        symbol = symbol_initialize(text,type);
	        st_add(st, symbol);
                break;
	    }

            case 'c':    
		if (st_close_scope(st) == -1)
		    printf("no open scopes to close\n");
                break;

            case 'd':    
		st_dump(st, symbol_print);
                break;

	    case 'l':    
	    {
		int type, scope;
		char text[255];
                tSymbol symbol;

		scanf("%s %d", text, &type);
	        symbol = symbol_initialize(text, type);
		scope = st_lookup(st, symbol);
		if (scope == -1)
		    printf("%s not found\n", text);
		else
		    printf("%s found at level %d\n", text, scope);

		symbol_free(symbol);
		break;
	    }

            case 'o':    
		if (st_open_scope(st) == -1)
  	            printf("can't open new scope\n");
                break;

	    case 'q':
		st_free(st);
                exit(0);
        }
    }

    st_free(st);
    return (0);
}
