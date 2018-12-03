#ifndef __protibadi_service_H__
#define __protibadi_service_H__

#include <app.h>
#include <dlog.h>
#include <locations.h>
#include <messages.h>
#include <email.h>
#include <message_port.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>

#include "location_service.h"
#include "data_processing.h"
#include "message.h"
#include "messaging_port.h"
#include "emailing.h"

typedef struct appdata {
	sqlite3 *db;
	char *current_key;
} appdata_s;

typedef struct recdata {
	char key[10];
	char name[255];
	char phone[30];
	char email[60];
} recdata_s;

appdata_s *m_ad; //GLOBAL variable for application data

const char *emails[10]; //
static int email_count = 0; //
const char *numbers[10]; //
static int number_count = 0; //

void init_db(appdata_s *ad);

void add_contact(unsigned char *name, unsigned char *number, unsigned char *email);

void list_contacts(int *num_count, int *mail_count, char *numbers[], char *emails[]);

/*implementation of PRINT_MSG function
 * #define PRINT_MSG(fmt, args...) do { char _log_[_PRINT_MSG_LOG_BUFFER_SIZE_]; \
    snprintf(_log_, _PRINT_MSG_LOG_BUFFER_SIZE_, fmt, ##args); _add_entry_text(_log_); } while (0)

void _add_entry_text(const char *text);*/

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "protibadi_service"


#endif /* __protibadi_service_H__ */
