
#include <Wire.h>
#include <LIDARLite.h>

#define ITERATOR 50

LIDARLite myLidarLite;

unsigned long  prev_dist = 0;
unsigned long  curr_dist = 0;

double curr_speed = 0;
unsigned long curr_time = 0;

int k = 0;

void setup()
{
  Serial.begin(115200); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
}


double typicalBreakingDistance(double curr_speed) {
    double result = 0.039 * curr_speed * curr_speed * 0.2941;

    return result;
}

boolean isRLR(int curr_dist, double curr_speed) {
    double breaking_distance = typicalBreakingDistance(curr_speed);
    Serial.print("typical breaking distance : ");
    Serial.println(breaking_distance);
    if (curr_dist > 0 && curr_dist * 0.01 < breaking_distance) {
        Serial.println("WARNING ! ! ");
    }
    
}


void loop()
{
  long prev_time;
  long elapsed_time;

  prev_time = curr_time;
  curr_time = millis();
  elapsed_time = curr_time - prev_time;
  prev_dist = curr_dist;
  curr_dist = (double)myLidarLite.distance(); 
  curr_speed = (double)(prev_dist - curr_dist) / elapsed_time * 36;

  if (curr_dist <= 4000 && curr_speed <= 10000)
  {
    
    Serial.print("Distance : ");
    Serial.print(curr_dist);
    Serial.print("\tspeed : ");
    Serial.print(curr_speed); // Print the distance//
    Serial.println("km/h");

    isRLR(curr_dist, curr_speed);
  }
    
  delay(100);
}
