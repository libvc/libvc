/*
 * libvc - vCard library
 * Copyright (C) 2003  Andrew Hsu
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: vc_scan.l,v 1.3 2003/06/04 10:53:59 ahsu Exp $
 */

%{
#define YYSTYPE char*
#include "vc_parse.h"

/****************************************************
  to force flex to scan only one character at a time
 ****************************************************/
#define YY_INPUT(buf,result,max_size) \
    { \
    int c = getc(yyin); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }

/* TODO: clean up the token definitions to match the rfc */
%}

ALPHA           [\x41-\x5A\x61-\x7A]
CHAR            [\x01-\x7F]
CR              \x0D
LF              \x0A
CRLF            {CR}{LF}
DIGIT           [\x30-\x39]
DQUOTE          \x22
HTAB            \x09
SP              \x20
VCHAR           [\x21-\x7E]
WSP             {SP}|{HTAB}
NON-ASCII       [\x80-\xFF]
SAFE-CHAR       {WSP}|\x21|[\x23-\x2B]|[\x2D-\x39]|[\x3C-\x7E]|{NON-ASCII}
VALUE-CHAR      {WSP}|{VCHAR}|{NON-ASCII}
NAME-CHAR       [\x21-\x2B\x2D\x2F-\x39\x3C\x3E-\x5A\x5C\x5E-\x7E]

%option noyywrap
%x SC_VALUE SC_PARAM SC_PARAM_VALUE

%%

"BEGIN:VCARD"             { yylval = NULL; return TOK_BEGIN_VCARD; }
"END:VCARD"               { yylval = NULL; return TOK_END_VCARD; }
{LF}                      { yylval = NULL; return yytext[0]; }
"."                       { yylval = NULL; return yytext[0]; }
({ALPHA}|{DIGIT}|-)+/"."  { yylval = yytext; return TOK_GROUP; }
{NAME-CHAR}+              { yylval = yytext; return TOK_NAME; }
";"                       { yylval = NULL; BEGIN(SC_PARAM); return yytext[0]; }
":"                       { yylval = NULL; BEGIN(SC_VALUE); return yytext[0]; }

<SC_VALUE>
{
({VALUE-CHAR}|({CRLF}|{LF}){SP})*  { yylval = yytext; return TOK_VALUE; }
{LF}                               { yylval = NULL; BEGIN(INITIAL); return yytext[0]; }
}

<SC_PARAM>
{
({ALPHA}|{DIGIT}|-)+      { yylval = yytext; return TOK_PARAM_NAME; }
"="                       { yylval = NULL; BEGIN(SC_PARAM_VALUE);
                            return yytext[0]; }
";"                       { yylval = NULL; BEGIN(SC_PARAM); return yytext[0]; }
":"                       { yylval = NULL; BEGIN(SC_VALUE); return yytext[0]; }
}

<SC_PARAM_VALUE>
{
{SAFE-CHAR}*              { yylval = yytext; return TOK_PARAM_VALUE; }
","                       { yylval = NULL; return yytext[0]; }
";"                       { yylval = NULL; BEGIN(SC_PARAM); return yytext[0]; }
":"                       { yylval = NULL; BEGIN(SC_VALUE); return yytext[0]; }
}

%%

