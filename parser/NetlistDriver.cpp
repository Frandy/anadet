/*
 * NetlistDriver.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: chjd
 */

#include <iostream>

#include "NetlistDriver.hh"
#include "NetlistParser.hh"

NetlistDriver::NetlistDriver() :
		trace_scanning(false), trace_parsing(false)
{
}

NetlistDriver::~NetlistDriver()
{
}

int NetlistDriver::parse(const std::string &f)
{
	file = f;
	scan_begin();
	yy::NetlistParser parser(*this);
	parser.set_debug_level(trace_parsing);
	int res = parser.parse();
	scan_end();
	return res;
}

void NetlistDriver::error(const yy::location& l, const std::string& m)
{
	std::cerr << l << ": " << m << std::endl;
}

void NetlistDriver::error(const std::string& m)
{
	std::cerr << m << std::endl;
}
