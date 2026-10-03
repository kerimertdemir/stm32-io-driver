/*
 * io_driver.c
 *
 *  Created on: Oct 3, 2026
 *      Author: HP
 */

#include "io_driver.h"

void IO_Initialization(IO_Infos_t *ioInfo){
	//Input
	ioInfo->inputsInfo.userButton.GPIOx = USER_BUTTON_GPIO_Port;
	ioInfo->inputsInfo.userButton.GPIO_Pin = USER_BUTTON_Pin;
	ioInfo->inputsInfo.userButton.numOfInput = 0;
	ioInfo->inputsInfo.userButton.currentState = GPIO_PIN_RESET;
	ioInfo->inputsInfo.userButton.lastState = GPIO_PIN_RESET;
	ioInfo->inputsInfo.userButton.currentTime = 0;
	ioInfo->inputsInfo.userButton.debounceTime = DEBOUNCE_TIME;
	ioInfo->inputsInfo.userButton.inputStatus = INPUT_STATUS_LOW;

	//Output
	ioInfo->outputsInfo.ledGreen.GPIOx = LED_GREEN_GPIO_Port;
	ioInfo->outputsInfo.ledGreen.GPIO_Pin = LED_GREEN_Pin;
	ioInfo->outputsInfo.ledGreen.pinState = GPIO_PIN_RESET;

	ioInfo->outputsInfo.ledOrange.GPIOx = LED_ORANGE_GPIO_Port;
	ioInfo->outputsInfo.ledOrange.GPIO_Pin = LED_ORANGE_Pin;
	ioInfo->outputsInfo.ledOrange.pinState = GPIO_PIN_RESET;

	ioInfo->outputsInfo.ledRed.GPIOx = LED_RED_GPIO_Port;
	ioInfo->outputsInfo.ledRed.GPIO_Pin = LED_RED_Pin;
	ioInfo->outputsInfo.ledRed.pinState = GPIO_PIN_RESET;

	ioInfo->outputsInfo.ledBlue.GPIOx = LED_BLUE_GPIO_Port;
	ioInfo->outputsInfo.ledBlue.GPIO_Pin = LED_BLUE_Pin;
	ioInfo->outputsInfo.ledBlue.pinState = GPIO_PIN_RESET;
}



void IO_Status_Control(IO_Infos_t *ioInfo){
	IO_Output_Control(&ioInfo->outputsInfo.ledGreen);
	IO_Output_Control(&ioInfo->outputsInfo.ledOrange);
	IO_Output_Control(&ioInfo->outputsInfo.ledRed);
	IO_Output_Control(&ioInfo->outputsInfo.ledBlue);

	IO_Input_Control(&ioInfo->inputsInfo.userButton);
}

void IO_Input_Control(Input_State_t *inputState){
	inputState->currentState = HAL_GPIO_ReadPin(inputState->GPIOx, inputState->GPIO_Pin);

	if(inputState->currentState == GPIO_PIN_SET){
		if(inputState->inputStatus == INPUT_STATUS_LOW){
			if(inputState->lastState != inputState->currentState){
				inputState->lastState = inputState->currentState;
				inputState->currentTime = HAL_GetTick();
			}

			if((HAL_GetTick() - inputState->currentTime) >= inputState->debounceTime){
				inputState->inputStatus = INPUT_STATUS_HIGH;
			}
		}
	}
	else{
		inputState->lastState = inputState->currentState;
		inputState->inputStatus = INPUT_STATUS_LOW;
	}
}

void IO_Output_Control(Output_State_t *outputState){
	HAL_GPIO_WritePin(outputState->GPIOx, outputState->GPIO_Pin, outputState->pinState);
}

