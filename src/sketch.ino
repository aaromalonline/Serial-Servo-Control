#include <SoftwareSerial.h>
#include <LX16Servo.h>

// Define the serial bus (TX, RX) for SoftwareSerial
SoftwareSerial servoBus(10, 11); // RX, TX (connect only TX to servo signal)

// Create servo instances
LX16Servo servo1;
LX16Servo servo2;

void setup() {
  Serial.begin(9600);        // For user input via Serial Monitor
  servoBus.begin(115200);    // Serial bus communication with servos

  // Attach servos to the bus and set their IDs
  servo1.attach(1, servoBus); // ID 1
  servo2.attach(2, servoBus); // ID 2

  Serial.println("Ready! Enter angles like 90,45");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove spaces/newlines

    int commaIndex = input.indexOf(',');

    if (commaIndex != -1) {
      int angle1 = input.substring(0, commaIndex).toInt();
      int angle2 = input.substring(commaIndex + 1).toInt();

      servo1.move(angle1);
      servo2.move(angle2);

      Serial.print("Servo 1 -> ");
      Serial.print(angle1);
      Serial.print("   Servo 2 -> ");
      Serial.println(angle2);
    } else {
      Serial.println("Invalid input! Use format like: 90,45");
    }

    Serial.println("Enter next angles:");
  }
}



/* Without LX16Servo.h library

#include <SoftwareSerial.h>

SoftwareSerial servoSerial(10, 11); // RX, TX — Connect only TX (pin 11) to servo signal

const int servoCount = 2;
const uint8_t servoIDs[] = {1, 2};  // Serial servo IDs

void setup() {
  Serial.begin(9600);
  servoSerial.begin(115200);  // Typical for serial servos

  Serial.println("Ready! Enter angles like 90,45");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int commaIndex = input.indexOf(',');

    if (commaIndex != -1) {
      int angle1 = input.substring(0, commaIndex).toInt();
      int angle2 = input.substring(commaIndex + 1).toInt();

      moveServo(servoIDs[0], angle1);
      moveServo(servoIDs[1], angle2);

      Serial.print("Servo ");
      Serial.print(servoIDs[0]);
      Serial.print(" -> ");
      Serial.print(angle1);
      Serial.print("   Servo ");
      Serial.print(servoIDs[1]);
      Serial.print(" -> ");
      Serial.println(angle2);
    } else {
      Serial.println("Invalid input! Use format like: 90,45");
    }

    Serial.println("Enter next angles:");
  }
}

// Send move command to servo with ID and angle (0–240 for most serial servos)
void moveServo(uint8_t id, uint16_t angle) {
  // Convert angle (0–240°) to position value (e.g., 0–1000 or 0–1023)
  uint16_t pos = map(angle, 0, 240, 0, 1000);

  uint8_t packet[10];
  uint8_t len = 7;          // Length after ID
  uint8_t cmd = 1;          // CMD for "move"
  uint8_t time_l = 0x20;    // Movement time (optional, 0x0020 = 32ms)
  uint8_t time_h = 0x00;

  packet[0] = 0x55;
  packet[1] = 0x55;
  packet[2] = id;
  packet[3] = len;
  packet[4] = cmd;
  packet[5] = pos & 0xFF;
  packet[6] = (pos >> 8) & 0xFF;
  packet[7] = time_l;
  packet[8] = time_h;

  // Checksum = ~(ID + LEN + CMD + PARAMS) & 0xFF
  uint8_t checksum = id + len + cmd + packet[5] + packet[6] + time_l + time_h;
  packet[9] = ~checksum;

  servoSerial.write(packet, 10);
}

*/
