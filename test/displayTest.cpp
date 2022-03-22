#include <Arduino.h>
#include "Display.h"

void setup() {
  // put your setup code here, to run once:
    Display display(2, 4);
    display.init();
    delay(2000);
    display.prompt("Everything\nOK?");
    display.reset();
    display.println("Display module test");
    display.display();
    delay(2000);
    display.reset();
    display.setTextSize(1);
    display.print("Lorem ipsum Lorem ipsum Lorem ipsum Lorem ipsum Lorem ipsum Lorem ipsum ");
    display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
}