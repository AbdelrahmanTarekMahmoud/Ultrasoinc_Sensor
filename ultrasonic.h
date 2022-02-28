/*
 * ultrasonic.h
 *
 *  Created on: Feb 28, 2022
 *      Author: abdelrahman
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* ULTRASONIC Trigger And Echo Ports and pins */
#define TRIGGER_PORT   PORTB_ID
#define TRIGGER_PIN    PIN5_ID

#define ECHO_PORT      PORTD_ID
#define ECHO_PIN       PIN6_ID

#define trigger_pulse  10     // time in micro-seconds
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 *Initialize the ICU driver as required.
 Setup the ICU call back function.
 Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);
/*
 * Description :
 Send the Trigger pulse to the ultrasonic
 */
void Ultrasonic_Trigger(void);
/*
 * Description :
 Send the trigger pulse by using Ultrasonic_Trigger function.
 Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void);
/*
 * Description :
 This is the call back function called by the ICU driver.
 This is used to calculate the high time (pulse time) generated by the ultrasonic sensor
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
