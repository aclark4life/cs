From gfurr@csmaster.loyola.edu Wed Jan 29 19:39:02 1997
Return-Path: <gfurr@csmaster.loyola.edu>
Received: from wisdom.loyola.edu by csmaster.loyola.edu (SMI-8.6/SMI-SVR4)
	id TAA03369; Wed, 29 Jan 1997 19:39:02 -0500
Received: by wisdom.loyola.edu (SMI-8.6/SMI-SVR4)
	id TAA02482; Wed, 29 Jan 1997 19:44:16 -0500
From: gfurr@csmaster.loyola.edu (Gwennie Furr)
Message-Id: <199701300044.TAA02482@wisdom.loyola.edu>
Subject: tokens.h
To: aclark@csmaster (foo|sj)
Date: Wed, 29 Jan 1997 19:44:15 -0500 (EST)
X-Mailer: ELM [version 2.4 PL25]
MIME-Version: 1.0
Content-Type: text/plain; charset=US-ASCII
Content-Transfer-Encoding: 7bit
Content-Length: 5877
Status: OR

#define OPEN_PAREN_TOKEN 1                     /* ( */
#define CLOSE_PAREN_TOKEN 2                     /* ) */
#define OPEN_BRACE_TOKEN 3                     /* { */
#define CLOSE_BRACE_TOKEN 4                     /* } */
#define OPEN_BRACKET_TOKEN 5                     /* [ */
#define CLOSE_BRACKET_TOKEN 6                     /* ] */
#define SEMICOLON_TOKEN 7                     /* ; */
#define COMMA_TOKEN 8                     /* , */
#define PERIOD_TOKEN 9                     /* . */
#define ASSIGNS_TOKEN 10                     /* = */
#define GREATER_TOKEN 11                     /* > */
#define LESS_TOKEN 12                     /* < */
#define NOT_TOKEN 13                     /* ! */
#define TILDE_TOKEN 14                     /* ~ */
#define CONDITIONAL_TOKEN 15                     /* ? */
#define COLON_TOKEN 16                     /* : */
#define EQ_TOKEN 17                     /* == */
#define LE_TOKEN 18                     /* <= */
#define GE_TOKEN 19                     /* >= */
#define NE_OP_TOKEN 20                     /* != */
#define LOGICAL_OR_TOKEN 21                     /* || */
#define LOGICAL_AND_TOKEN 22                     /* && */
#define INC_TOKEN 23                     /* ++ */
#define DEC_TOKEN 24                     /* -- */
#define PLUS_TOKEN 25                     /* + */
#define MINUS_TOKEN 26                     /* - */
#define DIV_TOKEN 27                     /* / */
#define AND_TOKEN 28                     /* & */
#define OR_TOKEN 29                     /* | */
#define XOR_TOKEN 30                     /* ^ */
#define MOD_TOKEN 31                     /* % */
#define SHL_TOKEN 32                     /* << */
#define SAR_TOKEN 33                     /* >> */
#define SHR_TOKEN 34                     /* >>> */
#define ADD_ASSIGN_TOKEN 35                     /* += */
#define SUB_ASSIGN_TOKEN 36                     /* -= */
#define MUL_ASSIGN_TOKEN 37                     /* *= */
#define DIV_ASSIGN_TOKEN 38                     /* /= */
#define AND_ASSIGN_TOKEN 39                     /* &= */
#define OR_ASSIGN_TOKEN 40                     /* |= */
#define XOR_ASSIGN_TOKEN 41                     /* ^= */
#define MOD_ASSIGN_TOKEN 42                     /* %= */
#define SHL_ASSIGN_TOKEN 43                     /* <<= */
#define SAR_ASSIGN_TOKEN 44                     /* >>= */
#define SHR_ASSIGN_TOKEN 45                     /* >>>= */

#define ABSTRACT_TOKEN 46                     /* abstract */
#define BOOLEAN_TOKEN 47                     /* boolean */
#define BREAK_TOKEN 48                     /* break */
#define BYTE_TOKEN 49                     /* byte */
#define CASE_TOKEN 50                     /* case */
#define CAST_TOKEN 51                     /* cast */
#define CATCH_TOKEN 52                     /* catch */
#define CHAR_TOKEN 53                     /* char */
#define CLASS_TOKEN 54                     /* class */
#define CONST_TOKEN 55                     /* const */
#define CONTINUE_TOKEN 56                     /* continue */
#define DEFAULT_TOKEN 57                     /* default */
#define DO_TOKEN 58                     /* do */
#define DOUBLE_TOKEN 59                     /* double */
#define ELSE_TOKEN 60                     /* else */
#define EXTENDS_TOKEN 61                     /* extends */
#define FINAL_TOKEN 62                     /* final */
#define FINALLY_TOKEN 63                     /* finally */
#define FLOAT_TOKEN 64                     /* float */
#define FOR_TOKEN 65                     /* for */
#define FUTURE_TOKEN 66                     /* future */
#define GENERIC_TOKEN 67                     /* generic */
#define GOTO_TOKEN 68                     /* goto */
#define IF_TOKEN 69                     /* if */
#define IMPLEMENTS_TOKEN 70                     /* implements */
#define IMPORT_TOKEN 71                     /* import */
#define INNER_TOKEN 72                     /* inner */
#define INSTANCEOF_TOKEN 73                     /* instanceof */
#define INT_TOKEN 74                     /* int */
#define INTERFACE_TOKEN 75                     /* interface */
#define LONG_TOKEN 76                     /* long */
#define NATIVE_TOKEN 77                     /* native */
#define NEW_TOKEN 78                     /* new */
#define NULL_TOKEN 79                     /* null */
#define OPERATOR_TOKEN 80                     /* operator */
#define OUTER_TOKEN 81                     /* outer */
#define PACKAGE_TOKEN 82                     /* package */
#define PRIVATE_TOKEN 83                     /* private */
#define PROTECTED_TOKEN 84                     /* protected */
#define PUBLIC_TOKEN 85                     /* public */
#define REST_TOKEN 86                     /* rest */
#define RETURN_TOKEN 87                     /* return */
#define SHORT_TOKEN 88                     /* short */
#define STATIC_TOKEN 89                     /* static */
#define SUPER_TOKEN 90                     /* super */
#define SWITCH_TOKEN 91                     /* switch */
#define SYNCHRONIZED_TOKEN 92                     /* synchronized */
#define THIS_TOKEN 93                     /* this */
#define THROW_TOKEN 94                     /* throw */
#define THROWS_TOKEN 95                     /* throws */
#define TRANSIENT_TOKEN 96                     /* transient */
#define TRY_TOKEN 97                     /* try */
#define VAR_TOKEN 98                     /* var */
#define VOID_TOKEN 99                     /* void */
#define VOLATILE_TOKEN 100                     /* volatile */
#define WHILE_TOKEN 101                     /* while */
#define MUL_TOKEN 102                     /* * */

#define CONSTANT 103
#define STRING_LITERAL 104
#define IDENTIFIER 105
#define ID_TOKEN 106 
#define FLOATING_POINT_LITERAL_TOKEN 107
#define INTEGER_LITERAL_TOKEN 108
#define BOOLEAN_LITERAL_TOKEN 109
#define CHARACTER_LITERAL_TOKEN 110
#define STRING_LITERAL_TOKEN 111



