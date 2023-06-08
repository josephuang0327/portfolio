#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <exception>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

#define KEYWORDS_COUNT 11
string keyword[] = {"int", "real", "bool", "true",
                    "false", "if", "while", "switch",
                    "case", "public", "private"};

LexicalAnalyzer input;
Token token;
int enumCount = 4;


struct sTableEntry
{
    string name;
    int lineNo;
    int type;
    int printed;
};

struct sTable
{
    sTableEntry *item;
    sTable *prev;
    sTable *next;
};

sTable *symbolTable;
int line = 0;
string output = "";

void updateTypes(int LHS, int RHS);
void addList(std::string n, int lN, int t);
int searchList(std::string n);

class type_mismatch_exception: public exception
{
    string type;
    int line;
public:
    type_mismatch_exception(const string& type, int line) {
        this->type = type;
        this->line = line;
    }

    virtual ~type_mismatch_exception() throw() {}

    virtual const char* what() const throw()
    {
        return "My exception happened";
    }
};

string token_type_name(TokenType token) {
    switch (token) {
        case END_OF_FILE:
            return "END_OF_FILE";
        case INT:
            return "INT";
        case REAL:
            return "REAL";
        case BOOL:
            return "BOOL";
        case TRUE:
            return "TRUE";
        case FALSE:
            return "FALSE";
        case IF:
            return "IF";
        case WHILE:
            return "WHILE";
        case SWITCH:
            return "SWITCH";
        case CASE:
            return "CASE";
        case NOT:
            return "NOT";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MULT:
            return "MULT";
        case DIV:
            return "DIV";
        case GREATER:
            return "GREATER";
        case LESS:
            return "LESS";
        case GTEQ:
            return "GTEQ";
        case LTEQ:
            return "LTEQ";
        case NOTEQUAL:
            return "NOTEQUAL";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case NUM:
            return "NUM";
        case REALNUM:
            return "REALNUM";
        case PUBLIC:
            return "PUBLIC";
        case PRIVATE:
            return "PRIVATE";
        case EQUAL:
            return "EQUAL";
        case COLON:
            return "COLON";
        case COMMA:
            return "COMMA";
        case SEMICOLON:
            return "SEMICOLON";
        case LBRACE:
            return "LBRACE";
        case RBRACE:
            return "RBRACE";
        case ID:
            return "ID";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void addList(std::string name, int line, int type) {
    if (symbolTable == NULL) {
        sTable *newEntry = new sTable();
        sTableEntry *newItem = new sTableEntry();

        newItem->name = name;
        newItem->lineNo = token.line_no;
        newItem->type = type;
        newItem->printed = 0;

        newEntry->item = newItem;
        newEntry->next = NULL;
        newEntry->prev = NULL;

        symbolTable = newEntry;

    } else {
        sTable *temp = symbolTable;
        while (temp->next != NULL) {
            if (temp->item->name == name) {
                temp->item->type = type;
                return;
            }
            temp = temp->next;
        }

        sTable *newEntry = new sTable();
        sTableEntry *newItem = new sTableEntry();

        newItem->name = name;
        newItem->lineNo = token.line_no;
        newItem->type = type;
        newItem->printed = 0;

        newEntry->item = newItem;
        newEntry->next = NULL;
        newEntry->prev = temp;
        temp->next = newEntry;
    }
}

int searchList(std::string n) {
    sTable *temp = symbolTable;
    bool found = false;
    if (symbolTable == NULL) {
        addList(n, token.line_no, enumCount);
        enumCount++;
        return (enumCount - 1);
    } else {
        while (temp->next != NULL) {
            if (strcmp(temp->item->name.c_str(), n.c_str()) == 0) {
                found = true;
                // std::cout << "[dbg] while->type = "<<  temp->item->type << '\n';
                return (temp->item->type);
            } else {
                temp = temp->next;
            }
        }
        if (strcmp(temp->item->name.c_str(), n.c_str()) == 0) {
            found = true;
            // std::cout << "[dbg] if->type = "<<  temp->item->type << '\n';
            return (temp->item->type);
        }
        if (!found) {
            addList(n, token.line_no, enumCount);
            enumCount++;
            int t = enumCount - 1;
            return (t);
        }
    }
    return 0;
}


void Token::Print() {
    cout << "{" << this->lexeme << " , "
         << token_type_name(this->token_type) << " , "
         << this->line_no << "}\n";
}

LexicalAnalyzer::LexicalAnalyzer() {
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    line = 1;
    tmp.token_type = ERROR;
}

bool LexicalAnalyzer::SkipSpace() {
    char c;
    bool space_encountered = false;

    input.GetChar(c);
    line_no += (c == '\n');
    line = line_no;

    while (!input.EndOfInput() && isspace(c)) {
        space_encountered = true;
        input.GetChar(c);
        line_no += (c == '\n');
        line = line_no;
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    }
    return space_encountered;
}

bool LexicalAnalyzer::SkipComments() {
    bool comments = false;
    char c;
    if (input.EndOfInput()) {
        input.UngetChar(c);
        return comments;
    }

    input.GetChar(c);

    if (c == '/') {
        input.GetChar(c);
        if (c == '/') {
            comments = true;
            while (c != '\n') {
                comments = true;
                input.GetChar(c);
            }
            line_no++;
            line = line_no;
            SkipComments();
        } else {
            comments = false;
            cout << "Syntax Error\n";
            exit(0);
        }
    } else {
        input.UngetChar(c);
        return comments;
    }
    return true;
}

bool LexicalAnalyzer::IsKeyword(string s) {
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s) {
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

Token LexicalAnalyzer::ScanNumber() {
    char c;
    bool realNUM = false;
    input.GetChar(c);
    if (isdigit(c)) {
        if (c == '0') {
            tmp.lexeme = "0";
            input.GetChar(c);
            if (c == '.') {
                input.GetChar(c);

                if (!isdigit(c)) {
                    input.UngetChar(c);
                } else {
                    while (!input.EndOfInput() && isdigit(c)) {
                        tmp.lexeme += c;
                        input.GetChar(c);
                        realNUM = true;
                    }
                    input.UngetChar(c);
                }
            } else {
                input.UngetChar(c);
            }
        } else {
            tmp.lexeme = "";
            while (!input.EndOfInput() && isdigit(c)) {
                tmp.lexeme += c;
                input.GetChar(c);
            }
            if (c == '.') {
                input.GetChar(c);

                if (!isdigit(c)) {
                    input.UngetChar(c);
                } else {
                    while (!input.EndOfInput() && isdigit(c)) {
                        tmp.lexeme += c;
                        input.GetChar(c);
                        realNUM = true;
                    }
                }
            }
            if (!input.EndOfInput()) {
                input.UngetChar(c);
            }
        }

        if (realNUM) {
            tmp.token_type = REALNUM;
        } else {
            tmp.token_type = NUM;
        }
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

Token LexicalAnalyzer::ScanIdOrKeyword() {
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

        if (IsKeyword(tmp.lexeme)) {
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        } else {
            tmp.token_type = ID;
        }
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}


TokenType LexicalAnalyzer::UngetToken(Token tok) {
    tokens.push_back(tok);;
    return tok.token_type;
}

Token LexicalAnalyzer::GetToken() {
    char c;

    if (!tokens.empty()) {
        tmp = tokens.back();
        tokens.pop_back();
        return tmp;
    }

    SkipSpace();
    // SkipComments();
    SkipSpace();
    tmp.lexeme = "";
    tmp.line_no = line_no;
    input.GetChar(c);
    //cout << "\n Char obtained " << c << "\n";
    switch (c) {
        case '!':
            tmp.token_type = NOT;
            return tmp;
        case '+':
            tmp.token_type = PLUS;
            return tmp;
        case '-':
            tmp.token_type = MINUS;
            return tmp;
        case '*':
            tmp.token_type = MULT;
            return tmp;
        case '/':
            tmp.token_type = DIV;
            return tmp;
        case '>':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = GTEQ;
            } else {
                input.UngetChar(c);
                tmp.token_type = GREATER;
            }
            return tmp;
        case '<':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = LTEQ;
            } else if (c == '>') {
                tmp.token_type = NOTEQUAL;
            } else {
                input.UngetChar(c);
                tmp.token_type = LESS;
            }
            return tmp;
        case '(':
            tmp.token_type = LPAREN;
            return tmp;
        case ')':
            tmp.token_type = RPAREN;
            return tmp;
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
        default:
            if (isdigit(c)) {
                input.UngetChar(c);
                return ScanNumber();
            } else if (isalpha(c)) {
                input.UngetChar(c);
                //cout << "[dbg]  ID scan " << c << " \n";
                return ScanIdOrKeyword();
            } else if (input.EndOfInput()) {
                tmp.token_type = END_OF_FILE;
            } else {
                tmp.token_type = ERROR;
            }
            return tmp;
    }
}

int Parser::parse_var_list() {
    token = input.GetToken();
    int var;
    addList(token.lexeme, token.line_no, 0);

    if (token.token_type == ID) {
        token = input.GetToken();
        if (token.token_type == COMMA) {
            var = parse_var_list();
        } else if (token.token_type == COLON) {
            input.UngetToken(token);
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_unary_operator() {
    token = input.GetToken();

    if (token.token_type == NOT) {
        return (1);
    } else {
        syntax_error();
        return (0);
    }
}

int Parser::parse_binary_operator() {
    token = input.GetToken();
    if (token.token_type == PLUS) {
        return (15);
    } else if (token.token_type == MINUS) {
        return (16);
    } else if (token.token_type == MULT) {
        return (17);
    } else if (token.token_type == DIV) {
        return (18);
    } else if (token.token_type == GREATER) {
        return (20);
    } else if (token.token_type == LESS) {
        return (23);
    } else if (token.token_type == GTEQ) {
        return (19);
    } else if (token.token_type == LTEQ) {
        return (21);
    } else if (token.token_type == EQUAL) {
        return (26);
    } else if (token.token_type == NOTEQUAL) {
        return (22);
    } else {
        syntax_error();
        return (-1);
    }
}

int Parser::parse_primary() {
    token = input.GetToken();
    if (token.token_type == ID) {
        return (searchList(token.lexeme));
    } else if (token.token_type == NUM) {
        return (1);
    } else if (token.token_type == REALNUM) {
        return (2);
    } else if (token.token_type == TRUE) {
        return (3);
    } else if (token.token_type == FALSE) {
        return (3);
    } else {
        syntax_error();
        return (0);
    }
}


bool isExpress(int c) {
    if (c != 15 && c != 16 && c != 17 && c != 18 && c != 19 && c != 20 && c != 21 && c != 22 && c != 23 && c != 26) {
        return true;
    } else {
        return false;
    }
}

int Parser::parse_expression() {
    //check for C2 error here
    int var;
    token = input.GetToken();
    if (token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TRUE ||
        token.token_type == FALSE) {
        input.UngetToken(token);
        var = parse_primary();
    } else if (token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT ||
               token.token_type == DIV || token.token_type == GREATER || token.token_type == LESS ||
               token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL ||
               token.token_type == NOTEQUAL) {
        input.UngetToken(token);
        var = parse_binary_operator();
        // std::cout << "[dbg] var ="<< var << '\n';
        int lExpr = parse_expression();
        // std::cout << "[dbg] lExpr ="<< lExpr << '\n';
        int rExpr = parse_expression();
        // std::cout << "[dbg] rExpr ="<< rExpr << '\n';
        if ((lExpr != rExpr) || isExpress(var)) {
            if (var == 15 || var == 16 || var == 17 || var == 18) {
                if (lExpr <= 2 && rExpr > 3) {
                    updateTypes(rExpr, lExpr);
                    rExpr = lExpr;
                    // std::cout << "[dbg] updated rExpr loop1 lExpr" <<lExpr<<"rExpr="<<rExpr <<'\n';
                } else if (lExpr > 3 && rExpr <= 2) {
                    updateTypes(rExpr, lExpr);
                    lExpr = rExpr;
                    // std::cout << "[dbg] updated lExpr loop2 lExpr" <<lExpr<<"rExpr="<<rExpr <<'\n';
                } else if (lExpr > 3 && rExpr > 3) {
                    updateTypes(rExpr, lExpr);
                    rExpr = lExpr;
                    // std::cout << "[dbg] updated rExpr loop3 lExpr" <<lExpr<<"rExpr="<<rExpr <<'\n';
                } else {
                    cout << "TYPE MISMATCH " << token.line_no << " C2" << endl;
                    throw type_mismatch_exception("C2", token.line_no);
                }
            } else if (var == 19 || var == 20 || var == 21 || var == 22 || var == 23 || var == 26) {
                if (rExpr > 3 && lExpr > 3) {
                    updateTypes(rExpr, lExpr);
                    rExpr = lExpr;
                    return (3);
                } else {
                    cout << "TYPE MISMATCH " << token.line_no << " C2" << endl;
                    throw type_mismatch_exception("C2", token.line_no);
                }
            } else {
                cout << "TYPE MISMATCH " << token.line_no << " C2" << endl;
                throw type_mismatch_exception("C2", token.line_no);
            }
        }
        if (var == 19 || var == 20 || var == 21 || var == 23 || var == 26 || var == 22) {
            var = 3;
        } else {
            var = rExpr;
        }
    } else if (token.token_type == NOT) {
        input.UngetToken(token);
        var = parse_unary_operator();
        var = parse_expression();
        if (var != 3) {
            cout << "TYPE MISMATCH " << token.line_no << " C3" << endl;
            throw type_mismatch_exception("C3", token.line_no);
        }
    } else {
        syntax_error();
        return (0);
    }
    // std::cout << "[dbg] var = "<<var << '\n';
    return var;
}

void compareLine(int line_No, int token_Type) {
    sTable *temp = symbolTable;
    while (temp->next != NULL) {
        if (temp->item->lineNo == line_No) {
            temp->item->type = token_Type;
        }
        temp = temp->next;
    }
    if (temp->item->lineNo == line_No) {
        temp->item->type = token_Type;
    }
}

void updateTypes(int currentType, int newType) {
    sTable *temp = symbolTable;

    while (temp->next != NULL) {
        if (temp->item->type == currentType) {
            temp->item->type = newType;
        }
        temp = temp->next;
    }
    if (temp->item->type == currentType) {
        temp->item->type = newType;
    }
}

int Parser::parse_assignment_stmt() {
    int var;
    string name;
    int LHS;
    int RHS;
    token = input.GetToken();
    if (token.token_type == ID) {
        LHS = searchList(token.lexeme);
        // std::cout << "[dbg] LHS = "<<LHS << '\n';
        token = input.GetToken();
        if (token.token_type == EQUAL) {
            token = input.GetToken();
            if (token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM ||
                token.token_type == TRUE || token.token_type == FALSE || token.token_type == PLUS ||
                token.token_type == MINUS || token.token_type == MULT || token.token_type == DIV ||
                token.token_type == LESS || token.token_type == GREATER || token.token_type == GTEQ ||
                token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL ||
                token.token_type == NOT) {
                // std::cout << "[dbg] assignment_stmt" << '\n';
                input.UngetToken(token);
                RHS = parse_expression();
                // std::cout << "[dbg] RHS ="<<RHS << '\n';

                if (LHS <= 3) {
                    if (LHS == RHS) {

                    } else {
                        if (LHS <= 3) {
                            cout << "TYPE MISMATCH " << token.line_no << " C1" << endl;
                            throw type_mismatch_exception("C1", token.line_no);
                        } else {
                            updateTypes(RHS, LHS);
                            RHS = LHS;
                        }
                    }
                } else {
                    updateTypes(LHS, RHS);
                    LHS = RHS;
                }
                token = input.GetToken();
                if (token.token_type == SEMICOLON) {
                    //cout << "[dbg]  Rule parsed: assignment_stmt -> ID EQUAL expression SEMICOLON"<<endl;

                } else {
                    cout << "\n Syntax Error " << token.token_type << " \n";
                }
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_case() {

    int var;
    token = input.GetToken();
    if (token.token_type == CASE) {
        token = input.GetToken();
        if (token.token_type == NUM) {
            token = input.GetToken();
            if (token.token_type == COLON) {
                var = parse_body();
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return 0;
}

int Parser::parse_case_list() {
    int var;
    token = input.GetToken();
    if (token.token_type == CASE) {
        input.UngetToken(token);
        var = parse_case();
        token = input.GetToken();
        if (token.token_type == CASE) {
            input.UngetToken(token);
            var = parse_case_list();
        } else if (token.token_type == RBRACE) {
            input.UngetToken(token);
        }
    }
    return (0);
}

int Parser::parse_switch_stmt() {
    int var;
    token = input.GetToken();
    if (token.token_type == SWITCH) {
        token = input.GetToken();
        if (token.token_type == LPAREN) {
            var = parse_expression();
            if (var <= 3 && var != 1) {
                cout << "TYPE MISMATCH " << token.line_no << " C5" << endl;
                throw type_mismatch_exception("C5", token.line_no);
            }
            token = input.GetToken();
            if (token.token_type == RPAREN) {
                token = input.GetToken();
                if (token.token_type == LBRACE) {
                    var = parse_case_list();
                    token = input.GetToken();
                    if (token.token_type == RBRACE) {
                        //successfully
                    } else {
                        syntax_error();
                    }
                } else {
                    syntax_error();
                }
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_while_stmt() {
    int var;

    token = input.GetToken();
    if (token.token_type == WHILE) {
        token = input.GetToken();
        if (token.token_type == LPAREN) {
            // std::cout << "[dbg] into while" << '\n';
            var = parse_expression();
            // std::cout << "[dbg] var in while ="<<var << '\n';
            if (var == 4 || var == 5) {
                var = 3;
            }
            if (var != 3) {
                cout << "TYPE MISMATCH " << token.line_no << " C4" << endl;
                throw type_mismatch_exception("C4", token.line_no);
            }
            token = input.GetToken();
            if (token.token_type == RPAREN) {
                var = parse_body();
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_if_stmt() {
    int var;
    token = input.GetToken();
    if (token.token_type == IF) {
        token = input.GetToken();
        if (token.token_type == LPAREN) {
            var = parse_expression();
            if (var != 3) {
                cout << "TYPE MISMATCH " << token.line_no << " C4" << endl;
                throw type_mismatch_exception("C4", token.line_no);
            }
            token = input.GetToken();
            if (token.token_type == RPAREN) {
                var = parse_body();

            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_stmt() {
    int var;
    token = input.GetToken();
    if (token.token_type == ID) {
        input.UngetToken(token);
        var = parse_assignment_stmt();

    } else if (token.token_type == IF) {
        input.UngetToken(token);
        var = parse_if_stmt();
    } else if (token.token_type == WHILE) {
        input.UngetToken(token);
        var = parse_while_stmt();
    } else if (token.token_type == SWITCH) {
        input.UngetToken(token);
        var = parse_switch_stmt();
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_stmt_list() {
    token = input.GetToken();
    int var;
    if (token.token_type == ID || token.token_type == IF || token.token_type == WHILE || token.token_type == SWITCH) {
        input.UngetToken(token);
        var = parse_stmt();
        token = input.GetToken();
        if (token.token_type == ID || token.token_type == IF || token.token_type == WHILE ||
            token.token_type == SWITCH) {
            input.UngetToken(token);
            var = parse_stmt_list();

        } else if (token.token_type == RBRACE) {
            input.UngetToken(token);
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_body() {
    token = input.GetToken();
    int var;
    if (token.token_type == LBRACE) {
        var = parse_stmt_list();
        token = input.GetToken();
        if (token.token_type == RBRACE) {
            return (0);
        } else {
            syntax_error();
            return (0);
        }
    } else if (token.token_type == END_OF_FILE) {
        input.UngetToken(token);
        return (0);
    } else {
        syntax_error();
        return (0);
    }
}

int Parser::parse_typename() {
    token = input.GetToken();
    if (token.token_type == INT || token.token_type == REAL || token.token_type == BOOL) {
        compareLine(token.line_no, token.token_type);
    } else {
        syntax_error();
    }
    return (token.token_type);
}

int Parser::parse_var_decl() {
    int var;
//    cout << "in_var_decl" << endl;
    token = input.GetToken();
    if (token.token_type == ID) {
        //
        input.UngetToken(token);
        var = parse_var_list();
        token = input.GetToken();
        if (token.token_type == COLON) {
            var = parse_typename();
            //addList(lexeme, token.line_no,var);
            // std::cout << "var = " << var << '\n';
            token = input.GetToken();
            if (token.token_type == SEMICOLON) {
                //Parsed successfully
//                cout << "\n Rule parsed: var_decl -> var_list COLON type_name SEMICOLON";
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }
    return (0);
}

int Parser::parse_var_decl_list() {
    int var;
    token = input.GetToken();
    while (token.token_type == ID) {
        input.UngetToken(token);
        var = parse_var_decl();
        token = input.GetToken();
        if (token.token_type != ID) {
            //Parsed successfully
//            cout << "\n Rule Parsed: var_decl_list -> var_decl \n";

        } else {
            //Parsed successfully
//            cout << "\n Rule Parsed: var_decl_list -> var_decl var_decl_list \n";

        }
    }
    input.UngetToken(token);
//    cout << "back in decl list" << endl;
    return (0);
}

int Parser::parse_global_vars() {
    token = input.GetToken();
    int var;
    if (token.token_type == ID) {
        input.UngetToken(token);
//        cout << "\n Rule parsed: globalVars -> var_decl_list \n";
        var = parse_var_decl_list();
    } else {
        syntax_error();
    }
//    cout << "back in glob var" << endl;

    return (0);
}
void printList() {
    sTable *temp = symbolTable;
    int temp1;

    while (temp->next != NULL) {
        if (temp->item->type > 3 && temp->item->printed == 0) {
            temp1 = temp->item->type;
            output += temp->item->name;
            temp->item->printed = 1;
            while (temp->next != NULL) {
                temp = temp->next;
                if (temp->item->type == temp1) {
                    output += ", " + temp->item->name;
                    temp->item->printed = 1;
                } else {

                }
            }
            output += ": ? #";
            cout << output << endl;
            temp->item->printed = 1;
            output = "";
            temp = symbolTable;
        } else if (temp->item->type < 4 && temp->item->printed == 0) {
            string lCase = keyword[(temp->item->type) - 1];
            int temp1 = temp->item->type;
            output = temp->item->name + ": " + lCase + " #";
            cout << output << endl;
            output = "";
            temp->item->printed = 1;

            while (temp->next != NULL && temp->next->item->type == temp1) {
                temp = temp->next;
                string lCase2 = keyword[(temp->item->type) - 1];
                output = temp->item->name + ": " + lCase2 + " #";
                cout << output << endl;
                temp->item->printed = 1;
                output = "";
            }
        } else {
            temp = temp->next;
        }
    }
    if (temp->item->type <= 3 && temp->item->printed == 0) {
        string lCase3 = keyword[(temp->item->type) - 1];
        output += temp->item->name + ": " + lCase3 + " #";
        cout << output << endl;
        output = "";
    } else if (temp->item->type > 3 && temp->item->printed == 0) {
        output += temp->item->name + ":" + " ? " + "#";
        cout << output << endl;
        output = "";
    } else {

    }
}
int Parser::parse_program() {
    token = input.GetToken();
    int var;
    while (token.token_type != END_OF_FILE) {
        if (token.token_type == ID) {
            input.UngetToken(token);
//            cout << "\n Rule parsed: program -> global_vars scope \n";
            var = parse_global_vars();
//            cout << "back in parse p1" << endl;
            var = parse_body();
//            cout << "back in parse p2" << endl;
        } else if (token.token_type == LBRACE) {
            input.UngetToken(token);
//            cout << "\n Rule parsed: global_vars -> epsilon \n";
            var = parse_body();
        } else if (token.token_type == END_OF_FILE) {
//            cout << "ending2" << endl;
            return (0);
        } else {
            syntax_error();
            return (0);
        }
        printList();
        break;
        token = input.GetToken();
        printList();
//        cout << token.lexeme << endl;
    }
//    cout << "ending" << endl;
    return 0;
}


void Parser::syntax_error() {
    cout << "\n Syntax Error\n";
}




const char* trim_list = " \t\n\r";

inline std::string& rtrim(std::string& s, const char* t = trim_list)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline std::string& ltrim(std::string& s, const char* t = trim_list)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline std::string& trim(std::string& s, const char* t = trim_list)
{
    return ltrim(rtrim(s, t), t);
}

std::string load(const std::string& path) {
    ostringstream ss;
    std::ifstream file(path.c_str());
    ss << file.rdbuf();
    string content = ss.str();
    return trim(content);
}

int main(int argc, char *argv[]) {
    bool has_input = false;
    bool has_output = false;
    bool has_expected = false;
    string test_file = "";
    string test_result = "";
    string test_expected = "";
    streambuf *cinbuf = cin.rdbuf();
    streambuf *coutbuf = cout.rdbuf();

    Parser parse;
    int i = parse.parse_program();
//    cout << "\n End of Program \n";

//    if (argc == 7) {
//        has_input = (string(argv[1]) == string("-i"));
//        has_output = (strcasecmp(argv[3], "-o") == 0);
//        has_expected = (strcasecmp(argv[5], "-e") == 0);
//        test_file = argv[2];
//        test_result = argv[4];
//        test_expected = argv[6];
//    } else if (argc == 5) {
//        has_input = (string(argv[1]) ==  string("-i"));
//        has_output = strcasecmp(argv[3], "-o") == 0;
//        test_file = argv[2];
//        test_result = argv[4];
//    } else if (argc == 3) {
//        has_input = (string(argv[1]) ==  string("-i"));
//        test_file = argv[2];
//    }
//
//    if (!has_input) {
//        cout << "usage: " << argv[0] << " -i <test_file> [-o <test_result_file> -e <expected_file>]" << endl;
//        return 0;
//    }
//
//    ifstream in(test_file.c_str());
//    ofstream out(test_result.c_str());
//
//    if (has_input) {
//        cin.rdbuf(in.rdbuf());
//    }
//
//    if (has_output) {
//        cout.rdbuf(out.rdbuf());
//    }
//
//    try {
//        Parser hmParser;
//        hmParser.parse_program();
//        printList();
//    } catch (type_mismatch_exception& e) {
//        ;
//    }
//
//    cin.rdbuf(cinbuf);
//    cout.rdbuf(coutbuf);
//
//    if (has_expected) {
//        const char* ws = " \t\n\r\f\v";
//        string cmp1 = load(test_result);
//        string cmp2 = load(test_expected);
//        if (cmp1 == cmp2) {
//            cout << "result match" << endl;
//        } else {
//            cout << "test_result: \n" << cmp1 << endl;
//            cout << "test_expected: \n" << cmp2 << endl;
//            cout << "result mismatch" << endl;
//        }
//    }
    return 0;
}
