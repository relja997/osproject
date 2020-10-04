#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include <stdlib.h>
#include "Other.h"

int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	Other::lock();
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	Other::unlock();
		return res;
}
