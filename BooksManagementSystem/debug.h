#pragma once
//#define __DEBUG__ //如果要去除调试信息请注释掉这行
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
