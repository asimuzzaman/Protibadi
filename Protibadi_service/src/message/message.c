/*
 * message.c
 *
 *  Created on: Sep 13, 2016
 *      Author: Mansib
 */

#include "message.h"

static messages_service_h service_handle = NULL;

static void sent_msg_cb(messages_sending_result_e result, void *user_data)
{
   if (MESSAGES_SENDING_SUCCEEDED == result)
   {
      dlog_print(DLOG_DEBUG, LOG_TAG, "Message sending succeeded");
   }
   else
   {
      dlog_print(DLOG_DEBUG, LOG_TAG, "Message sending failed");
   }
}


void start_sms()
{
	int error_code;

	error_code = messages_open_service(&service_handle);

	if (error_code != MESSAGES_ERROR_NONE)
	{
	   // Error handling
		dlog_print(DLOG_ERROR, LOG_TAG, "Message opening failed");
	}
}

void sms_close_service()
{
	messages_close_service(service_handle);
	service_handle = NULL;
}

/*void app_ownership()
{
	char *app_id_string = NULL;
	if (!app_get_id(&app_id_string))
	{
	   // Use app_id_string
	   if (app_id_string != NULL)
	      free(app_id_string);
	}
}*/

void create_recipient_send(char *address, double latitude, double longitude)
{
	int error_code;
	messages_message_h msg_hndl = NULL;

	char text[100];


	sprintf(text, "Help me, my location is: Latitude = %.5lf, Longitude = %.5lf", latitude, longitude);

	dlog_print(DLOG_DEBUG, LOG_TAG, text);


	error_code = messages_create_message(MESSAGES_TYPE_SMS, &msg_hndl);
	if (error_code != MESSAGES_ERROR_NONE)
	{

		   dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to add create message");

	}

	error_code = messages_add_address(msg_hndl, *&address, MESSAGES_RECIPIENT_TO); //ADD ADDRESS
	if (error_code != MESSAGES_ERROR_NONE)
	{
	   dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to add recipient address");
	}

	error_code = messages_set_text(msg_hndl,*&text); //ADD BODY
	if (error_code != MESSAGES_ERROR_NONE)
	{
	   dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to set message text");
	}

	error_code = messages_send_message(service_handle, msg_hndl, true, sent_msg_cb, NULL);
	if (error_code != MESSAGES_ERROR_NONE)
	{
	   dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to send message");
	}

}

void run_sms(char *numbers[], int number_count, double latitude, double longitude) {
	int i;

	start_sms();

	for(i=0;i<number_count;i++) {
		create_recipient_send(numbers[i],latitude,longitude);
	}

}
