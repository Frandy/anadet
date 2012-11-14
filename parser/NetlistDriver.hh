/*
 * NetlistDriver.h
 *
 *  Created on: Nov 14, 2012
 *      Author: chjd
 */
#ifndef NETLISTDRIVER_H_
#define NETLISTDRIVER_H_

#include <string>

# include "NetlistParser.hh"


// Tell Flex the lexer's prototype ...
# define YY_DECL                                        \
       yy::NetlistParser::token_type                         \
       yylex (yy::NetlistParser::semantic_type* yylval,      \
              yy::NetlistParser::location_type* yylloc,      \
              NetlistDriver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

class NetlistDriver
{
public:
	NetlistDriver();
	virtual ~NetlistDriver();

	int result;
	// Handling the scanner.
	void scan_begin();
	void scan_end();
	bool trace_scanning;
	// Run the parser.  Return 0 on success.
	int parse(const std::string& f);
	std::string file;
	bool trace_parsing;
	// Error handling.
	void error(const yy::location& l, const std::string& m);
	void error(const std::string& m);
};

#endif /* NETLISTDRIVER_H_ */
