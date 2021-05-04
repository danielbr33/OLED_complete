/*
 * Buzzer.cpp
 *
 *  Created on: 15.09.2018
 *      Author: mice
 */

#include "Buzzer.h"
#include "stdlib.h"
#include "tim.h"
#include "cmsis_os.h"
#include "math.h"

#define TIM1_FREQ 1000000

void Buzzer::Init(void){
	SetPWMFrequency(1000.f);
	Mute();
	HAL_TIM_PWM_Start(timer, channel);

	osDelay(500);

	uint8_t tempMicro = 2;

	if (tempMicro%3 == 0){
	//if (tools.GetMicros() % 3 == 0) {
		for (uint8_t i = 0; i < 8; i++) {
			Tone("C6", 50);
			Tone("E6", 50);
			Tone("A6", 100, 126);
		}
		for (uint8_t i = 0; i < 3; i++) {
			Tone("B5", 50);
			Tone("E6", 50);
			Tone("A6", 100, 126);
		}
		for (uint8_t i = 0; i < 5; i++) {
			Tone("B5", 50);
			Tone("E6", 50);
			Tone("G6", 100, 126);
		}
		osDelay(300);
	}
	//else if (tools.GetMicros() % 2 == 0) {
	else if (tempMicro%2 ==0){

		for (uint8_t i = 0; i < 5; i++) {
			Tone("D5", 40);
			Tone("E5", 40);
			Tone("G5", 40);
			Tone("D6", 40, 50);
		}
		osDelay(210);
		for (uint8_t i = 0; i < 5; i++) {
			Tone("D5", 40);
			Tone("E5", 40);
			Tone("G5", 40);
			Tone("D6", 40, 50);
		}
		osDelay(210);
		for (uint8_t i = 0; i < 4; i++) {
			Tone("D5", 20);
			Tone("E5", 20);
			Tone("G5", 20);
			Tone("D6", 20, 25);
		}
		Tone("D5", 40);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("D6", 40, 50);
		osDelay(3360);

		// #6 - #9
		for (uint8_t i = 0; i < 2; i++) {
			osDelay(210);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("A5", 80, 50);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("A5", 80, 50);

			osDelay(210);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("G5", 80, 50);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("G5", 80, 50);

			osDelay(210);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("F#5", 80, 50);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("F#5", 80, 50);

			osDelay(210);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("E5", 80, 50);
			Tone("B4", 40);
			Tone("D5", 40);
			Tone("E5", 80, 50);
			osDelay(840);
		}
		// #10
		osDelay(210);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("D6", 80, 50);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("D6", 80, 50);

		osDelay(210);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("C6", 80, 50);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("C6", 80, 50);

		osDelay(210);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("B5", 80, 50);
		// #11
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("B5", 80, 50);

		osDelay(210);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("A5", 80, 50);
		Tone("E5", 40);
		Tone("G5", 40);
		Tone("A5", 80, 50);
		osDelay(840);

		// #12
		osDelay(210);
		Tone("D#5", 40);
		Tone("G5", 40);
		Tone("D6", 80, 50);
		Tone("D#5", 40);
		Tone("G5", 40);
		Tone("D6", 80, 50);

		osDelay(210);
		Tone("D#5", 40);
		Tone("G5", 40);
		Tone("C6", 80, 50);
		Tone("D#5", 40);
		Tone("G5", 40);
		Tone("C6", 80, 50);

		osDelay(210);
		Tone("C5", 40);
		Tone("D#5", 40);
		Tone("A#5", 80, 50);
		Tone("C5", 40);
		Tone("D#5", 40);
		Tone("A#5", 80, 50);

		osDelay(210);
		Tone("C5", 40);
		Tone("D#5", 40);
		Tone("A5", 80, 50);
		Tone("C5", 40);
		Tone("D#5", 40);
		Tone("A5", 80, 50);
		osDelay(840);


	} else {
		// 1/4 - 460; 1/8 - 230
		Tone("A#5", 900);

		Tone("F5", 150);
		Tone("A#5", 150);
		Tone("C6", 150);
		Tone("C#6", 300);
		Tone("C6", 150);
		Tone("A#5", 300);
		Tone("C6", 300);
		Tone("G#5", 1350);

		Tone("F6", 300);
		Tone("D#6", 150);
		Tone("C#6", 300);
		Tone("C6", 450);
		Tone("A#5", 900);

		Tone("F5", 150);
		Tone("A#5", 150);
		Tone("C6", 150);
		Tone("C#6", 300);
		Tone("C6", 150);
		Tone("C#6", 300);
		Tone("D#6", 300);
		Tone("G#5", 1350);

		Tone("F6", 300);
		Tone("F#6", 150);
		Tone("F6", 300, 450);
	}
	/*Tone("A6", 75, 75);
	Tone("A6", 75, 225);
	Tone("A6", 75, 225);
	Tone("F6", 75, 75);
	Tone("A6", 75, 225);
	Tone("C7", 75, 525);
	Tone("C6", 75, 225);*/
}


