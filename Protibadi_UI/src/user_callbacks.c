/*
 * user_callbacks.c
 *
 *  Created on: Sep 17, 2016
 *      Author: Mansib
 */
#include "user_callbacks.h"

void ask_for_help() {
	bundle *b = bundle_create ();
	bundle_add_str (b, "command", "HELP");

	send_message_port(b);
}

void btn_add_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	char* s_name = elm_object_text_get(ad->entry1);
	char* s_number = elm_object_text_get(ad->entry2);
	char* s_email = elm_object_text_get(ad->entry3);

	bundle *b = bundle_create();
	bundle_add_str(b,"command","ADD_CONTACT");
	bundle_add_str(b,"name", s_name);
	bundle_add_str(b,"number", s_number);
	bundle_add_str(b,"email", s_email);

	send_message_port(b); //send new contact to service app

	//dlog_print(DLOG_DEBUG,LOG_TAG,"Input: %s, %s, %s.",s_name,s_number,s_email);
}

void launch_service_app() {
	/*app_control_h app_control;

	if (app_control_create(&app_control)== APP_CONTROL_ERROR_NONE) 	{
		//Setting an app ID.
		if (app_control_set_app_id(app_control, "org.example.protibadi_service") == APP_CONTROL_ERROR_NONE)
		{
			if(app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE)
			{
				dlog_print(DLOG_DEBUG,LOG_TAG,"App launch request sent!");
			}
		}

		if (app_control_destroy(app_control) == APP_CONTROL_ERROR_NONE)
		{
			dlog_print(DLOG_DEBUG,LOG_TAG,"App control destroyed");
		}
	}*/

	app_control_h app_control;
	if (app_control_create(&app_control)== APP_CONTROL_ERROR_NONE)
	{
	//Setting an app ID.
	    if (app_control_set_app_id(app_control, "org.example.protibadi_service") == APP_CONTROL_ERROR_NONE)
	    {
	        if(app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE)
	        {
	        	dlog_print(DLOG_DEBUG,LOG_TAG,"App launch request sent!");
	        }
	    }
	    if (app_control_destroy(app_control) == APP_CONTROL_ERROR_NONE)
	    {
	    	dlog_print(DLOG_DEBUG,LOG_TAG,"App control destroyed");
	    }
	}
}
