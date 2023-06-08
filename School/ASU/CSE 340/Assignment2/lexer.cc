/*
 * Copyright (C) Rida Bazzi, 2016
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

string currscope;
int pubpriv;


string reserved[] = { "END_OF_FILE",
		"PUBLIC", "PRIVATE",
		"EQUAL", "COLON", "COMMA", "SEMICOLON",
		"LBRACE", "RBRACE", "ID", "ERROR" // TODO: Add labels for new token types here (as string)
};
#define KEYWORDS_COUNT 2
string keyword[] = { "PUBLIC", "PRIVATE" };

void Token::Print()
{

    cout <<  this->lexeme << " = " << reserved[(int) this->token_type] ;
}

void Token:: Print2()
{

    cout << this->lexeme << endl;

}

LexicalAnalyzer::LexicalAnalyzer()
{
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    tmp.token_type = ERROR;
}

bool LexicalAnalyzer::SkipSpace()
{
    char c;
    bool space_encountered = false;

    input.GetChar(c);
    line_no += (c == '\n');

    while (!input.EndOfInput() && isspace(c)) {
        space_encountered = true;
        input.GetChar(c);
        line_no += (c == '\n');
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    }
    return space_encountered;
}

bool LexicalAnalyzer::IsKeyword(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

Token LexicalAnalyzer::ScanNumber()
{
    char c;

    input.GetChar(c);
    if (isdigit(c)) {
        if (c == '0') {
            tmp.lexeme = "0";
        } else {
            tmp.lexeme = "";
            while (!input.EndOfInput() && isdigit(c)) {
                tmp.lexeme += c;
                input.GetChar(c);
            }
            if (!input.EndOfInput()) {
                input.UngetChar(c);
            }
        }
        // TODO: You can check for REALNUM, BASE08NUM and BASE16NUM here!
        //tmp.token_type = NUM;
        tmp.line_no = line_no;
        return tmp;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
        tmp.line_no = line_no;
        return tmp;
    }
}


Token LexicalAnalyzer::ScanIdOrKeyword()
{
    char c;
    input.GetChar(c);

    if (isalpha(c)) {
        tmp.lexeme = "";
        while (!input.EndOfInput() && isalnum(c)) {
            tmp.lexeme += c;
            input.GetChar(c);
        }
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.line_no = line_no;
        if (IsKeyword(tmp.lexeme))
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        else
            tmp.token_type = ID;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}

// you should unget tokens in the reverse order in which they
// are obtained. If you execute
//
//    t1 = lexer.GetToken();
//    t2 = lexer.GetToken();
//    t3 = lexer.GetToken();
//
// in this order, you should execute
//
//    lexer.UngetToken(t3);
//    lexer.UngetToken(t2);
//    lexer.UngetToken(t1);
//
// if you want to unget all three tokens. Note that it does not
// make sense to unget t1 without first ungetting t2 and t3
//
TokenType LexicalAnalyzer::UngetToken(Token tok)
{
    tokens.push_back(tok);;
    return tok.token_type;
}

Token LexicalAnalyzer::GetToken()
{
    char c;

    // if there are tokens that were previously
    // stored due to UngetToken(), pop a token and
    // return it without reading from input
    if (!tokens.empty()) {
        tmp = tokens.back();
        tokens.pop_back();
        return tmp;
    }


    SkipSpace();
    tmp.lexeme = "";
    tmp.line_no = line_no;
    input.GetChar(c);
    switch (c) {
//        case '.':
//            tmp.token_type = DOT;
//            return tmp;
//        case '+':
//            tmp.token_type = PLUS;
//            return tmp;
//        case '-':
//            tmp.token_type = MINUS;
//            return tmp;
//        case '/':
//            tmp.token_type = DIV;
//            return tmp;
//        case '*':
//            tmp.token_type = MULT;
//            return tmp;
        case '=':
            tmp.token_type = EQUAL;
            return tmp;
        case ':':
            tmp.token_type = COLON;
            return tmp;
        case ',':
            tmp.token_type = COMMA;
            return tmp;
        case ';':
            tmp.token_type = SEMICOLON;
            return tmp;
        case '{':
            tmp.token_type = LBRACE;
            return tmp;
        case '}':
            tmp.token_type = RBRACE;
            return tmp;
//        case '(':
//            tmp.token_type = LPAREN;
//            return tmp;
//        case ')':
//            tmp.token_type = RPAREN;
//            return tmp;
//        case '<':
//            input.GetChar(c);
//            if (c == '=') {
//                tmp.token_type = LTEQ;
//            } else if (c == '>') {
//                tmp.token_type = NOTEQUAL;
//            } else {
//                if (!input.EndOfInput()) {
//                    input.UngetChar(c);
//                }
//                tmp.token_type = LESS;
//            }
//            return tmp;
//        case '>':
//            input.GetChar(c);
//            if (c == '=') {
//                tmp.token_type = GTEQ;
//            } else {
//                if (!input.EndOfInput()) {
//                    input.UngetChar(c);
//                }
//                tmp.token_type = GREATER;
//            }
//            return tmp;
        default:
            if (isdigit(c)) {
                input.UngetChar(c);
                return ScanNumber();
            } else if (isalpha(c)) {
                input.UngetChar(c);
                return ScanIdOrKeyword();
            } else if (input.EndOfInput())
                tmp.token_type = END_OF_FILE;
            else
                tmp.token_type = ERROR;

            return tmp;
    }
}

Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

Token Parser::peek()
{
    Token t = lexer.GetToken();
    Token t1 = t;
    lexer.UngetToken(t);
    return t1;
}

void Parser::syntax_error()
{
    cout << "Syntax Error\n";
    exit(1);
}

void Parser :: parse_program()
{
	//program -> gloval_vars scope

//	cout << "in parse program" << endl;

	Token tmp1;

	tmp1 = lexer.GetToken();					// Should get ID
	Token t = peek();
	lexer.UngetToken(tmp1);

	if(t.token_type == COMMA || t.token_type == SEMICOLON)		// Var_list
	{
		parse_global_vars();
		parse_scope();
	}
	else if(t.token_type == LBRACE)	// scope
	{
		parse_scope();

	}
	else
	{
		syntax_error();
	}

}

void Parser :: parse_global_vars()
{
	// -> var_list semicolon
	pubpriv = 0;
	parse_var_list();
	expect(SEMICOLON);

}

void Parser :: parse_var_list()
{
//	cout << "in parse var_list" << endl;

	Token tok = lexer.GetToken();
	Token tmp1 = tok;
	lexer.UngetToken(tok);

//	if(pubpriv == 0)		//global
//	{
//		AddTable(tmp1.lexeme, "::");
//	}
//	else if(pubpriv == 1)	//pub
//	{
//		AddTable(tmp1.lexeme, currscope + ".");
//	}
//	else if(pubpriv == 2)	//priv
//	{
//		AddTable(tmp1.lexeme, currscope + ".");
//	}
//	else
//	{
//		AddTable(tmp1.lexeme, "?.");
//	}

	expect(ID);
	Token t = peek();
	if(t.token_type == COMMA)
	{
		expect(COMMA);
		parse_var_list();
	}
}


void Parser :: parse_scope()
{
//	cout << "in parse scope" << endl;


	// trying linked list
	Token tok = lexer.GetToken();
	Token tmp1 = tok;
	lexer.UngetToken(tok);

	currscope = tmp1.lexeme;


	expect(ID);

	expect(LBRACE);

	//peek for next: if public then public var if private then private var
	Token t = peek();
	if(t.token_type == PUBLIC)
	{
		parse_public_vars();
	}
	t = peek();
	if(t.token_type == PRIVATE)
	{
		parse_private_vars();
	}
	t = peek();
	if(t.token_type == ID)
	{
		parse_stmt_list();
	}
	else
	{
		syntax_error();
	}

	expect(RBRACE);


}

void Parser :: parse_public_vars()
{
//	cout << "in parse public_vars" << endl;
	expect(PUBLIC);
	expect(COLON);
	parse_var_list();
	expect(SEMICOLON);
//	cout << "in parse public_vars2" << endl;

}

void Parser :: parse_private_vars()
{
//	cout << "in parse private_vars" << endl;
	expect(PRIVATE);
	expect(COLON);
	parse_var_list();
	expect(SEMICOLON);
}

void Parser :: parse_stmt_list()
{
//	cout << "in parse stmt_list" << endl;

	parse_stmt();

	Token t = peek();

	if(t.token_type == ID)
	{
		parse_stmt_list();
	}

//	cout << "back in stmt list" << endl;



}

void Parser :: parse_stmt()
{
//	cout << "in parse stmt" << endl;
	Token tmp1;
	tmp1 = lexer.GetToken();
	Token t = peek();
	lexer.UngetToken(tmp1);

	if(t.token_type == EQUAL)
	{
		expect(ID);
		expect(EQUAL);
		expect(ID);
		expect(SEMICOLON);
	}
	else if(t.token_type == LBRACE)
	{

		parse_scope();
	}
	else
	{
		syntax_error();
	}

}

void Parser::ParseInput()
{
//	cout << "in parse input" << endl;
    parse_program();
    expect(END_OF_FILE);
}

//void Parser :: AddTable(string id, string  scope)
//{
//	Node* curr = head;
//	if(head == NULL)
//	{
//		head->id = id;
//		head->scope = scope;
//	}
//	else
//	{
//		while(curr->next != NULL)
//		{
//			curr = curr->next;
//		}
//		curr->id = id;
//		curr->scope = scope;
//	}
//}


int main()
{
    LexicalAnalyzer lexer;
    Parser parser;
    Token token;
    SymbolTable st;

    parser.ParseInput();






//    token = lexer.GetToken();
//    //token.Print();
//    while (token.token_type != END_OF_FILE)
//    {
//        token = lexer.GetToken();
//        //token.Print();
//    }
}
