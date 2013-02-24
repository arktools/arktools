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

class VisCar::Impl : public Viewer {
public:
    Impl(std::string dataPath) : car(NULL) {
        std::string texturePath = dataPath+"/images/lz.rgb";
        std::string modelPath = dataPath+"/models/rcTruck.ac";
        car = new Car(modelPath);
        osg::Group * root = new Frame(1,"N","E","D");
        root->addChild(new Terrain(texturePath,osg::Vec3(10,10,0)));
        if (car) root->addChild(car);
        setCameraManipulator(new osgGA::TrackballManipulator);
        getCameraManipulator()->setHomePosition(osg::Vec3(-3,3,-3),
                                                osg::Vec3(0,0,0),osg::Vec3(0,0,-1));
        if (root) setSceneData(root);
        setUpViewInWindow(0,0,400,400);
        run();
    }
    Car * car;
};

VisCar::VisCar(std::string dataPath) :
    _impl(new Impl(dataPath)) {
};

VisCar::~VisCar() {
    if (_impl) delete _impl;
}

void VisCar::setEuler(double roll, double pitch, double yaw) {
    _impl->lock();
    _impl->car->setEuler(roll, pitch, yaw);
    _impl->unlock();
};

void VisCar::setPosition(double x, double y, double z) {
    _impl->lock();
    _impl->car->setPositionScalars(x, y, z);
    _impl->unlock();
};

void VisCar::setU(double throttle, double steering) {
    _impl->lock();
    _impl->car->setU(throttle, steering);
    _impl->unlock();
};



// vim:ts=4:sw=4
