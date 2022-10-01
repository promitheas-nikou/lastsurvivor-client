#define _CRT_SECURE_NO_WARNINGS
#include "Logging.h"
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

FILE* session_log_file;
ALLEGRO_TEXTLOG* session_allegro_textlog;

LOGGING_LEVEL current_logging_level = INFO;

const char* lsg_get_logging_level_name(LOGGING_LEVEL level)
{
	switch (level) {
	case VERBOSE:
		return "VERBOSE";
	case INFO:
		return "   INFO";
	case WARNING:
		return "WARNING";
	case ERROR:
		return "  ERROR";
	case FATAL:
		return "  FATAL";
	}
	return "UNKNOWN";
}

void lsg_set_logging_level(LOGGING_LEVEL level)
{
	current_logging_level = level;
}

LOGGING_LEVEL lsg_get_logging_level()
{
	return current_logging_level;
}

bool lsg_open_session_logfile()
{
	char fn[100];
	time_t t = time(NULL);
	strftime(fn, 100, "logs/lastsurvivor_log_%F_%H_%M_%S.log", localtime(&t));
	session_log_file = fopen(fn, "w");
	return session_log_file!=NULL;	
}

bool lsg_open_session_textlog()
{
	session_allegro_textlog = al_open_native_text_log("LAST SURVIVOR SESSION LOG", ALLEGRO_TEXTLOG_MONOSPACE);
	return session_allegro_textlog != NULL;
}

void lsg_register_textlog_event_listener(ALLEGRO_EVENT_QUEUE* queue)
{
	if (session_allegro_textlog)
		al_register_event_source(queue, al_get_native_text_log_event_source(session_allegro_textlog));
}

void lsg_write_to_session_log(LOGGING_LEVEL level, const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	time_t t = time(NULL);
	struct tm time;
	char timestr[100];
	strftime(timestr, 100, "%c", localtime(&t));
	
	char msg[400];
	vsprintf(msg, format, argp);

	if (session_log_file)
		fprintf(session_log_file, "[%s | %s] %s\n", timestr, lsg_get_logging_level_name(level), msg);
	if (session_allegro_textlog)
		if(current_logging_level<=level)
			al_append_native_text_log(session_allegro_textlog, "[%s | %s] %s\n", timestr, lsg_get_logging_level_name(level), msg);

	va_end(argp);
}

void lsg_close_session_logs()
{
	lsg_close_session_logfile();
	lsg_close_session_textlog();
}

void lsg_close_session_textlog()
{
	if (session_allegro_textlog)
	{
		al_close_native_text_log(session_allegro_textlog);
		session_allegro_textlog = NULL;
	}
}

void lsg_close_session_logfile()
{
	if (session_log_file)
	{
		fflush(session_log_file);
		fclose(session_log_file);
		session_log_file = NULL;
	}
}
