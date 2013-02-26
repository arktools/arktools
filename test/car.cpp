#include <iostream>
#include <cmath>

#include <visualization.hpp>
#include <utilities.hpp>

#include <boost/thread.hpp>

VisCar * car;

int main(int argc, char * argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " data_directory" << std::endl;
        return 1;
    }

    VisCar  car(argv[1]);

    float period = 3; // seconds
    float dt = 0.05;
    for (float t=0;t<period;t+=dt) {
        std::cout << "t: " << t << std::endl;
        sleepMillis(dt*1000);
        float phi = 0.5*sin(2*M_PI/period*t);
        float theta = 0.5*sin(2*M_PI/period*t);
        float psi = 0.5*sin(2*M_PI/period*t);
        float throttle = 0.5*sin(2*M_PI/period*t);	
        float steering = 0.5*sin(2*M_PI/period*t);
        float pN = 0.3*sin(2*M_PI/period*t);
        float pE = 0.3*cos(2*M_PI/period*t);
        float pD = -0.3*(1+sin(2*M_PI/period*t));
        car.setPosition(pN, pE, pD);
        car.setEuler(phi,theta,psi);
        car.setU(throttle,steering);
        car.frame();
    }

    return 0;
}

// vim:ts=4:sw=4
