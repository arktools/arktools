/*
 * utilities.hpp
 * Copyright (C) James Goppert 2010 <james.goppert@gmail.com>
 *
 * utilities.hpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * utilities.hpp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ARKTOOLS_UTILITIES_HPP
#define _ARKTOOLS_UTILITIES_HPP

void getIpars(int nStrings, int nInts, int * ipar, char *** stringArray, int ** intArray);

int evtPortNumToFlag(int portNum);

void sleepMillis(int millis);

extern "C"
{
	
void cMatrix2FortranVector(double ** cMatrix, const int & rows, const int & cols, double * fMatrix);

void allocateCMatrix(double ** cMatrix, const int & rows, const int & cols);

void freeCMatrix(double ** matrix, const int & rows, const int & cols);

}

#endif // _ARKTOOLS_UTILITIES_HPP

// vim:ts=4:sw=4
