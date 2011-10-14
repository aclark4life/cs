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
  {"", -1}
};

struct OpToken
{
	char *Op;
	int TokenCode;

};

struct OpToken OpTable [] = 
{
  {"(", OPEN_PAREN_TOKEN },
  {")", CLOSE_PAREN_TOKEN },
  {"}", OPEN_BRACE_TOKEN },
  {"}", CLOSE_BRACE_TOKEN },
  {"[", OPEN_BRACKET_TOKEN },
  {"]", CLOSE_BRACKET_TOKEN },
  {";", SEMICOLON_TOKEN },
  {",", COMMA_TOKEN },
  {".", PERIOD_TOKEN },
  {"=", ASSIGNS_TOKEN },
  {">", GREATER_TOKEN },
  {"<", LESS_TOKEN },
  {"!", NOT_TOKEN },
  {"?", CONDITIONAL_TOKEN },
  {";", COLON_TOKEN },
  {"==" EQ_TOKEN },

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
{"", -1}
};

