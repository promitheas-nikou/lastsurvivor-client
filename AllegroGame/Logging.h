#pragma once
#include <allegro5/allegro5.h>

enum LOGGING_LEVEL {VERBOSE=1, INFO=2, WARNING=3, ERROR=4, FATAL=5};

const char* lsg_get_logging_level_name(LOGGING_LEVEL level);

void lsg_set_logging_level(LOGGING_LEVEL level);
LOGGING_LEVEL lsg_get_logging_level();

bool lsg_open_session_logfile();
bool lsg_open_session_textlog();

void lsg_register_textlog_event_listener(ALLEGRO_EVENT_QUEUE* queue);

void lsg_write_to_session_log(LOGGING_LEVEL level, const char* format, ...);
void lsg_close_session_logs();
void lsg_close_session_textlog();
void lsg_close_session_logfile();
