/*
 * messaging_port.c
 *
 *  Created on: Sep 16, 2016
 *      Author: Mansib
 */
#include "messaging_port.h"

void
message_port_cb(int local_port_id, const char *remote_app_id, const char *remote_port,
                bool trusted_remote_port, bundle *message, void *user_data)
{
    char *command = NULL;
    //char *data = NULL;
    bundle_get_str(message, "command", &command);
    //bundle_get_str(message, "data", &data);

    if(strcmp(command, "HELP") == 0) //"Ask for help" button call back
    	run_app();

    dlog_print(DLOG_INFO, LOG_TAG, "Message from %s, command: %s ",
               remote_app_id, command);
}

void message_receiver() {
	char *local_port = "test1"; //NOT SURE

	int port_id = message_port_register_local_port(local_port, message_port_cb, NULL);
	if (port_id < 0)
	    dlog_print(DLOG_ERROR, LOG_TAG, "Port register error: %d", port_id);
	else
	    dlog_print(DLOG_INFO, LOG_TAG, "port_id: %d", port_id);
}
