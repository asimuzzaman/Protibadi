/*
 * messaging_port.c
 *
 *  Created on: Sep 17, 2016
 *      Author: Mansib
 */
#include "messaging_port.h"

static char *remote_app_id = "org.example.protibadi_service";
static char *remote_port = "test1";

bool test_check_remote_port()
{
   int ret;
   bool found;

   ret = message_port_check_remote_port (remote_app_id, remote_port, &found);
   if (ret != MESSAGE_PORT_ERROR_NONE)
   {
      dlog_print(DLOG_ERROR, LOG_TAG, "message_port_check_remote_port error : %d", ret);
   }
   return found;
}

void send_message_port(bundle *b)
{
	if (test_check_remote_port()) {
		dlog_print(DLOG_INFO, LOG_TAG, "port is found");
	} else {
		dlog_print(DLOG_INFO, LOG_TAG, "port is not found");
	}

   int ret;
   /*bundle *b = bundle_create ();
   bundle_add_str (b, "command", "begin");
   bundle_add_str (b, "data", "dummy");*/

   ret = message_port_send_message (remote_app_id, remote_port, b);
   if (ret != MESSAGE_PORT_ERROR_NONE)
   {
      dlog_print(DLOG_ERROR, LOG_TAG,  " (Sending failed) message_port_check_remote_port error : %d", ret);
   }
   else
   {
      dlog_print(DLOG_INFO, LOG_TAG, "Send message done");
   }
   bundle_free (b);
}
