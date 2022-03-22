#include <Arduino.h>
#include <Definitions.h>
#include <Drive.h>
#include <Display.h>

Drive driveModule(new Motor(3, 5), new Motor(6, 11));
Display display(2, 4);


void forwardTest() {
    display.reset();
    display.println("forward\n++");
    display.display();
    for (size_t i = 0; i < 100; i++) {
        driveModule.drive(i);
        delay(20);
    }
    display.reset();
    display.println("forward\n--");
    display.display();
    for (size_t i = 100; i > 0; i--) {
        driveModule.drive(i);
        delay(20);
    }
}

void reverseTest() {
    display.reset();
    display.println("reverse\n++");
    display.display();
    for (size_t i = 0; i < 100; i++) {
        driveModule.drive(-i);
        delay(20);
    }
    display.reset();
    display.println("reverse\n--");
    display.display();
    for (size_t i = 100; i > 0; i--) {
        driveModule.drive(-i);
        delay(20);
    }
}

void rotateTest(uint8_t turnDirection) {
    display.reset();
    display.print("rotate\n++");
    display.println(turnDirection == 1 ? "right" : "left");
    display.display();
    for (size_t i = 0; i <= 100; i++) {
        driveModule.rotate(i, turnDirection);
        delay(20);
    }
    display.reset();
    display.print("rotate\n--");
    display.println(turnDirection == 1 ? "right" : "left");
    display.display();
    for (size_t i = 100; i > 0; i--) {
        driveModule.rotate(i, turnDirection);
        delay(20);
    }
}

void turnAroundTest(uint8_t turnDirection) {
    display.reset();
    display.print("turn\naround\n++");
    display.print(turnDirection == 1 ? "right" : "left");
    display.display();
    for (size_t i = 0; i <= 100; i++) {
        driveModule.turnAround(i, turnDirection);
        delay(20);
    }
    display.reset();
    display.print("turn\naround\n--");
    display.println(turnDirection == 1 ? "right" : "left");
    display.display();
    for (size_t i = 100; i > 0; i--) {
        driveModule.turnAround(i, turnDirection);
        delay(20);
    }
}

void differentialTest() {
    display.reset();
    display.println("diffrntial\n0-100\nleft");
    display.display();
    for (size_t i = 0; i <= 100; i++) {
        driveModule.drive(i, i / 2);
        delay(20);
    }

    display.reset();
    display.println("diffrntial\n0-100\nright");
    display.display();
    for (size_t i = 0; i <= 100; i++) {
        driveModule.drive(i / 2, i);
        delay(20);
    }

    display.reset();
    display.println("diffrntial\n100-0\nleft");
    display.display();
    for (size_t i = 100; i > 0; i--) {
        driveModule.drive(i, i / 2);
        delay(20);
    }

    display.reset();
    display.println("diffrntial\n100-0\nright");
    display.display();
    for (size_t i = 100; i > 0; i--) {
        driveModule.drive(i / 2, i);
        delay(20);
    }

}

void lowPWMTest() {
    for (size_t i = 0; i < 10; i++) {
        display.reset();
        display.print("speed: ");
        display.println(i);
        display.display();
        driveModule.drive(i);
        delay(200);
    }
    for (size_t i = 10; i > 0; i--) {
        display.reset();
        display.print("speed: ");
        display.println(i);
        display.display();
        driveModule.drive(i);
        delay(200);
    }
}

void setup() {
    driveModule.init();
    display.init();
    delay(2000);
}


void loop() {
    forwardTest();
    reverseTest();
    rotateTest(LEFT);
    rotateTest(RIGHT);
    turnAroundTest(LEFT);
    turnAroundTest(RIGHT);
    differentialTest();
    lowPWMTest();
}