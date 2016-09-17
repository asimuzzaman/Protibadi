#ifndef __protibadi_v2_H__
#define __protibadi_v2_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <message_port.h> //message_port

#include "messaging_port.h"
#include "user_callbacks.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "protibadi_v2"

#if !defined(PACKAGE)
#define PACKAGE "org.example.protibadi_v2"
#endif

#endif /* __protibadi_v2_H__ */
