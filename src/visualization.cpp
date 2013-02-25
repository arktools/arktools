/*
 * visualization.cpp
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

#include <osgGA/TrackballManipulator>

#include "visualization.hpp"
#include "private/osgUtils.hpp"
#include "private/Viewer.hpp"

class VisCar::Impl {
public:
    Impl(std::string dataPath) : 
        car(new Car(dataPath+"/models/rcTruck.ac")),
        _viewer(NULL),
        _dataPath(dataPath),
        _thread(new boost::thread(boost::bind(&Impl::run,this))) {
    }
    void run() {
        _viewer = new Viewer;
        std::string texturePath = _dataPath+"/images/lz.rgb";
        osg::Group * root = new Frame(1,"N","E","D");
        root->addChild(new Terrain(texturePath,osg::Vec3(10,10,0)));
        if (car) root->addChild(car);
        _viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        _viewer->getCameraManipulator()->setHomePosition(
                osg::Vec3(-3,3,-3),
                osg::Vec3(0,0,0),
                osg::Vec3(0,0,-1));
        _viewer->setSceneData(root);
        _viewer->setUpViewInWindow(0,0,400,400);
        _viewer->run();
    }
    ~Impl() {
        _viewer->setDone(true);
        if (_thread) _thread->join();
    }
    osg::ref_ptr<Car> car;
    osg::ref_ptr<Viewer> _viewer;
private:
    std::string _dataPath;
    boost::scoped_ptr<boost::thread> _thread; // viewer thread
};

VisCar::VisCar(std::string dataPath) :
    _impl(new Impl(dataPath)) {
};

VisCar::~VisCar() {
    if (_impl) delete _impl;
}

void VisCar::setEuler(double roll, double pitch, double yaw) {
    if (!(_impl->_viewer && _impl->car)) return;
    _impl->_viewer->lock();
    _impl->car->setEuler(roll, pitch, yaw);
    _impl->_viewer->unlock();
};

void VisCar::setPosition(double x, double y, double z) {
    if (!(_impl->_viewer && _impl->car)) return;
    _impl->_viewer->lock();
    _impl->car->setPositionScalars(x, y, z);
    _impl->_viewer->unlock();
};

void VisCar::setU(double throttle, double steering) {
    if (!(_impl->_viewer && _impl->car)) return;
    _impl->_viewer->lock();
    _impl->car->setU(throttle, steering);
    _impl->_viewer->unlock();
};



// vim:ts=4:sw=4