void Buzzer::SingleBeep(Sound sound){
	if (sound == Sound1){
		Tone("C6", 100);
		Tone("F6", 100);
		Tone("G6", 100, 100);
	}
	else if(sound == Sound2){

		Tone("G6", 100, 100);
		Tone("F6", 100);
		Tone("C6", 100);
	}
	else if(sound == Sound3){
		Tone("C#6", 100, 200);
		Tone("D6", 100);
		Tone("F#6", 100, 50);
		Tone("C#6", 100, 50);
	}
}

void Buzzer::Loop(void) {
	if (mode) {
		if (mode & LOW_BATTERY) {
			Tone("E6", 150);
			Tone("D6", 150);
			Tone("F#5", 300);
			Tone("G#5", 300);

			Tone("C#6", 150);
			Tone("B5", 150);
			Tone("D5", 300);
			Tone("E5", 300);

			Tone("B5", 150);
			Tone("A5", 150);
			Tone("C#5", 300);
			Tone("E5", 300);

			Tone("A5", 900, 900);
		}
		if (mode & IMU_CALIBRATION) {
			Tone("B6", 10, 250);
			DisableMode(IMU_CALIBRATION);
		}
		if (mode & ONE_BEEP) {
			Tone("D7", 250, 250);
			DisableMode(ONE_BEEP);
		}
		if (mode & ARMING) {
			Tone("G5", 500, 100);
			Tone("D6", 800, 200);
			DisableMode(ARMING);
		}
		if (mode & DISARMING) {
			Tone("D6", 300, 50);
			Tone("D6", 300, 50);
			Tone("G5", 800, 200);
			DisableMode(DISARMING);
		}
		if (mode & THREE_BEEPS) {
			Tone("G7", 250, 250);
			Tone("G7", 250, 250);
			Tone("G7", 250, 250);
			DisableMode(THREE_BEEPS);
		}
		if (mode & SMIECIARKA) {
			Tone("G6", 700, 300);
			DisableMode(SMIECIARKA);
		}

	} else
		Mute();
	osDelay(5);
}
void Buzzer::SetBeepPower(float pwr){
	if(pwr > 1.f)
		pwr = 1.f;
	else if(pwr < 0.f)
		pwr = 0.f;

	if(channel == TIM_CHANNEL_1)
		timer_macro->CCR1 = (uint16_t) (floorf( pwr * TIM1->ARR / 2.f));
	if(channel == TIM_CHANNEL_2)
		timer_macro->CCR2 = (uint16_t) (floorf( pwr * TIM1->ARR / 2.f));
	if(channel == TIM_CHANNEL_3)
		timer_macro->CCR3 = (uint16_t) (floorf( pwr * TIM1->ARR / 2.f));
	if(channel == TIM_CHANNEL_4)
		timer_macro->CCR4 = (uint16_t) (floorf( pwr * TIM1->ARR / 2.f));
}
void Buzzer::SetPWMFrequency(float freq){
	timer_macro->CNT = 0u;
	timer_macro->ARR = (uint16_t)(roundf(TIM1_FREQ / freq) - 1);
}
void Buzzer::Mute(void){
	if (channel == TIM_CHANNEL_1)
		timer_macro->CCR1 = 0;
	if (channel == TIM_CHANNEL_2)
		timer_macro->CCR2 = 0;
	if (channel == TIM_CHANNEL_3)
		timer_macro->CCR3 = 0;
	if (channel == TIM_CHANNEL_4)
		timer_macro->CCR4 = 0;
}
void Buzzer::Beep(uint8_t power, uint8_t pitch){

}
void Buzzer::Tone(const char* keynote, uint16_t duration, uint16_t pause, float loudness) {
	uint8_t octave = 0, note = 0;
	for (uint8_t i = 0; i < 12; i++) {
		if (keynote[0] == keynotes[i][0]) {
			note = i;
			break;
		}
	}

	if (keynote[1] == '#') {
		note++;
		octave = atoi(&keynote[2]);
	} else
		octave = atoi(&keynote[1]);

	float frequency = NoteToFrequency(octave * 12 + note);

	SetPWMFrequency(frequency);
	SetBeepPower(loudness);
	if (duration) {
		osDelay(duration);
		Mute();
	}
	if (pause)
		osDelay(pause);
}

void Buzzer::EnableMode(Mode mode) {
	this->mode |= mode;
}
void Buzzer::DisableMode(Mode mode) {
	this->mode &= ~mode;
}
float Buzzer::NoteToFrequency(uint8_t note) {
	if (note <= 119)
		return base_a4*powf(2.f,(note-57)/12.f);
	return -1;
}

Buzzer::Buzzer(TIM_HandleTypeDef *timer, TIM_TypeDef* timer_macro, uint32_t channel) {
	// TODO Auto-generated constructor stub
	this->timer = timer;
	this->timer_macro = timer_macro;
	this->channel = channel;
}

Buzzer::~Buzzer() {
	// TODO Auto-generated destructor stub
}

