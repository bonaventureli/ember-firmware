/*
 * MotorController.h
 * Author: Jason Lefley
 * Date  : 2015-05-01
 */

#ifndef MOTORCONTROLLER_H_AVR
#define MOTORCONTROLLER_H_AVR

#include <stdint.h>

#include "AxisSettings.h"
#include "StateMachine.h"

namespace MotorController
{
void Initialize(MotorController_t* mcState);
void Reset();
void HandleSettingsCommand(Command* command, AxisSettings& axisSettings);
void HomeZAxis(int32_t homingDistance, MotorController_t* mcState);
void HomeRAxis(int32_t homingDistance, MotorController_t* mcState);
void HandleAxisLimitReached();
void Move(uint8_t motorIndex, int32_t distance, const AxisSettings& settings);
void EndMotion();
}

#endif /* MOTORCONTROLLER_H_AVR */
