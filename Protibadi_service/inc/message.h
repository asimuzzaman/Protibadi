/*
 * message.h
 *
 *  Created on: Sep 13, 2016
 *      Author: Mansib
 */
#include "protibadi_service.h"

#ifndef MESSAGE_H_
#define MESSAGE_H_

void run_sms(char *numbers[], int number_count, double latitude, double longitude);
void sms_close_service();

#endif /* MESSAGE_H_ */
