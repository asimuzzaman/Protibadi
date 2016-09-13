/*
 * location_service.h
 *
 *  Created on: Sep 12, 2016
 *      Author: Mansib
 */

#ifndef LOCATION_SERVICE_H_
#define LOCATION_SERVICE_H_

#include "protibadi_service.h"

void location_close_service();
void run_location(double *latitude, double *longitude);

#endif /* LOCATION_SERVICE_H_ */
