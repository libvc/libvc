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
 * $Id: vc_parse.y,v 1.2 2003/05/15 03:47:18 ahsu Rel $
 */

%{

#include "vc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE char*

extern FILE *yyin;

extern int yylex ();
void yyerror (char *s);

vc_component *current_vcard = NULL;
vc_component *current_vc = NULL;
char *current_vc_param_name = NULL;

%}

/*-----------------------
   create a y.tab.h file
  -----------------------*/
%defines

%start vcard

%token TOK_BEGIN_VCARD
%token TOK_END_VCARD
%token TOK_GROUP
%token TOK_NAME
%token TOK_PARAM_NAME
%token TOK_PARAM_VALUE
%token TOK_VALUE

%%

vcard
        : begin_line contentlines end_line { YYACCEPT; }
        | error '\n' { yyerrok; }
        ;

begin_line
        : filler first_line
        | first_line
        ;

filler
        : filler '\n'
        | '\n'
        ;

first_line
        : TOK_BEGIN_VCARD '\n' { current_vcard = vc_new (); }
        | TOK_GROUP '.' TOK_BEGIN_VCARD '\n' {
            current_vcard = vc_new ();
            vc_set_group (current_vcard, $1); }
        ;

end_line
        : TOK_END_VCARD '\n'
        | TOK_GROUP '.' TOK_END_VCARD '\n'
        ;

contentlines
        : contentlines group_contentline
        | group_contentline
        ;

group_contentline
        : TOK_GROUP '.' contentline { vc_set_group (current_vc, $1); }
        | contentline
        ;

contentline
        : name params ':' value '\n'
        | name ':' value '\n' 
        ;

name
        : TOK_NAME { current_vc = vc_append_with_name (current_vcard, $1); }
        ;

params
        : ';' param
        | params ';' param
        ;

param
        : param_name '=' param_values
        | param_name {
            vc_component_param *tmp_vc_param = NULL;
            tmp_vc_param = vc_param_new ();
            vc_param_set_name (tmp_vc_param, "TYPE");
            vc_param_set_value (tmp_vc_param, current_vc_param_name);
            vc_add_param (current_vc, tmp_vc_param); }
        ;

param_name
        : TOK_PARAM_NAME {
            if (NULL != current_vc_param_name)
              {
                free (current_vc_param_name);
                current_vc_param_name = NULL;
              }
            current_vc_param_name = strdup ($1); }
        ;

param_values
        : param_value
        | param_values ',' param_value
        ;

param_value
        : TOK_PARAM_VALUE {
            vc_component_param *tmp_vc_param = NULL;

            tmp_vc_param = vc_param_new ();
            vc_param_set_name (tmp_vc_param, current_vc_param_name);
            vc_param_set_value (tmp_vc_param, $1);
            vc_add_param (current_vc, tmp_vc_param); }
        ;

value
        : TOK_VALUE { vc_set_value (current_vc, $1); }
        ;

%%

void
yyerror (char *s)
{
}

vc_component *
parse_vcard_file (FILE * fp)
{
  vc_component *vc = NULL;

  yyin = fp;

  if (0 == yyparse ())
    {
      vc = current_vcard;
    }

  return vc;
}
