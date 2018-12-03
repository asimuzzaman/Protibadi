/*
 * data_processing.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Mansib
 */
#include "data_processing.h"

void run_app() {
	run_location(&latitude,&longitude);
		dlog_print(DLOG_DEBUG, LOG_TAG, "Lat: %lf, Long: %lf", latitude, longitude);

	list_contacts(&number_count, &email_count, numbers, emails);
	int i;
	for (i = 0; i < number_count; ++i) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "CONTENT: %s, %s", numbers[i], emails[i]);
	}

	run_sms(numbers, number_count, latitude, longitude);

	//run_email(emails,email_count,latitude,longitude);

	location_close_service();
	sms_close_service();
	//add email close service here
}
/*
 * data_processing.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Mansib
 */
#include "data_processing.h"

void run_app() {
	run_location(&latitude,&longitude);
		dlog_print(DLOG_DEBUG, LOG_TAG, "Lat: %lf, Long: %lf", latitude, longitude);

	list_contacts(&number_count, &email_count, numbers, emails);
	int i;
	for (i = 0; i < number_count; ++i) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "CONTENT: %s, %s", numbers[i], emails[i]);
	}

	run_sms(numbers, number_count, latitude, longitude);

	//run_email(emails,email_count,latitude,longitude);

	location_close_service();
	sms_close_service();
	//add email close service here
}
