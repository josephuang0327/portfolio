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

string reserved[] = { "END_OF_FILE",
    "IF", "WHILE", "DO", "THEN", "PRINT",
    "PLUS", "MINUS", "DIV", "MULT",
    "EQUAL", "COLON", "COMMA", "SEMICOLON",
    "LBRAC", "RBRAC", "LPAREN", "RPAREN",
    "NOTEQUAL", "GREATER", "LESS", "LTEQ", "GTEQ",
    "DOT", "NUM", "ID", "ERROR", "REALNUM", "BASE08NUM", "BASE16NUM" // TODO: Add labels for new token types here (as string)
};

#define KEYWORDS_COUNT 5
string keyword[] = { "IF", "WHILE", "DO", "THEN", "PRINT" };

void Token::Print()
{
    cout << "{" << this->lexeme << " , "
         << reserved[(int) this->token_type] << " , "
         << this->line_no << "}\n";
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
    char first;
    char second;
    char third;

    int startZero = 0;
    int pos08 = 0;

    input.GetChar(c);
    if (isdigit(c)) 	//if the char is digit || true
    {
        if (c == '0') 	// if char = 0
        {
            tmp.lexeme = "0";
            startZero = 1;
        }

        else //all numbers
        {
            tmp.lexeme = "";
            while (!input.EndOfInput() && isdigit(c))
            {
                tmp.lexeme += c;
                input.GetChar(c);
                if(c == '8' || c == '9')			// if it contains 8 or 9 then could not be base08
                {
                	pos08 = 1;
                }
            }

            if (!input.EndOfInput())
            {
                input.UngetChar(c);
            }
        }

    // TODO: You can check for REALNUM, BASE08NUM and BASE16NUM here!

		input.GetChar(first);
		if(first == 'x')							//check for x
		{
			input.GetChar(second);
			if(second == '0')						// check for 0 for possible 08
			{
				input.GetChar(third);
				if(third == '8' && pos08 == 0)	// if the third char is an 8 and does pos08 is still true
				{
					tmp.lexeme += first;
					tmp.lexeme += second;
					tmp.lexeme += third;
					tmp.token_type = BASE08NUM;
					tmp.line_no = line_no;
					return tmp;

				}

				input.UngetChar(third);			//release third char
				input.UngetChar(second);			//release second char
			}

			else if(second == '1')
			{
				input.GetChar(third);
				if(third == '6')					//if it is a six then matched base16
				{
					tmp.lexeme += first;
					tmp.lexeme += second;
					tmp.lexeme += third;
					tmp.token_type = BASE16NUM;
					tmp.line_no = line_no;
					return tmp;
				}

				input.UngetChar(third);			//release third char
				input.UngetChar(second);			//release second char

			}
			else
			{
				input.UngetChar(second);
			}
			input.UngetChar(first);
		}
		// check for char after '.'
		else if(first == '.')
		{
			string tmpstring = "";
			int hasZero = 1;

			// check for second char
			input.GetChar(second);
			if(isdigit(second))				// if it is a digit then possible realnum
			{
				while(!input.EndOfInput() && isdigit(second))
				{
					if(second != '0')		// if after dot is not zero
					{
						hasZero = 0;
					}
					// if it is zero then looking for next char
					tmpstring += second;
					input.GetChar(second);
				}

				if(!input.EndOfInput())
				{
					input.UngetChar(second);
				}
			}
			else							// if after . is not digit
			{
				input.UngetChar(second);
			}

			// if it contains 0.000~ ... 00 all zeros then release string
			if(hasZero == 1 && startZero == 1)
			{
				input.UngetString(tmpstring);
			}
			else
			{
				input.UngetString(tmpstring);
				input.GetChar(second);
				if(isdigit(second))
				{
					tmp.lexeme += '.';
					while(!input.EndOfInput() && isdigit(second))
					{
						tmp.lexeme += second;		// maybe we can just add tmpstring
						input.GetChar(second);
					}
					if(!input.EndOfInput())
					{
						input.UngetChar(second);
					}
					   tmp.token_type = REALNUM;
					   tmp.line_no = line_no;
					   return tmp;
				}
				else								// if it is not digit anymore
				{
					input.UngetChar(second);
				}
			}
			input.UngetChar(first);
		}
		// If first char start from A ~ F checking for pdigit16 and digit16
		else if(first >= 65 && first <= 70)
		{
			int tracker = 0;
			int tmptrk = 0;
			char arr[512];
			arr[tracker] = first;

			while(isdigit(arr[tracker]) || (arr[tracker] >= 65 && arr[tracker] <= 70))
			{
				tracker++;
				input.GetChar(arr[tracker]);
			}
			tmptrk = tracker;
			first = arr[tracker];

			//check for base16
			if(first == 'x')
			{
				input.GetChar(second);
				if(second == '1')
				{
					input.GetChar(third);
					if(third == '6')
					{
						for(tracker = 0; tracker < tmptrk; tracker++)
						{
							tmp.lexeme = tmp.lexeme + arr[tracker];
						}
						tmp.lexeme += first;
						tmp.lexeme += second;
						tmp.lexeme += third;
						tmp.token_type = BASE16NUM;
						tmp.line_no = line_no;
						return tmp;
					}
					else								//start backtracking
					{
						input.UngetChar(third);
						input.UngetChar(second);
					}
				}
				else
				{
					input.UngetChar(second);
				}
				input.UngetChar(first);
			}
			else
			{
				input.UngetChar(first);
			}


			tracker--;
			while(tracker >= 0)							//release everything in the array
			{
				input.UngetChar(arr[tracker]);
				tracker--;
			}
		}
		else
		{
			input.UngetChar(first);
		}

		tmp.token_type = NUM;
		tmp.line_no = line_no;
		return tmp;
    }

    else	// if nothings matching something is wrong output error
    {
        if (!input.EndOfInput())
        {
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
        case '.':
            tmp.token_type = DOT;
            return tmp;
        case '+':
            tmp.token_type = PLUS;
            return tmp;
        case '-':
            tmp.token_type = MINUS;
            return tmp;
        case '/':
            tmp.token_type = DIV;
            return tmp;
        case '*':
            tmp.token_type = MULT;
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
        case '[':
            tmp.token_type = LBRAC;
            return tmp;
        case ']':
            tmp.token_type = RBRAC;
            return tmp;
        case '(':
            tmp.token_type = LPAREN;
            return tmp;
        case ')':
            tmp.token_type = RPAREN;
            return tmp;
        case '<':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = LTEQ;
            } else if (c == '>') {
                tmp.token_type = NOTEQUAL;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = LESS;
            }
            return tmp;
        case '>':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = GTEQ;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = GREATER;
            }
            return tmp;
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

int main()
{
    LexicalAnalyzer lexer;
    Token token;

    token = lexer.GetToken();
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }
}
