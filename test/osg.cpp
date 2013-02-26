/* OpenSceneGraph example, osgcompositeviewer.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*/

#include <iostream>

#include <osg/Notify>
#include <osg/io_utils>

#include <osg/ArgumentParser>
#include <osg/GraphicsContext>
#include <osgDB/WriteFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <ctime>

#include "private/Viewer.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

// Thread that runs the viewer's frame loop as we can't run Qt in the background...

int main(int argc, char **argv)
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
    viewer->setSceneData(new osg::Group);
    viewer->setCameraManipulator(new osgGA::TrackballManipulator());
    // create a thread to run the viewer's frame loop
//    viewer->setUpViewAcrossAllScreens();
    viewer->setUpViewInWindow(0,0,400,400);
    viewer->realize();
    boost::thread thread(boost::bind(&osgViewer::Viewer::run,viewer));
    std::cout << "viewer running" << std::endl;
    while(1) {
        sleep(1);
    }
//    thread.join();
    return 0;
}
