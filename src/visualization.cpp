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

class VisCar::Impl : public ViewerThread {
public:
    Impl(std::string dataPath) :
        _dataPath(dataPath),
        _car(),
        _viewer()
    {
    }
    virtual void run() {
        _viewer = new Viewer;
        _car = new Car(_dataPath+"/models/rcTruck.ac");
        std::string texturePath = _dataPath+"/images/lz.rgb";
        osg::Group * root = new Frame(1,"N","E","D");
        root->addChild(new Terrain(texturePath,osg::Vec3(10,10,0)));
        if (_car) root->addChild(_car);
        _viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        _viewer->getCameraManipulator()->setHomePosition(
                osg::Vec3(-3,3,-3),
                osg::Vec3(0,0,0),
                osg::Vec3(0,0,-1));
        _viewer->setSceneData(root);
        _viewer->setUpViewInWindow(0,0,400,400);
        _viewer->run();
    }
    virtual ~Impl() {}
    std::string _dataPath;
    osg::ref_ptr<Car> _car;
    osg::ref_ptr<Viewer> _viewer;
};

VisCar::VisCar(std::string dataPath) :
    _impl(new Impl(dataPath)) {
};

VisCar::~VisCar() {
    _impl->cancel();
    if (_impl) delete _impl;
}

void VisCar::setEuler(double roll, double pitch, double yaw) {
    if (!(_impl->_viewer && _impl->_car)) return;
    boost::mutex::scoped_lock lock(_impl->_viewer->mutex);
    _impl->_car->setEuler(roll, pitch, yaw);
};

void VisCar::setPosition(double x, double y, double z) {
    if (!(_impl->_viewer && _impl->_car)) return;
    boost::mutex::scoped_lock lock(_impl->_viewer->mutex);
    _impl->_car->setPositionScalars(x, y, z);
};

void VisCar::setU(double throttle, double steering) {
    if (!(_impl->_viewer && _impl->_car)) return;
    boost::mutex::scoped_lock lock(_impl->_viewer->mutex);
    _impl->_car->setU(throttle, steering);
};

void VisCar::run() {
    if (_impl) _impl->startThread();
}



// vim:ts=4:sw=4
