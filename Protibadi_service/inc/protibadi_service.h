#ifndef __protibadi_service_H__
#define __protibadi_service_H__

#include <dlog.h>
#include <locations.h>

#include "location_service.h"
#include "data_processing.h"

/*implementation of PRINT_MSG function
 * #define PRINT_MSG(fmt, args...) do { char _log_[_PRINT_MSG_LOG_BUFFER_SIZE_]; \
    snprintf(_log_, _PRINT_MSG_LOG_BUFFER_SIZE_, fmt, ##args); _add_entry_text(_log_); } while (0)

void _add_entry_text(const char *text);*/

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "protibadi_service"


#endif /* __protibadi_service_H__ */
