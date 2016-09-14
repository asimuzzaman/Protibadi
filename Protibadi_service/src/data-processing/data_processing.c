/*
 * data_processing.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Mansib
 */
#include "data_processing.h"

static double latitude, longitude;
const char *emails[10];
static int email_count = 2;
const char *numbers[10];
static int number_count = 2;

void run_app() {
	run_location(&latitude,&longitude);
		dlog_print(DLOG_DEBUG, LOG_TAG, "Lat: %lf, Long: %lf", latitude, longitude);

	numbers[0] = "01552333083";
	numbers[1] = "01521218382";
	emails[0] = "fiasco.farah@gmail.com";
	emails[1] = "mansib.raj@gmail.com";

	run_sms(numbers, number_count, latitude, longitude);

	location_close_service();
	sms_close_service();

	free(emails);
	free(numbers)
}
