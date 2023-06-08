/*
 * Copyright (C) Rida Bazzi, 2016
 *
 * Do not share this file with anyone
 */
#ifndef __LEXER__H__
#define __LEXER__H__

#include <vector>
#include <string>

#include "inputbuf.h"

// ------- token types -------------------

typedef enum { END_OF_FILE = 0,
INT, REAL,
BOOL, TRUE, FALSE, IF, WHILE, SWITCH,
CASE, NOT, PLUS, MINUS, MULT, DIV,
GREATER, LESS, GTEQ, LTEQ, NOTEQUAL,
LPAREN, RPAREN, NUM, REALNUM,
PUBLIC, PRIVATE,
EQUAL, COLON, COMMA, SEMICOLON,
LBRACE, RBRACE, ID, ERROR
} TokenType;


class Token {
  public:
    void Print();
    void Print2();
    std::string lexeme;
    TokenType token_type;
    int line_no;
};

class LexicalAnalyzer {
  public:
    Token GetToken();
    TokenType UngetToken(Token);
    LexicalAnalyzer();

  private:
    std::vector<Token> tokens;
    int line_no;
    Token tmp;
    InputBuffer input;

    bool SkipComments();
    bool SkipSpace();
    bool IsKeyword(std::string);
    TokenType FindKeywordIndex(std::string);
    Token ScanIdOrKeyword();
    Token ScanNumber();
};

class SymbolTable
{
public:
    int scope;
    std::string variable;

};

struct Node
{
	std::string id;
    std::string scope;
    struct Node* next;
};

class Parser {
  public:
    LexicalAnalyzer lexer;
    struct Node* head;
    void syntax_error();
	void AddTable(std::string id, std::string scope );
    Token expect(TokenType expected_type);
    Token peek();

//    Token parse_input();



    int parse_program();

    int parse_body();

    int parse_var_decl();

    int parse_global_vars();

    int parse_var_list();

    int parse_scope();

    int parse_public_vars();

    int parse_private_vars();

    int parse_stmt_list();

    int parse_stmt();

    int parse_case();

    int parse_binary_operator();

    int parse_unary_operator();

    int parse_assignment_stmt();

    int parse_case_list();

    int parse_switch_stmt();

    int parse_while_stmt();

    int parse_if_stmt();

    int parse_typename();

    int parse_var_decl_list();

    int parse_primary();

    int parse_expression();


  public:
    void ParseInput();
};

#endif  //__LEXER__H__
