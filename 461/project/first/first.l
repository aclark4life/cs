%%
.|\n	{ ECHO; } 
%%

yywrap()
{
	return(1);
}


main() 
{
	int foo;
  	foo = yylex();
	while (foo > 0)
 	{
     		 foo= yylex();
 	}
	return(0);
}
