/*
 * emailing.c
 *
 *  Created on: Sep 17, 2016
 *      Author: Mansib
 */
#include "emailing.h"

static email_h msg;

create_message(double latitude, double longitude){
	int error_code = EMAILS_ERROR_NONE;
	error_code = email_create_message(&msg);
	char body[] = "Help me, my current location is:\nLatitude = ";
	char *subject_body = "Help!";

	char lat[10], longt[10];

	char body2[150];
	sprintf(body2, "Help me, my current location is:\n https://maps.google.com/maps?q=%.6lf,%.6lf&hl=es;z=14", latitude, longitude);

	sprintf(lat,"%.5lf",latitude);
	sprintf(longt,"%.5lf",longitude);

	strcat(body,lat);
	strcat(body,", Longitude = ");
	strcat(body,longt);

	//dlog_print(DLOG_DEBUG, LOG_TAG, body);
	//email_set_body(msg, "My location is %lf", alt);

	if (error_code != EMAILS_ERROR_NONE) {
		dlog_print(DLOG_INFO, LOG_TAG, "Failed to create email message\n");
	}
	int fuzzywuzzy = email_set_body(msg, *&body2);
	if (fuzzywuzzy != EMAILS_ERROR_NONE) {
			dlog_print(DLOG_INFO, LOG_TAG, "Failed to create email message AGAIN!\n");
	}
	int subject = email_set_subject(msg, *&subject_body);
		if (subject != EMAILS_ERROR_NONE) {
				dlog_print(DLOG_INFO, LOG_TAG, "Failed to create email subject text\n");
	}

}

add_recipients(char *recipient){
	//int error_code = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO, "mansib.raj@gmail.com");
	int error_code = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO,*&recipient);
	if (error_code != EMAILS_ERROR_NONE){
	    dlog_print(DLOG_INFO, LOG_TAG, "Failed to add recipient\n");
	}
}

/*add_attachments(){
	int error_code = email_add_attach(msg, "/opt/usr/apps/org.example.media/data/record.WAV");
	if (error_code != EMAILS_ERROR_NONE) {
	    dlog_print(DLOG_INFO, LOG_TAG, "Failed to add attachment\n");
	}
}*/

save_email(){
	int error_code = email_save_message(msg);
	if (error_code != EMAILS_ERROR_NONE){
		dlog_print(DLOG_INFO, LOG_TAG, "Failed to save email\n");
	}
}


email_send_status(email_h email, email_sending_e result, void *user_data)
{
	if (result == EMAIL_SENDING_FAILED) {
		/* Error handling */
		dlog_print(DLOG_INFO, LOG_TAG, "Failed to send email\n");
	} else if (result == EMAIL_SENDING_SUCCEEDED) {
		/* Sending was successful */
		dlog_print(DLOG_INFO, LOG_TAG, "Email sending finished with success\n");
	}
}

sending_status_calback(){
	int error_code = email_set_message_sent_cb(msg, email_send_status, NULL);
	if (error_code != EMAILS_ERROR_NONE) {
	    dlog_print(DLOG_INFO, LOG_TAG, "Failed to set sending status callback\n");
	}
}

send_email(){
	int error_code = email_send_message(msg, false);
		if (error_code != EMAILS_ERROR_NONE){
	    dlog_print(DLOG_INFO, LOG_TAG, "NOOOO!!!");
	}
}

void run_email(char *emails[], int email_count, double latitude, double longitude) {
	int i;

	create_message(latitude,longitude);

	for(i=0;i<email_count;i++) {
		add_recipients(emails[i]);
	}

	save_email();
	sending_status_calback();
	send_email();
}
