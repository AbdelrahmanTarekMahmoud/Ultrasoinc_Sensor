/*
 * ultrasonic.c
 *
 *  Created on: Feb 28, 2022
 *      Author: abdelrahman
 */
#include"ultrasonic.h"
#include"gpio.h"
#include"icu.h"
#include"util/delay.h"

uint8 g_edgeCount = 0;
uint16 TIMER_VALUE = 0; /* the time required by the sensor to detect an object and return back from an object*/
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Ultrasonic_init(void) {
	/*setup Icu to with f_cpu_clock and to detect Rising Edge initially*/
	Icu_ConfigType Icu_Config = { F_CPU_8, RISING };
	Icu_init(&Icu_Config);
	/*CallBack function Becasue Icu is in lower layer than Ultrasonic*/
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}
void Ultrasonic_Trigger(void) {
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(trigger_pulse); /*Min Trigger pulse 10 micro Seconds */
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
	Ultrasonic_Trigger();
	return (((TIMER_VALUE) / 58.8));
}
void Ultrasonic_edgeProcessing(void) {
	g_edgeCount++;
	if (g_edgeCount == 1) {
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	if (g_edgeCount == 2) {
		TIMER_VALUE = Icu_getInputCaptureValue();
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount = 0;
	}
}

