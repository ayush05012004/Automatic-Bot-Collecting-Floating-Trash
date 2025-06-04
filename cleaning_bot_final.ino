#include <Servo.h>
#include <NewPing.h>

// Motor A (Left Motor)
#define IN1 2
#define IN2 3
#define ENA 5 

// Motor B (Right Motor)
#define IN3 4
#define IN4 7
#define ENB 6 

// Ultrasonic Sensors
#define TRIG_WASTE 8
#define ECHO_WASTE 10
#define TRIG_OBS 11
#define ECHO_OBS 12
#define MAX_DISTANCE 200

// Servo for Waste Collection
#define SERVO_RIGHT 9
#define SERVO_LEFT 13

// State Variables
char lastCommand = 'S';
boolean autoMode = false;  

// Objects
NewPing sonarWaste(TRIG_WASTE, ECHO_WASTE, MAX_DISTANCE);
NewPing sonarObs(TRIG_OBS, ECHO_OBS, MAX_DISTANCE);
Servo servoRight, servoLeft;

void setup() {
    Serial.begin(9600);

    // Motor Setup
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Servo Setup
    servoRight.attach(SERVO_RIGHT);
    servoLeft.attach(SERVO_LEFT);
    servoRight.write(0);
    servoLeft.write(180);

    // Motor Speed
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);

    Serial.println("Manual Mode Started...");
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read();
        while (Serial.available()) Serial.read(); // Flush buffer

        if (command == 'M') {
            autoMode = !autoMode;
            Serial.println(autoMode ? "Auto Mode Activated" : "Manual Mode Activated");
            if (!autoMode) stopBot();
        } 
        else if (command == 'P' && !autoMode) {
            pickItem();
        } 
        else if (!autoMode) {
            lastCommand = command;
            executeManualCommand();
        }
    }

    if (autoMode) runAutoMode();
}

// ============================ Manual Mode ============================ //
void executeManualCommand() {
    switch (lastCommand) {
        case 'F': moveForward(); break;
        case 'B': moveBackward(); break;
        case 'L': turnLeft(); break;
        case 'R': turnRight(); break;
        case 'S': stopBot(); break;
    }
}

void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopBot() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// ============================ Auto Mode ============================ //
void runAutoMode() {
    int distWaste = sonarWaste.ping_cm();
    int distObs = sonarObs.ping_cm();

    if (distObs > 0 && distObs <= 45) {
        avoidObstacle();
    } else if (distWaste > 0 && distWaste <= 35) {
        collectWaste();
    } else {
        moveForward();
    }
}

void avoidObstacle() {
    moveBackward();
    delay(500);
    
    long startTime = millis();
    while (sonarObs.ping_cm() <= 45) {
        turnRight();
        delay(100);
        if (millis() - startTime > 3000) {
            stopBot();
            return;
        }
    }
    moveForward();
}

// ============================ Simultaneous Servo Movement ============================ //
void moveBothServos(int startRight, int endRight, int startLeft, int endLeft, int stepDelay) {
    int posRight = startRight;
    int posLeft = startLeft;
    int step = 2; // Adjust step size for smooth movement

    while ((startRight < endRight ? posRight <= endRight : posRight >= endRight) ||
           (startLeft < endLeft ? posLeft <= endLeft : posLeft >= endLeft)) {
        
        if (startRight < endRight ? posRight <= endRight : posRight >= endRight) {
            servoRight.write(posRight);
            posRight += (startRight < endRight) ? step : -step;
        }
        
        if (startLeft < endLeft ? posLeft <= endLeft : posLeft >= endLeft) {
            servoLeft.write(posLeft);
            posLeft += (startLeft < endLeft) ? step : -step;
        }
        
        delay(stepDelay);
        delay(50);
    }
}

// ============================ Collect Waste Function ============================ //
void collectWaste() {
    stopBot();
    delay(500);

    // Move both servos together
    moveBothServos(0, 180, 180, 0, 20);
    
    delay(1000);  // Hold position

    // Move both servos back
    moveBothServos(180, 0, 0, 180, 20);

    moveForward();
}

// ============================ Pick Item Function ============================ //
void pickItem() {
    moveBothServos(0, 180, 180, 0, 20);
    
    delay(1000);  // Hold position

    moveBothServos(180, 0, 0, 180, 20);
}