/*
// ref 
// http://blog.csdn.net/yuucyf/article/details/7439860
// http://glacjay.is-a-geek.org/blog/archives/42
*/
/*

%code requires {circuit.h}  //放 Bison 定义要用到的 C/C++ 代码
%code provides {

    typedef yy::Parser::semantic_type YYSTYPE;
    typedef yy::Parser::location_type YYLTYPE;

} // 放需要 Bison 定义的 C/C++ 代码, 两部分的代码都会原样输出到生成的头文件中

*/


%skeleton "lalr1.cc" /* -*- C++ -*- */
%pure_parser
%language "c++"
%require "2.6.4"

%defines
%define parser_class_name "NetlistParser"
// The parsing context.
%parse-param { NetlistDriver& driver }
%lex-param   { NetlistDriver& driver }

%locations
%initial-action
{
	// Initialize the initial location.
	@$.begin.filename = @$.end.filename = &driver.file;
};

%debug
%error-verbose


%code {
# include "NetlistDriver.hh"
}

// Symbols.

%union
{
	std::string* sval;
}

/*	two kinds of token, 
	one is word token, if match, no need to save the text
	another is text, save text, no matter text or digit 
*/

%token			END      0 	"end of file"
%token <sval>  	ID 			"identifier"
%destructor { delete $$; } <sval>  // using type to destruct token with this kind ok type
/*
yytext 只能在flex里面使用，不能在bison里面使用，每次需要传递值时，需要将yytext复制到token里面。
对于不需要传递值的token，只需要标识token名称，对应到token的ID 就可以了。
*/


%%
%start netlist;

netlist:
	stats NETLISTEND
	; 

stats:
	/* nothing */ 
	| LINEEND
	| ckt_stat
	| cmd_stat
	| ckt_stat stats
	| cmd_stat stats
	;

ckt_stat:
	ckt_elem LINEEND
	;

cmd_stat:
	cmd_elem LINEEND
	;

ckt_elem:
	  r_elem
	| v_elem
	| x_elem
	;

cmd_elem:
	  cmd_title
	| cmd_op
	| cmd_dc
	| cmd_tran
	| cmd_ac
	| cmd_print
	| cmd_plot
	| cmd_param
	| cmd_subckt_begin
	| cmd_subckt_ends
	;


node:
	  TEXT
	| INTEGER 
	;

value:
	  INTEGER
	| FLOAT
	;

param_expr:
	LQUOTE expr RQUOTE
	;

expr:
	  term "+" term
	| term "-" term
	;

term:
	  factor "*" factor
	| factor "/" factor
	;

factor:
	  value
	| TEXT
	| func
	;

param:
	  value
	| INFTY
	| param_expr
	;

%%
     
void yy::NetlistParser::error (const yy::NetlistParser::location_type& l,
                               const std::string& m)
{
	driver.error (l, m);
}    

