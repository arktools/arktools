/*
 * visualization.hpp
 * Copyright (C) James Goppert 2010 <jgoppert@users.sourceforge.net>
 *
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <string>

class VisCar {
public:
    VisCar(std::string dataPath);
    ~VisCar();
    void setEuler(double roll, double pitch, double yaw);
    void setPosition(double x, double y, double z);
    void setU(double throttle, double steering);
private:
    class Impl;
    Impl * _impl;
    // disable copy ctors
    VisCar(const VisCar & other);
    VisCar & operator=(const VisCar & other);
};

#endif

// vim:ts=4:sw=4
