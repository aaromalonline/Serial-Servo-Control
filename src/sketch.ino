#include <SoftwareSerial.h>

#define SERVO_COUNT 6           // Number of servos
#define SERVO_BAUDRATE 115200   // Most serial servos use 100000 or 115200

// Connect TX to Servo Controller's RX
SoftwareSerial servoSerial(10, 11); 

int servoIDs[SERVO_COUNT] = {1, 2, 3, 4, 5, 6}; // Servo IDs

// Converts angle to position (0° to 240° maps to 0-1000 for SC/ST servos)
int angleToPosition(float angle) {
  return (int)(angle / 240.0 * 1000.0);
}

// Send move command to one servo
void moveServo(int id, int position, int time = 500) {
  byte cmd[10];
  cmd[0] = 0x55;
  cmd[1] = 0x55;
  cmd[2] = id;
  cmd[3] = 7;         // Length of following bytes
  cmd[4] = 1;         // CMD: Write position
  cmd[5] = position & 0xFF;
  cmd[6] = (position >> 8) & 0xFF;
  cmd[7] = time & 0xFF;
  cmd[8] = (time >> 8) & 0xFF;
  cmd[9] = 0;         // Checksum

  // Compute checksum: ~(ID + LEN + CMD + PARAMS)
  for (int i = 2; i <= 8; i++) {
    cmd[9] += cmd[i];
  }
  cmd[9] = ~cmd[9];

  // Send command
  for (int i = 0; i < 10; i++) {
    servoSerial.write(cmd[i]);
  }
}

// Move all servos to specified angles
void moveAllServos(float angles[]) {
  for (int i = 0; i < SERVO_COUNT; i++) {
    int pos = angleToPosition(angles[i]);
    moveServo(servoIDs[i], pos, 500); // 500ms movement time
  }
}

void setup() {
  servoSerial.begin(SERVO_BAUDRATE);
  Serial.begin(9600);  // Start serial communication for input
  delay(500); // Wait for servos to initialize

  Serial.println("Ready to receive angles.");
}

void loop() {
  // Check if data is available on Serial input
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read input as a string
    
    // Parse the input into an array of floats
    float angles[SERVO_COUNT];
    int startIndex = 0;
    for (int i = 0; i < SERVO_COUNT; i++) {
      int endIndex = input.indexOf(',', startIndex);
      if (endIndex == -1) {
        endIndex = input.length();
      }
      
      String angleStr = input.substring(startIndex, endIndex);
      angles[i] = angleStr.toFloat();  // Convert string to float and store in angles array
      
      startIndex = endIndex + 1;
    }

    // Move all servos based on received angles
    moveAllServos(angles);
    Serial.println("Servos moved to the new angles.");
  }
}
