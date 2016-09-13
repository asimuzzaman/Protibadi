/*
 * location_service.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Mansib
 */

#include "location_service.h"


location_service_state_e state_;
location_manager_h manager = NULL;

/* Called when the service state changes */
static void __state_changed_cb(location_service_state_e state, void *user_data)
{
    /*PRINT_MSG("__state_changed_cb new state: %s", state == LOCATIONS_SERVICE_ENABLED ?
              "LOCATIONS_SERVICE_ENABLED" : "LOCATIONS_SERVICE_DISABLED");*/
    dlog_print(DLOG_DEBUG, LOG_TAG, "__state_changed_cb %s\n", state == LOCATIONS_SERVICE_ENABLED ?
               "LOCATIONS_SERVICE_ENABLED" : "LOCATIONS_SERVICE_DISABLED");
    state_ = state;

    /* Get the current location information */
    double altitude, latitude, longitude, climb, direction, speed;
    double horizontal, vertical;
    location_accuracy_level_e level;
    time_t timestamp;
    int ret = 0;

    if (state == LOCATIONS_SERVICE_ENABLED) {
        ret = location_manager_get_location(manager, &altitude, &latitude, &longitude,
                                            &climb, &direction, &speed, &level,
                                            &horizontal, &vertical, &timestamp);
        if (LOCATIONS_ERROR_NONE != ret) {
            /*PRINT_MSG("Error %s",
                      (LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE ==
                       ret) ? "LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE" : "Other error");*/
        }

        /*PRINT_MSG("Current location: A:%f La:%f Lo:%f ", altitude, latitude, longitude);*/
        dlog_print(DLOG_DEBUG, LOG_TAG, "Current location: A:%f La:%f Lo:%f",
                   altitude, latitude, longitude);
    }
}

void _location_init(void)
{
    bool is_enabled = false;
    int ret = location_manager_is_enabled_method(LOCATIONS_METHOD_HYBRID, &is_enabled);
    if (LOCATIONS_ERROR_NONE != ret) {
        /*PRINT_MSG("location_manager_is_enabled_method failed : %d", ret);*/
        dlog_print(DLOG_ERROR, LOG_TAG, "location_manager_is_enabled_method failed : %d", ret);
        return;
    }

    if (true != is_enabled) {
        state_ = LOCATIONS_SERVICE_DISABLED;
        /*PRINT_MSG
        ("Location service is disabled. Please switch it on and tap \"Initialize location service\" button.");*/
        return;
    }

    state_ = LOCATIONS_SERVICE_ENABLED;
    /* Create a location manager handle */
    ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
    if (LOCATIONS_ERROR_NONE != ret) {
        /*PRINT_MSG("location_manager_create failed : %d", ret);*/
        dlog_print(DLOG_ERROR, LOG_TAG, "location_manager_create failed : %d", ret);
        return;
    }

    /*PRINT_MSG("location_manager_create success");*/
    dlog_print(DLOG_ERROR,LOG_TAG,"location_manager_create_success");

    /* To know when the service becomes enabled */
    ret = location_manager_set_service_state_changed_cb(manager, __state_changed_cb, NULL);
    if (LOCATIONS_ERROR_NONE != ret) {
        /*PRINT_MSG("location_manager_set_service_state_changed_cb failed : %d", ret);*/
        dlog_print(DLOG_ERROR, LOG_TAG, "location_manager_set_service_state_changed_cb failed : %d", ret);
    }

    /* Start the location service */
    ret = location_manager_start(manager);
    if (LOCATIONS_ERROR_NONE != ret) {
        /*PRINT_MSG("location_manager_start failed : %d", ret);*/
        dlog_print(DLOG_ERROR, LOG_TAG, "location_manager_start failed : %d", ret);
        return;
    }

    /*PRINT_MSG("location_manager_start success");*/
    dlog_print(DLOG_ERROR, LOG_TAG, "location_manager_start success");
    /*PRINT_MSG("Wait for state LOCATIONS_SERVICE_ENABLED...");*/
    //elm_object_disabled_set(start, EINA_TRUE);
    //elm_object_disabled_set(stop, EINA_FALSE);
}

/* Get the Last Known Location */
//void _get_last_location_cb(appdata_s *ad, Evas_Object *obj, void *event_info)
//void _get_last_location_cb()
void _get_last_location_cb(double *lat, double *longt)
{
    if (state_ != LOCATIONS_SERVICE_ENABLED) {
        /*PRINT_MSG("state is not LOCATIONS_SERVICE_ENABLED");*/
        dlog_print(DLOG_ERROR, LOG_TAG, "state is not LOCATIONS_SERVICE_ENABLED");
        return;
    }

    int ret = 0;
    /*PRINT_MSG("_get_last_location_cb");*/
    dlog_print(DLOG_DEBUG, LOG_TAG, "_get_last_location_cb");

    double altitude = 0, latitude = 0, longitude = 0, climb = 0, direction = 0, speed = 0;
    double horizontal = 0, vertical = 0;
    location_accuracy_level_e level;
    time_t timestamp;
    /* Get the last location information including altitude, latitude, and direction */
    ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude,
            &climb, &direction, &speed, &level, &horizontal,
            &vertical, &timestamp);
    if (LOCATIONS_ERROR_NONE != ret) {
        dlog_print(DLOG_ERROR, LOG_TAG, "location_manager_get_last_location failed : %d", ret);
        /*PRINT_MSG("location_manager_get_last_location failed : %d", ret);*/
    } else {
        /*PRINT_MSG("Last location: A:%f La:%f Lo:%f ", altitude, latitude, longitude);*/

        dlog_print(DLOG_DEBUG, LOG_TAG, "Last location: A:%f La:%f Lo:%f",
                   altitude, latitude, longitude);
    }
    *lat = latitude;
    *longt = longitude;
}

void location_close_service() {
	location_manager_destroy(manager);
}

void run_location(double *latitude, double *longitude) {
	_location_init();
	_get_last_location_cb(latitude, longitude);
	//ADD LOCATION DESTROY FUNCTION HERE
}
