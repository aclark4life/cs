D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
LS			(l|L)
US			(u|U)

%{
#include <stdio.h>
#include "tokens.h"
#include "structs.h"

%}

%%

{L}({L}|{D})*		{ return(Table_Lookup(Table)); }

0[xX]{H}+{LS}?{US}?	{ return(CONSTANT); }
0[xX]{H}+{US}?{LS}?	{ return(CONSTANT); }
0{D}+{LS}?{US}?		{ return(CONSTANT); }
0{D}+{US}?{LS}?		{ return(CONSTANT); }
{D}+{LS}?{US}?		{ return(CONSTANT); }
{D}+{US}?{LS}?		{ return(CONSTANT); }
'(\\.|[^\\'])+'		{ return(CONSTANT); }

{D}+{E}{LS}?		{ return(CONSTANT); }
{D}*"."{D}+({E})?{LS}?	{ return(CONSTANT); }
{D}+"."{D}*({E})?{LS}?	{ return(CONSTANT); }

\"(\\.|[^\\"])*\"	{ return(STRING_LITERAL); }

.			{ /* ignore bad characters */ }



%%

yywrap()
{
	return(1);
}

main()
{
    int t;

    t = yylex();
    while (t > 0)
      {
          printf("%s\t%d\n", yytext,t);
          t = yylex();
      }

  return 0;
}


int Table_Lookup(struct KeywordToken Table[])
     /* input: Table of tokens
      * returns TokenCode of keyword if matched or
      * IDENTIFIER(in tokens.h) if text is a literal */
{
  struct KeywordToken *Curr;

  for (Curr = Table; Curr->Keyword != ""; Curr++)
    if (strcmp(Curr->Keyword,yytext)==0)
      {
	return (Curr->TokenCode);
      }
  return IDENTIFIER;
}






