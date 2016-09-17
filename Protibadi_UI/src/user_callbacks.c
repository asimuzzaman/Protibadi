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

