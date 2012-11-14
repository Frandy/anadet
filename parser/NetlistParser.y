// ref 
// http://blog.csdn.net/yuucyf/article/details/7439860
// http://glacjay.is-a-geek.org/blog/archives/42

/*

%code requires {circuit.h}  //放 Bison 定义要用到的 C/C++ 代码
%code provides {

    typedef yy::Parser::semantic_type YYSTYPE;
    typedef yy::Parser::location_type YYLTYPE;

} // 放需要 Bison 定义的 C/C++ 代码, 两部分的代码都会原样输出到生成的头文件中

*/


// %skeleton "lalr1.cc" /* -*- C++ -*- */
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
       int          ival;
       std::string *sval;
     };

%token        END      0 "end of file"
%token <sval> IDENTIFIER "identifier"

%destructor { delete $$; } "identifier"


%%
     %start unit;
     unit: assignments exp  { driver.result = $2; };
     
     assignments:
       /* Nothing.  */        {}
     | assignments assignment {};
     
     assignment:
          "identifier" ":=" exp
            { driver.variables[*$1] = $3; delete $1; };
     
     %left '+' '-';
     %left '*' '/';
     exp: exp '+' exp   { $$ = $1 + $3; }
        | exp '-' exp   { $$ = $1 - $3; }
        | exp '*' exp   { $$ = $1 * $3; }
        | exp '/' exp   { $$ = $1 / $3; }
        | "identifier"  { $$ = driver.variables[*$1]; delete $1; }
        | "number"      { $$ = $1; };


%%
     
void yy::NetlistParser::error (const yy::NetlistParser::location_type& l,
                               const std::string& m)
     {
       driver.error (l, m);
     }     
