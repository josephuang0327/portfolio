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



    void parse_program();

    void parse_global_vars();

    void parse_var_list();

	void parse_scope();

    void parse_public_vars();

    void parse_private_vars();

    void parse_stmt_list();

    void parse_stmt();




  public:
    void ParseInput();
};

#endif  //__LEXER__H__
