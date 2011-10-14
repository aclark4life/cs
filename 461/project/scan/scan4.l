D			[0-9]
N                       [1-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
OC                      [0-7]
E			[Ee][+-]?{D}+
LS			[fFdD]
Escape                  \\[ntbrf\\'"]

%{
#include <stdio.h>
#include "tokens.h"
#include "table.h"
%}

%%

{N}{D}*(l|L)?           { return(INTEGER_LITERAL_TOKEN); }
0[xX]{H}+(l|L)?	        { return(INTEGER_LITERAL_TOKEN); }
0{OC}*(l|L)?     	{ return(INTEGER_LITERAL_TOKEN); }

{D}+"."{D}*({E})?{LS}?	{ return(FLOATING_POINT_LITERAL_TOKEN); }
"."{D}+({E})?{LS}?	{ return(FLOATING_POINT_LITERAL_TOKEN); }
{D}+{E}{LS}?            { return(FLOATING_POINT_LITERAL_TOKEN); }

"true"                  { return(BOOLEAN_LITERAL_TOKEN); }
"false"                 { return(BOOLEAN_LITERAL_TOKEN); }

{L}({L}|{D})*		{ return(Table_Lookup(KeywordTable));}

'[^'\\]'                { return(CHARACTER_LITERAL_TOKEN);}
'{Escape}'              { return(CHARACTER_LITERAL_TOKEN);}


\"([^\"\\]|{Escape})*\"             { return(STRING_LITERAL_TOKEN); }

\/\/.*$			{}
\/\*			{ comment();}
\/\*\*			{ comment();}

"("     { return (OPEN_PAREN_TOKEN); }
")"     { return (CLOSE_PAREN_TOKEN); }
"{"     { return (OPEN_BRACE_TOKEN); }
"}"     { return (CLOSE_BRACE_TOKEN); }
"["     { return (OPEN_BRACKET_TOKEN); }
"]"     { return (CLOSE_BRACKET_TOKEN); }
";"     { return (SEMICOLON_TOKEN); }
","     { return (COMMA_TOKEN); }
"."     { return (PERIOD_TOKEN); }
"="     { return (ASSIGNS_TOKEN); }
">"     { return (GREATER_TOKEN); }
"<"     { return (LESS_TOKEN); }
"!"     { return (NOT_TOKEN); }
"~"     { return (TILDE_TOKEN); }
"?"     { return (CONDITIONAL_TOKEN); }
":"     { return (COLON_TOKEN); }
"=="    { return (EQ_TOKEN); }
"<="    { return (LE_TOKEN); }
">="    { return (GE_TOKEN); }
"!="    { return (NE_OP_TOKEN); }
"||"    { return (LOGICAL_OR_TOKEN); }
"&&"    { return (LOGICAL_AND_TOKEN); }
"++"    { return (INC_TOKEN); }
"--"    { return (DEC_TOKEN); }
"+"     { return (PLUS_TOKEN); }
"-"     { return (MINUS_TOKEN); }
"*"     { return (MUL_TOKEN); }
"/"     { return (DIV_TOKEN); }
"&"     { return (AND_TOKEN); }
"|"     { return (OR_TOKEN); }
"^"     { return (XOR_TOKEN); }
"%"     { return (MOD_TOKEN); }
"<<"    { return (SHL_TOKEN); }
">>"    { return (SAR_TOKEN); }
">>>"   { return (SHL_TOKEN); }
"+="    { return (ADD_ASSIGN_TOKEN); }
"-="    { return (SUB_ASSIGN_TOKEN); }
"*="    { return (MUL_ASSIGN_TOKEN); }
"/="    { return (DIV_ASSIGN_TOKEN); }
"&="    { return (AND_ASSIGN_TOKEN); }
"|="    { return (OR_ASSIGN_TOKEN); }
"^="    { return (XOR_ASSIGN_TOKEN); }
"%="    { return (MOD_ASSIGN_TOKEN); }
"<<="   { return (SHL_ASSIGN_TOKEN); }
">>="   { return (SAR_ASSIGN_TOKEN); }
">>>="  { return (SHR_ASSIGN_TOKEN); }

[ \t\v\n\f]             {}

.			{ printf("unknown char %c ignored\n", yytext[0]); /* ignore bad characters ????*/}



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
	IDENTIFIER if no match is found */
{
  struct KeywordToken *Curr;

  for (Curr = Table; Curr->Keyword != ""; Curr++)
    if (strcmp(Curr->Keyword,yytext)==0)
      {
	return (Curr->TokenCode);
      }
  return IDENTIFIER;
}

comment()
{
	char c = -1, c1;
        while(c != 0)
        {
        for(c = input(); c != '*' && c!=0; c = input())
          ;
        /* now we have a star or no more chars */
        if(c== 0 || (c1 = input() == '/'))
          return;
        if (c1 == '*')
          unput(c1);
        }
}


From gfurr@csmaster.loyola.edu Wed Jan 29 19:38:38 1997
Return-Path: <gfurr@csmaster.loyola.edu>
Received: from wisdom.loyola.edu by csmaster.loyola.edu (SMI-8.6/SMI-SVR4)
	id TAA03358; Wed, 29 Jan 1997 19:38:38 -0500
Received: by wisdom.loyola.edu (SMI-8.6/SMI-SVR4)
	id TAA02470; Wed, 29 Jan 1997 19:43:51 -0500
From: gfurr@csmaster.loyola.edu (Gwennie Furr)
Message-Id: <199701300043.TAA02470@wisdom.loyola.edu>
Subject: scan.l
To: aclark@csmaster (foo|sj)
Date: Wed, 29 Jan 1997 19:43:51 -0500 (EST)
X-Mailer: ELM [version 2.4 PL25]
MIME-Version: 1.0
Content-Type: text/plain; charset=US-ASCII
Content-Transfer-Encoding: 7bit
Content-Length: 3660
Status: OR

D			[0-9]
N                       [1-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
OC                      [0-7]
E			[Ee][+-]?{D}+
LS			[fFdD]
Escape                  \\[ntbrf\\'"]

%{
#include <stdio.h>
#include "tokens.h"
#include "table.h"
%}

%%

{N}{D}*(l|L)?           { return(INTEGER_LITERAL_TOKEN); }
0[xX]{H}+(l|L)?	        { return(INTEGER_LITERAL_TOKEN); }
0{OC}*(l|L)?     	{ return(INTEGER_LITERAL_TOKEN); }

{D}+"."{D}*({E})?{LS}?	{ return(FLOATING_POINT_LITERAL_TOKEN); }
"."{D}+({E})?{LS}?	{ return(FLOATING_POINT_LITERAL_TOKEN); }
{D}+{E}{LS}?            { return(FLOATING_POINT_LITERAL_TOKEN); }

"true"                  { return(BOOLEAN_LITERAL_TOKEN); }
"false"                 { return(BOOLEAN_LITERAL_TOKEN); }

{L}({L}|{D})*		{ return(Table_Lookup(KeywordTable));}

'[^'\\]'                { return(CHARACTER_LITERAL_TOKEN);}
'{Escape}'              { return(CHARACTER_LITERAL_TOKEN);}


\"([^\"\\]|{Escape})*\"             { return(STRING_LITERAL_TOKEN); }

\/\/.*$			{}
\/\*(.$)*\*\\		{}
\/\*\*(\/|.*($)?\*\\)	{}		

"("     { return (OPEN_PAREN_TOKEN); }
")"     { return (CLOSE_PAREN_TOKEN); }
"{"     { return (OPEN_BRACE_TOKEN); }
"}"     { return (CLOSE_BRACE_TOKEN); }
"["     { return (OPEN_BRACKET_TOKEN); }
"]"     { return (CLOSE_BRACKET_TOKEN); }
";"     { return (SEMICOLON_TOKEN); }
","     { return (COMMA_TOKEN); }
"."     { return (PERIOD_TOKEN); }
"="     { return (ASSIGNS_TOKEN); }
">"     { return (GREATER_TOKEN); }
"<"     { return (LESS_TOKEN); }
"!"     { return (NOT_TOKEN); }
"~"     { return (TILDE_TOKEN); }
"?"     { return (CONDITIONAL_TOKEN); }
":"     { return (COLON_TOKEN); }
"=="    { return (EQ_TOKEN); }
"<="    { return (LE_TOKEN); }
">="    { return (GE_TOKEN); }
"!="    { return (NE_OP_TOKEN); }
"||"    { return (LOGICAL_OR_TOKEN); }
"&&"    { return (LOGICAL_AND_TOKEN); }
"++"    { return (INC_TOKEN); }
"--"    { return (DEC_TOKEN); }
"+"     { return (PLUS_TOKEN); }
"-"     { return (MINUS_TOKEN); }
"*"     { return (MUL_TOKEN); }
"/"     { return (DIV_TOKEN); }
"&"     { return (AND_TOKEN); }
"|"     { return (OR_TOKEN); }
"^"     { return (XOR_TOKEN); }
"%"     { return (MOD_TOKEN); }
"<<"    { return (SHL_TOKEN); }
">>"    { return (SAR_TOKEN); }
">>>"   { return (SHL_TOKEN); }
"+="    { return (ADD_ASSIGN_TOKEN); }
"-="    { return (SUB_ASSIGN_TOKEN); }
"*="    { return (MUL_ASSIGN_TOKEN); }
"/="    { return (DIV_ASSIGN_TOKEN); }
"&="    { return (AND_ASSIGN_TOKEN); }
"|="    { return (OR_ASSIGN_TOKEN); }
"^="    { return (XOR_ASSIGN_TOKEN); }
"%="    { return (MOD_ASSIGN_TOKEN); }
"<<="   { return (SHL_ASSIGN_TOKEN); }
">>="   { return (SAR_ASSIGN_TOKEN); }
">>>="  { return (SHR_ASSIGN_TOKEN); }

[ \t\v\n\f]             {}

.			{ printf("unknown char %c ignored\n", yytext[0]); /* ignore bad characters ????*/}



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
	IDENTIFIER if no match is found */
{
  struct KeywordToken *Curr;

  for (Curr = Table; Curr->Keyword != ""; Curr++)
    if (strcmp(Curr->Keyword,yytext)==0)
      {
	return (Curr->TokenCode);
      }
  return IDENTIFIER;
}

#if 0
void comment(void)
{

return;
}
comment()
{
        char c, c1;

loop:
        while ((c = input()) != '*' && c != 0)
                putchar(c);

        if ((c1 = input()) != '/' && c != 0)
        {
                unput(c1);
                goto loop;
        }

        if (c != 0)
                putchar(c1);
}
#endif

