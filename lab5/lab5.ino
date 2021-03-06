int motorSpeed;
unsigned long endTime;
int receivedInput = 0;
// 0 if waiting for first input,
// 1 if wating for second input,
// 2 if running motors

unsigned long startTime;

#define MOTOR1PWM 3
#define MOTOR1DIR 12
#define MOTOR1BRK 9


#define MOTOR2PWM 11
#define MOTOR2DIR 13
#define MOTOR2BRK 8


void setup() {
  Serial.begin(9600);

  // Set pins
  pinMode(MOTOR1PWM, OUTPUT);
  pinMode(MOTOR2PWM, OUTPUT);
  pinMode(MOTOR1DIR, OUTPUT);
  pinMode(MOTOR2DIR, OUTPUT);
  pinMode(MOTOR1BRK, OUTPUT);
  pinMode(MOTOR2BRK, OUTPUT);


  digitalWrite(MOTOR1DIR, LOW);
  digitalWrite(MOTOR2DIR, HIGH);
  digitalWrite(MOTOR1BRK, HIGH);
  digitalWrite(MOTOR2BRK, HIGH);
  digitalWrite(MOTOR1PWM, 0);
  digitalWrite(MOTOR2PWM, 0);

  
  Serial.println("Enter a motor speed!");
} 


void loop() {
  if (receivedInput == 0) { // Waiting for first input from user
    if (Serial.available() > 0) {
      int input = (Serial.readString()).toInt();

      if (input < 0 || input > 255) Serial.println("Enter a valid integer between 0 and 255.");
      else {
        motorSpeed = input;
        receivedInput = 1;
        Serial.println("How long do you want to run the motor for?");
      }

      
    }
  } else if (receivedInput == 1) { // Waiting for second input
    if (Serial.available() > 0) {
      int input = (Serial.readString()).toInt();

      if (input < 1 || input > 30) Serial.println("Enter a valid integer between 1 and 30.");
      else {
        receivedInput = 2;
        Serial.println("Running motors!");
          
        digitalWrite(MOTOR1BRK, LOW);
        digitalWrite(MOTOR2BRK, LOW);
          
        analogWrite(MOTOR1PWM, motorSpeed);
        analogWrite(MOTOR2PWM, motorSpeed);
          
        endTime = millis() + input * 1000;
      }
    }
  } else { // Run motors
    if (millis() > endTime) { // Motors have been running for specified amount of time
      receivedInput = 0;
      Serial.println("Enter a motor speed!");
        
      analogWrite(MOTOR1PWM, 0);
      analogWrite(MOTOR2PWM, 0);
      
      digitalWrite(MOTOR1BRK, HIGH);
      digitalWrite(MOTOR2BRK, HIGH);
    }
  }
}
