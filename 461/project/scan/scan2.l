D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
LS                      (l|L)
US                      (u|U)

%{
#include <stdio.h>
#include "tokens.h"
#include "structs.h"

%}

%%
"#define"     {return 1;}
{L}({L}|{D})*           { return(Table_Lookup(Table));/*change */}

0[xX]{H}+{LS}?{US}?     { return(CONSTANT); }
0[xX]{H}+{US}?{LS}?     { return(CONSTANT); }
0{D}+{LS}?{US}?         { return(CONSTANT); }
0{D}+{US}?{LS}?         { return(CONSTANT); }
{D}+{LS}?{US}?          { return(CONSTANT); }
{D}+{US}?{LS}?          { return(CONSTANT); }
'(\\.|[^\\'])+'         { return(CONSTANT); }

{D}+{E}{LS}?            { return(CONSTANT); }
{D}*"."{D}+({E})?{LS}?  { return(CONSTANT); }
{D}+"."{D}*({E})?{LS}?  { return(CONSTANT); }


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

\"(\\.|[^\\"])*\"       { return(STRING_LITERAL); }

.                       { /* ignore bad characters */ }



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
      * returns TokenCode of keyword if matched or -1 if
      * no match is found */
{
  struct KeywordToken *Curr;

  for (Curr = Table; Curr->Keyword != ""; Curr++)
    if (strcmp(Curr->Keyword,yytext)==0)
      {
        return (Curr->TokenCode);
      }

  return -1;
}


