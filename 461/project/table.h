From gfurr@csmaster.loyola.edu Wed Jan 29 19:38:49 1997
Return-Path: <gfurr@csmaster.loyola.edu>
Received: from wisdom.loyola.edu by csmaster.loyola.edu (SMI-8.6/SMI-SVR4)
	id TAA03364; Wed, 29 Jan 1997 19:38:49 -0500
Received: by wisdom.loyola.edu (SMI-8.6/SMI-SVR4)
	id TAA02475; Wed, 29 Jan 1997 19:44:03 -0500
From: gfurr@csmaster.loyola.edu (Gwennie Furr)
Message-Id: <199701300044.TAA02475@wisdom.loyola.edu>
Subject: table.h
To: aclark@csmaster (foo|sj)
Date: Wed, 29 Jan 1997 19:44:03 -0500 (EST)
X-Mailer: ELM [version 2.4 PL25]
MIME-Version: 1.0
Content-Type: text/plain; charset=US-ASCII
Content-Transfer-Encoding: 7bit
Content-Length: 1738
Status: OR

# include "tokens.h"

struct KeywordToken
{
	char * Keyword;
	int TokenCode;

};

struct KeywordToken KeywordTable [] = 
{

  {"abstract", ABSTRACT_TOKEN },
  {"boolean", BOOLEAN_TOKEN },
  {"break", BREAK_TOKEN },
  {"byte", BYTE_TOKEN },
  {"case", CASE_TOKEN }, 
  {"default", CAST_TOKEN },
  {"catch", CATCH_TOKEN },
  {"char", CHAR_TOKEN },
  {"class", CLASS_TOKEN },
  {"const", CONST_TOKEN },
  {"continue", CONTINUE_TOKEN },
  {"default", DEFAULT_TOKEN },
  {"do", DO_TOKEN },
  {"double", DOUBLE_TOKEN },
  {"else", ELSE_TOKEN },
  {"extends", EXTENDS_TOKEN },
  {"final", FINAL_TOKEN },
  {"finally", FINALLY_TOKEN },
  {"float", FLOAT_TOKEN },
  {"for", FOR_TOKEN },
  {"future", FUTURE_TOKEN },
  {"generic", GENERIC_TOKEN },
  {"goto", GOTO_TOKEN },
  {"if", IF_TOKEN },
  {"implements", IMPLEMENTS_TOKEN },
  {"import", IMPORT_TOKEN },
  {"inner", INNER_TOKEN },
  {"instanceof", INSTANCEOF_TOKEN },
  {"int", INT_TOKEN },
  {"interface", INTERFACE_TOKEN },
  {"long", LONG_TOKEN },
  {"native", NATIVE_TOKEN },
  {"new", NEW_TOKEN },
  {"null", NULL_TOKEN },
  {"operator", OPERATOR_TOKEN },
  {"outer", OUTER_TOKEN },
  {"package", PACKAGE_TOKEN },
  {"private", PRIVATE_TOKEN },
  {"protected", PROTECTED_TOKEN },
  {"public", PUBLIC_TOKEN },
  {"rest", REST_TOKEN },
  {"return", RETURN_TOKEN },
  {"short", SHORT_TOKEN },
  {"static", STATIC_TOKEN },
  {"super", SUPER_TOKEN },
  {"switch", SWITCH_TOKEN },
  {"synchronized", SYNCHRONIZED_TOKEN },
  {"this", THIS_TOKEN },
  {"throw", THROW_TOKEN },
  {"throws", THROWS_TOKEN },
  {"transient", TRANSIENT_TOKEN },
  {"try", TRY_TOKEN },
  {"var", VAR_TOKEN },
  {"void", VOID_TOKEN },
  {"volatile", VOLATILE_TOKEN },
  {"while", WHILE_TOKEN },
  {"", IDENTIFIER}
};



