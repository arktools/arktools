/*
 * Viewer.hpp
 * Copyright (C) James Goppert 2010 <jgoppert@users.sourceforge.net>
 *
 * Viewer.hpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Viewer.hpp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Viewer_HPP
#define Viewer_HPP

#include <osgViewer/Viewer>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/scoped_ptr.hpp>
#include <osgDB/ReadFile>

#include "osgUtils.hpp"

/**
 * The purpose of this class is to create a viewer for simulation purposes.
 */
class Viewer : public osgViewer::Viewer
{
public:
    /**
     * Constructor
     */
    Viewer();
    virtual ~Viewer();
    void frame(double simulationTime);
    boost::mutex mutex; // mutex lock to protect data for multi-threading
};

class ViewerThread : public OpenThreads::Thread
{
public:
    ViewerThread();
    virtual ~ViewerThread();
    int cancel();
    virtual void run();
    osg::ref_ptr<Viewer> _viewer;
};

#endif

// vim:ts=4:sw=4
