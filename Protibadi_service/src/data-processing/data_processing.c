/*
 * data_processing.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Mansib
 */
#include "data_processing.h"

static double latitude, longitude;
//const char *emails[10];
static int email_count = 0;
//const char *numbers[10];
static int number_count = 0;

void run_app() {
	run_location(&latitude,&longitude);
		dlog_print(DLOG_DEBUG, LOG_TAG, "Lat: %lf, Long: %lf", latitude, longitude);
}

