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
#include <osgViewer/Viewer>

#include "visualization.hpp"
#include "private/osgUtils.hpp"

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



class VisCar::Impl : public osgViewer::Viewer {
public:
    Impl(std::string dataPath) :
        _car(NULL)
    {
        _car = new Car(dataPath+"/models/rcTruck.ac");
        std::string texturePath = dataPath+"/images/lz.rgb";
        osg::Group * root = new Frame(1,"N","E","D");
        root->addChild(new Terrain(texturePath,osg::Vec3(10,10,0)));
        if (_car) root->addChild(_car);
        setCameraManipulator(new osgGA::TrackballManipulator);
        getCameraManipulator()->setHomePosition(
                osg::Vec3(-3,3,-3),
                osg::Vec3(0,0,0),
                osg::Vec3(0,0,-1));
        setSceneData(root);
        setUpViewInWindow(0,0,400,400);
    }
    osg::ref_ptr<Car> _car;
};

VisCar::VisCar(std::string dataPath) :
    _impl(new Impl(dataPath)) {
};

VisCar::~VisCar() {
    if (_impl) delete _impl;
}

void VisCar::setEuler(double roll, double pitch, double yaw) {
    _impl->_car->setEuler(roll, pitch, yaw);
};

void VisCar::setPosition(double x, double y, double z) {
    _impl->_car->setPositionScalars(x, y, z);
};

void VisCar::setU(double throttle, double steering) {
    _impl->_car->setU(throttle, steering);
};

void VisCar::frame() {
    if (_impl) _impl->frame();
}

// vim:ts=4:sw=4
