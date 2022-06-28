#include "main.h"
#include <cmath>

const double PI = 3.141592653589793238462643383279502884L;

double posX = 0;
double posY = 0;
double prevLeft = 0;
double prevRight = 0;
double prevBack = 0;
double thetaPrev = 0;
const double T_l = 2.5;
const double T_r = 2.5;
const double T_b = 2.75;

void updateOdom() {
    double deltaLeft = (leftEncoder.get() - prevLeft) * 2 * 180 / PI;
    double deltaRight = (rightEncoder.get() - prevRight) * 2 * 180 / PI;
    double deltaBack = (backEncoder.get() - prevBack) * 2 * 180 / PI;

    double deltaTheta = (deltaLeft - deltaRight) / (deltaLeft + deltaRight) + thetaPrev;

    if (deltaTheta == 0) {
        posX += deltaBack;
        posY += deltaRight;
    }
    else {
        posX += 2*sin(deltaTheta)*(deltaBack/deltaTheta + T_b);
        posY += 2*sin(deltaTheta)*(deltaRight/deltaTheta + T_r);
    }

    double prevLeft = leftEncoder.get();
    double prevRight = rightEncoder.get();
    double prevBack = backEncoder.get();
}