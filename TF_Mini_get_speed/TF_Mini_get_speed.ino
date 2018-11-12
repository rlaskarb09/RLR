#define ITERATOR 10
#define ANGLE 0
#include "TF_Mini_speed.h"

TF_Mini_speed * tf_mini_speed;

void setup() {
    Serial.begin(115200);
    tf_mini_speed = new TF_Mini_speed(ITERATOR, ANGLE);
}

void loop() {
    if(tf_mini_speed->isGotSpeed) {
        tf_mini_speed->isGotSpeed = false;
        printResult();
    }
}

void printResult() {
    Serial.print(tf_mini_speed->curr_dist);
    Serial.print("cm\t");
    Serial.print(tf_mini_speed->curr_speed);
    Serial.print("km/h\t");
    //Serial.print(tf_mini_speed->curr_time);
    //Serial.print("ms\t");
    //Serial.print("strength: ");
    //Serial.print(tf_mini_speed->strength);
    Serial.println();
}

void serialEvent() {
    tf_mini_speed->get_speed(); 
}
