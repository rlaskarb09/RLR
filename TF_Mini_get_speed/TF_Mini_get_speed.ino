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
        isRLR(tf_mini_speed->curr_dist, tf_mini_speed->curr_speed);
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

double typicalBreakingDistance(double curr_speed) {
    double result = 0.039 * curr_speed * curr_speed * 0.2941;

    return result;
}

boolean isRLR(int curr_dist, double curr_speed) {
    double breaking_distance = typicalBreakingDistance(curr_speed);
    //Serial.print("typical breaking distance : ");
    //Serial.println(breaking_distance);
    if (curr_dist > 0 && curr_dist * 0.01 < breaking_distance) {
        Serial.println("WARNING WARNING WARNING WARNING WARNING");\
    }
}

void serialEvent() {
    tf_mini_speed->get_speed(); 
}
