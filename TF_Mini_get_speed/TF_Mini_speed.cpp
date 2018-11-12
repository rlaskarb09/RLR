#include <Arduino.h>
#include <Wire.h>
#include <stdarg.h>
#include "TF_Mini_speed.h"

void TF_Mini_speed::get_speed() {
    static int rx[9];
    static char i = 0;
    static char j = 0;
    long prev_time = 0, elapsed_time = 0;
    
    if (get_data(&i, rx)) {
        j++;
    }

    if (j >= this->iterator) {
        j = 0;
        prev_time = this->curr_time;
        this->curr_time = millis();
        elapsed_time = this->curr_time - prev_time;
        this->prev_dist = this->curr_dist;
        this->curr_dist = rx[2] + rx[3] * 256;
        //Serial.print("current distance = ");
        //Serial.println(this->curr_dist);
        this->strength = rx[4] + rx[5] * 256;
        this->curr_speed = (double)(this->prev_dist - this->curr_dist) / elapsed_time * 36;
        this->isGotSpeed = true;
    }
}

boolean TF_Mini_speed::get_data(char * i, int rx[]) {
    char j = 0;
    int checksum = 0;

    if (Serial.available()) {
        rx[*i] = Serial.read();
        if (rx[0] != 0x59) {
            *i = 0;
        } else if (*i == 1 && rx[1] != 0x59) {
            *i = 0;
        } else if (*i == 8) {
            for (int j = 0; j < 8; j++) {
                checksum += rx[j];
            }
            if(rx[8] == (checksum % 256)) {
                //Serial.print("raw current distance = ");
                //Serial.println(rx[2] + rx[3] * 256);
                return true;
            } 
            *i = 0;
        } else {
            (*i)++;
        }
    }
    return false;
}
