#include "motor_control.h"

#define MOTOR_SLEEP 16
#define MOTOR_ENABLE 12
#define MOTOR_PHASE 13
#define MOTOR_ENC_A 4
#define MOTOR_ENC_B 5

volatile unsigned int turns = 0;
volatile unsigned int saved_turns = 0;
volatile Direction direction = Direction::Up;
volatile bool moving = false;

void setupMotor() {
  /* Set modes for pins */
  pinMode(MOTOR_SLEEP, OUTPUT);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_PHASE, OUTPUT);
  pinMode(MOTOR_ENC_A, INPUT);
  pinMode(MOTOR_ENC_B, INPUT);

  /* Start motor */
  digitalWrite(MOTOR_SLEEP, HIGH);
  digitalWrite(MOTOR_PHASE, LOW);
  digitalWrite(MOTOR_ENABLE, LOW);

  /* Interupt setup */
  attachInterrupt(digitalPinToInterrupt(MOTOR_ENC_A), handleEncoderInterrupt,
                  RISING);
  // attachInterrupt(digitalPinToInterrupt(MOTOR_ENC_B), handleEncoderInterrupt,
  // RISING);
}

ICACHE_RAM_ATTR void handleEncoderInterrupt() {
  updateTurnsCount();
  stopMotorWhenDestinationReached();
}

/* Updates the turns count based on the direction */
void updateTurnsCount() {
  if (direction == Direction::Down && turns == 0) {
    return;
  }

  direction == Direction::Up ? turns++ : turns--;
}

/* Stops the motor when the destination is reached */
void stopMotorWhenDestinationReached() {
  if (!moving) {
    return;
  }

  if (validateDirection(direction)) {
    stopMotor();
  }
}

/* Stops the motor and sets the moving flag to false */
void stopMotor() {
  moving = false;
  digitalWrite(MOTOR_ENABLE, LOW);
}

void move(Direction dir) {
  /* Check if movement is possible */
  if (validateDirection(dir)) {
    return;
  }

  /* Set the movement direction */
  direction = dir;

  /* Set the motor phase */
  digitalWrite(MOTOR_PHASE, direction == Direction::Down ? LOW : HIGH);

  /* Enable motor movement */
  moving = true;
  digitalWrite(MOTOR_ENABLE, HIGH);
  // analogWrite(MOTOR_ENABLE, 768); // 75% duty cycle
}

bool validateDirection(Direction dir) {
  return (dir == Direction::Up && turns >= saved_turns) ||
         (dir == Direction::Down && turns == 0);
}