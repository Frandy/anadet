/*
 * stdafx.hpp
 *
 *  Created on: Nov 9, 2012
 *      Author: chjd
 */

#ifndef STDAFX_HPP_
#define STDAFX_HPP_

#include <string>
using std::string;

#include <cstdlib>

#include <cctype>
using std::isdigit;

#include <cstddef>
// use nullptr


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <stdio.h>
// using C-style file operation

#include <vector>
using std::vector;

#include <array>
using std::array;

#include <list>
using std::list;

#include <unordered_map>
using std::unordered_map;

#include <utility>
using std::pair;
using std::make_pair;

#include <functional>
using std::function;

#include <complex>
using std::complex;
typedef complex<double> Cplx;

#include <cmath>
using std::sin;

#include <cassert>

#include <stdarg.h>
// to use variable length param

#endif /* STDAFX_HPP_ */
