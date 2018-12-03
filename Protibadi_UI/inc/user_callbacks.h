/*
 * user_callbacks.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Mansib
 */
#include "protibadi_v2.h"
#include <app_control.h>

#ifndef USER_CALLBACKS_H_
#define USER_CALLBACKS_H_

void ask_for_help(); //send service app HELP signal

void btn_add_cb(void *data, Evas_Object *obj, void *event_info); //send service app new contact info

void launch_service_app(); //launch service app

#endif /* USER_CALLBACKS_H_ */
