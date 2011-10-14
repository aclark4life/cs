L			[a-zA-Z_]
I_HATE_THIS		[a-zA-Z_]

%{
#include <stdio.h>
printf ("this_is_gay\n");
%}
 
%%
"stego"		{ printf("I found a stego!\n"); return("stego"); }
{I_HATE_THIS}({I_HATE_THIS})* { printf("this is gay!\n"); return(0); }
"assinine"	{ printf("this is asinine\n"); return("asinine"); }
{L}({L})*       { return(yytext);}
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

