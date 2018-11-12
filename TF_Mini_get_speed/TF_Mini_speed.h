#ifndef TF_MINI_SPEED
#define TF_MINI_SPEED

#include <Arduino.h>

class TF_Mini_speed {
public:
    TF_Mini_speed(int iterator, double angle) {
        this->iterator = iterator;
        this->cosine = cos(angle);
        this->curr_dist = 0;
        this->isGotSpeed = false;
    }
    int prev_dist;
    int curr_dist;
    int strength;
    double curr_speed;
    long curr_time;
    int iterator;
    double cosine;
    boolean isGotSpeed;

    void get_speed();
    boolean get_data(char * i, int * rx);

private:
};

#endif
