ID_CHAR			[a-zA-Z_]

%{
#include <stdio.h>
%}
 
%%
"stego"		{ printf("FOUND: stego\n"); return("stego"); }
{ID_CHAR}({ID_CHAR})* { printf("IDENTIFIER\n"); return(0); }
"asinine"	{ printf("FOUND: asinine\n"); return("asinine"); }
{ID_CHAR}({ID_CHAR})*       { return(yytext);}
.		{ /* ignore bad characters */ }

%%

yywrap()
{
	return(1);
}
main()
{
	int i;
	i = yylex();
	while (i > 0)
	{
 	i = yylex();
	 }
	return(0);
}

