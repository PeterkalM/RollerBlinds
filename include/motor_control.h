#pragma once

#include <Arduino.h>

extern volatile unsigned int turns;
extern volatile unsigned int saved_turns;

enum class Direction { Up, Down };

void setupMotor();
void move(Direction dir);
void stopMotor();
bool validateDirection(Direction dir);
void handleEncoderInterrupt();