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

"("     { return (OPEN_PAREN_TOKEN) }

"("     { return (OPEN_PAREN_TOKEN) }
"{"     { return (OPEN_BRACE_TOKEN) }
"}"     { return (CLOSE_BRACE_TOKEN) }
"["     { return (OPEN_BRACKET_TOKEN) }
  {"]", CLOSE_BRACKET_TOKEN },
  {";", SEMICOLON_TOKEN },
  {",", COMMA_TOKEN },
  {".", PERIOD_TOKEN },
  {"=", ASSIGNS_TOKEN },
  {">", GREATER_TOKEN },
  {"<", LESS_TOKEN },
  {"!", NOT_TOKEN },
  {"~", TILDE_TOKEN },
  {"?", CONDITIONAL_TOKEN },
  {":", COLON_TOKEN },
  {"==", EQ_TOKEN },
  {"<=", LE_TOKEN },
  {">=", GE_TOKEN },
  {"!=", NE_OP_TOKEN },
  {"||", LOGICAL_OR_TOKEN },
  {"&&", LOGICAL_AND_TOKEN },
  {"++", INC_TOKEN },
  {"--", DEC_TOKEN },
  {"+", PLUS_TOKEN },
  {"-", MINUS_TOKEN },
  {"*", MUL_TOKEN },
  {"/", DIV_TOKEN },
  {"&", AND_TOKEN },
 {"|", OR_TOKEN },
  {"^", XOR_TOKEN },
  {"%", MOD_TOKEN },
  {"<<", SHL_TOKEN },
  {">>", SAR_TOKEN },
  {">>>", SHL_TOKEN },
  {"+=", ADD_ASSIGN_TOKEN },
  {"-=", SUB_ASSIGN_TOKEN },
  {"*=", MUL_ASSIGN_TOKEN },
  {"/=", DIV_ASSIGN_TOKEN },
  {"&=", AND_ASSIGN_TOKEN },
  {"|=",  OR_ASSIGN_TOKEN },
  {"^=", XOR_ASSIGN_TOKEN },
  {"%=", MOD_ASSIGN_TOKEN },
  {"<<=", SHL_ASSIGN_TOKEN },
  {">>=", SAR_ASSIGN_TOKEN },
  {">>>=", SHR_ASSIGN_TOKEN },
  {"", -1 }


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

