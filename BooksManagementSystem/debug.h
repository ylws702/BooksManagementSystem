#pragma once
//#define __DEBUG__ //���Ҫȥ��������Ϣ��ע�͵�����
#ifdef __DEBUG__
#include <stdarg.h>
void debug(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	getchar();
}
#else
void debug(const char *fmt, ...)
{
}
#endif
