/*
 * MAVLinkParser.hpp
 * Copyright (C) James Goppert 2013 <jgoppert@users.sourceforge.net>
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

#ifndef _ARKTOOLBOX_MAVLINKPARSER_HPP
#define _ARKTOOLBOX_MAVLINKPARSER_HPP

#include <inttypes.h>
#include <string>

class MAVLinkParser {
public:
    MAVLinkParser(const uint8_t sysid, const uint8_t compid,
            const std::string & device, const uint32_t baudRate);
    ~MAVLinkParser();

    void send(double * u, uint64_t timeStamp);
    void receive(double * y);
private:
    class Impl;
    Impl * _impl;
    // disable copy ctors
    MAVLinkParser(const MAVLinkParser & other);
    MAVLinkParser & operator=(const MAVLinkParser & other);
};

#endif // _ARKTOOLBOX_MAVLINKPARSER_HPP

// vim:ts=4:sw=4:expandtab
