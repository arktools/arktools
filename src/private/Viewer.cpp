/*
 * Viewer.cpp
 * Copyright (C) James Goppert 2010 <jgoppert@users.sourceforge.net>
 *
 * Viewer.cpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Viewer.cpp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Viewer.hpp"
#include <boost/bind.hpp>
#include <osgGA/TrackballManipulator>

// Static linking of OSG needs special macros
#ifdef OSG_LIBRARY_STATIC
#include <osgDB/Registry>

#if defined(__APPLE__) 
    USE_GRAPICSWINDOW_IMPLEMENTATION(Cocoa) 
#else 
    USE_GRAPHICSWINDOW() 
#endif 

USE_OSGPLUGIN(rgb);
USE_OSGPLUGIN(ac);
#endif

Viewer::Viewer() :
    osgViewer::Viewer(), mutex()
{
    using namespace osgViewer;
//    setThreadSafeReferenceCounting(true);
//    setThreadSafeRefUnref(true);
    _runMaxFrameRate = 20;
}

Viewer::~Viewer()
{
}

void Viewer::frame(double simulationTime)
{
    boost::mutex::scoped_lock lock(mutex);
    osgViewer::Viewer::frame(simulationTime);
}

ViewerThread::ViewerThread() {
}

ViewerThread::~ViewerThread() {
    cancel();
    while (isRunning()) {
        OpenThreads::Thread::YieldCurrentThread();
    }
}

int ViewerThread::cancel() {
    if (_viewer) _viewer->setDone(true);
    return 0;
}

void ViewerThread::run() {
    if (!_viewer) _viewer = new Viewer;
    if (_viewer) _viewer->run();
}

// vim:ts=4:sw=4
