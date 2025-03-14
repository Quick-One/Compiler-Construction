/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>

#define MAX_BUFFER_SIZE 50
#define MAX_STATES 65
#define MAX_TOKENS 100

static const char ALPHABETS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '\n', '\t', '~', '(', '[', ']', ')', '<', '>', '!', '@', '#', '%', '&', '*', '_', '+', '-', '/', '=', ';', ':', '.', ','};
static const int ALPHABET_SIZE = sizeof(ALPHABETS) / sizeof(ALPHABETS[0]);
static const char *const TOKENS[] = {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype", "constructedDatatype", "remaining_list", "stmts", "typeDefinitions", "typeDefinition", "actualOrRedefined", "fieldDefinitions", "fieldDefinition", "fieldType", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", "assignmentStmt", "singleOrRecId", "option_single_constructed", "oneExpansion", "moreExpansions", "funCallStmt", "outputParameters", "inputParameters", "iterativeStmt", "conditionalStmt", "elsePart", "ioStmt", "arithmeticExpression", "expPrime", "termPrime", "term", "factor", "lowPrecedenceOperators", "highPrecedenceOperators", "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A", "TK_NOTOKEN", "TK_INVALID", "TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RUID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_UNION", "TK_ENDUNION", "TK_DEFINETYPE", "TK_AS", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "TK_DOLLAR", "TK_EPSILON", 0};

typedef enum state_id
{
    S_0,
    S_1,
    S_2,
    S_3,
    S_4,
    S_5,
    S_6,
    S_7,
    S_8,
    S_9,
    S_10,
    S_11,
    S_12,
    S_13,
    S_14,
    S_15,
    S_16,
    S_17,
    S_18,
    S_19,
    S_20,
    S_21,
    S_22,
    S_23,
    S_24,
    S_25,
    S_26,
    S_27,
    S_28,
    S_29,
    S_30,
    S_31,
    S_32,
    S_33,
    S_34,
    S_35,
    S_36,
    S_37,
    S_38,
    S_39,
    S_40,
    S_41,
    S_42,
    S_43,
    S_44,
    S_45,
    S_46,
    S_47,
    S_48,
    S_49,
    S_50,
    S_51,
    S_52,
    S_53,
    S_54,
    S_55,
    S_56,
    S_57,
    S_58,
    S_59,
    S_60,
    S_61,
    S_62,
    START,
    INVALID,
} state_id; // Enum for state ids

typedef enum token_id
{
    program,
    mainFunction,
    otherFunctions,
    function,
    input_par,
    output_par,
    parameter_list,
    dataType,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    typeDefinition,
    actualOrRedefined,
    fieldDefinitions,
    fieldDefinition,
    fieldType,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    singleOrRecId,
    option_single_constructed,
    oneExpansion,
    moreExpansions,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    arithmeticExpression,
    expPrime,
    termPrime,
    term,
    factor,
    lowPrecedenceOperators,
    highPrecedenceOperators,
    booleanExpression,
    var,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A,
    TK_NOTOKEN,
    TK_INVALID,
    TK_ASSIGNOP,
    TK_COMMENT,
    TK_FIELDID,
    TK_ID,
    TK_NUM,
    TK_RNUM,
    TK_FUNID,
    TK_RUID,
    TK_WITH,
    TK_PARAMETERS,
    TK_END,
    TK_WHILE,
    TK_UNION,
    TK_ENDUNION,
    TK_DEFINETYPE,
    TK_AS,
    TK_TYPE,
    TK_MAIN,
    TK_GLOBAL,
    TK_PARAMETER,
    TK_LIST,
    TK_SQL,
    TK_SQR,
    TK_INPUT,
    TK_OUTPUT,
    TK_INT,
    TK_REAL,
    TK_COMMA,
    TK_SEM,
    TK_COLON,
    TK_DOT,
    TK_ENDWHILE,
    TK_OP,
    TK_CL,
    TK_IF,
    TK_THEN,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_RETURN,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_CALL,
    TK_RECORD,
    TK_ENDRECORD,
    TK_ELSE,
    TK_AND,
    TK_OR,
    TK_NOT,
    TK_LT,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    TK_DOLLAR,
    TK_EPSILON
} token_id; // Enum for token ids

typedef struct TwinBuffer
{
    char primary_buffer[MAX_BUFFER_SIZE];
    char secondary_buffer[MAX_BUFFER_SIZE];
    int primary_buffer_index;
    int secondary_buffer_index;
    int line_count;
} TwinBuffer;

typedef struct Token
{
    token_id tk;
    int lc;
    char *lexeme;
} Token;

typedef struct TokenInfo
{
    struct Token **tokens;
    int token_count;
} TokenInfo;

typedef struct State
{
    struct Transition **transitions;
    int length;
    token_id token;
    int retract_count;
    int state_id;
} State;

typedef struct Transition
{
    char next_char;
    struct State *next_state;
} Transition;

typedef struct State *state;           // Pointer to a state
typedef struct Transition *transition; // Pointer to a transition
typedef struct TwinBuffer *twinBuffer; // Pointer to a twin buffer
typedef struct TokenInfo *tokenInfo;   // Pointer to a token info
typedef struct Token *token;           // Pointer to a token

// Array of states for the graph


// #ifndef TRIE_INCOMPLETE
// #include "trie.h"

// #endif

#include "lexer.h"
#endif