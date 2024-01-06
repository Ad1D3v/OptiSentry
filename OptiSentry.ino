#include<Servo.h>

Servo x, y, tr;
int width = 640, height = 480;  // total resolution of the video
int xpos = 90, ypos = 90;  // initial positions of both Servos
byte triggerledPin = 4;
int leds1 = 0, leds2 = 0, val = 0;
int xmin = 265, xmax = 375, ymin = 195, ymax = 285;
int xinc = 98, xdec = 87.5, yinc = 100, ydec = 87.5, stop = 90;
unsigned long currtime = 0;
int tout = 0;
int trigg = 0;

void setup() {
  Serial.begin(9600);
  leds1 = 0;
  leds2 = 0;
  x.attach(9);
  y.attach(8);
  tr.attach(10);
  pinMode(triggerledPin, OUTPUT);
  digitalWrite(triggerledPin, LOW);
  tr.write(stop);
  tout = 0;
  trigg = 1;
}

void loop() {
  if (Serial.available() > 0)
  {
    int x_mid, y_mid;
    tout = 1;
    if (Serial.read() == 'X')
    {
      x_mid = Serial.parseInt();  // read center x-coordinate
      if (Serial.read() == 'Y')
        y_mid = Serial.parseInt(); // read center y-coordinate
    }
    /* adjust the servo within the squared region if the coordinates
        is outside it
    */
    if ((x_mid < xmin && x_mid > 20) || (x_mid > xmax && x_mid < 620)) {
      if (x_mid > xmax && x_mid < 620) {
        xpos = xinc;
        x.write(xpos);
        delay(100);
        x.write(stop);
        tr.write(stop);
        leds1 = 0;
        val = 0;
      }
      else if (x_mid < xmin && x_mid > 20) {
        xpos = xdec;
        x.write(xpos);
        delay(100);
        x.write(stop);
        tr.write(stop);
        leds1 = 0;
        val = 0;
      }
      else if (x_mid > xmin && x_mid < xmax) {
        xpos= stop;
        x.write(xpos);
        delay(100);
        x.write(stop);
        tr.write(stop);
        leds1 = 1;
        val = 0;
      }
      else {
        xpos=stop;
        ypos=stop;
        leds1=1;
        leds2=1;
        x.write(xpos);
        y.write(ypos);
        tr.write(stop);
        //val = 1;
        /*tr.write(180);
        delay(500);
        tr.write(0);
        delay(250);
        tr.write(90);*/
        //delay(1500);
      }
    }
    else if ((y_mid < ymin && y_mid > 20) || (y_mid > ymax && y_mid < 460)) {
      if (y_mid > ymax && y_mid < 460) {
        ypos = ydec;
        y.write(ypos);
        delay(100);
        y.write(stop);
        tr.write(stop);
        leds2 = 0;
        val = 0;
      }
      else if (y_mid < ymin && y_mid > 20) {
        ypos = yinc;
        y.write(ypos);
        delay(100);
        y.write(stop);
        tr.write(stop);
        leds2 = 0;
        val = 0;
      }
      else if (y_mid > ymin && y_mid < ymax) {
        ypos= stop;
        leds2 = 1;
        y.write(ypos);
        delay(100);
        y.write(stop);
        tr.write(stop);
        val = 0;
      }
      else {
        xpos=stop;
        ypos=stop;
        leds1=1;
        leds2=1;
        x.write(xpos);
        y.write(ypos);
        tr.write(stop);
        //val = 1;
        /*tr.write(180);
        delay(500);
        tr.write(0);
        delay(250);
        tr.write(90);*/
        //delay(1500);
      }
    }
    else {
      xpos=stop;
      ypos=stop;
      leds1=1;
      leds2=1;
      x.write(xpos);
      y.write(ypos);
      val = 1;
      /*tr.write(0);
      delay(250);
      tr.write(90);*/
      //delay(1500);
    }
    Serial.print(val);
    Serial.print(",");
    Serial.print(tout);
  }
  else {
    xpos=stop;
    ypos=stop;
    x.write(xpos);
    y.write(ypos);
    tr.write(stop);
    //val = 1;
  }
  statLED(leds1, leds2);
  trigmot(val);
  trigg = 1;
}

void statLED (int s1, int s2) {
  if (s1 == 1 && s2 == 1) {
    digitalWrite(triggerledPin, HIGH);
  }
  else {
    digitalWrite(triggerledPin, LOW);
  }
}

void trigmot (int val) {
  currtime = millis();
  if (val > 0 && trigg > 0) {
    tout += 5;
    tr.write(180);
    if (millis() > currtime+20) {
      tr.write(90);
    }
  }
  else {
    tr.write(90);
  }
  val = 0;
  trigg = 0;
  //delay(200);
}