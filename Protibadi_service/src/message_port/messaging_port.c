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

    dlog_print(DLOG_INFO, LOG_TAG, "Message from %s, command: %s ",
               remote_app_id, command);

    if(strcmp(command, "HELP") == 0) //"Ask for help" button call back
        run_app(); //calling Data Processor function

    else if(strcmp(command,"ADD_CONTACT") == 0) { //adding contact in the database
        char *name = NULL, *number = NULL, *email = NULL;

        bundle_get_str(message, "name", &name);
        bundle_get_str(message, "number", &number);
        bundle_get_str(message, "email", &email);

        dlog_print(DLOG_DEBUG,LOG_TAG,"Received: %s, %s, %s.",name,number,email);
        add_contact(name, number, email);
    }

}

void message_receiver() {
    char *local_port = "test1"; //port for UI app

    int port_id = message_port_register_local_port(local_port, message_port_cb, NULL);
    if (port_id < 0)
        dlog_print(DLOG_ERROR, LOG_TAG, "Port register error: %d", port_id);
    else
        dlog_print(DLOG_INFO, LOG_TAG, "port_id: %d", port_id);
}
