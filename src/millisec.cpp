#include "millisec.h"

namespace ogrubik {

#ifdef WIN32

long TimeMillisec(void)
{
	// TODO
	return 0;
}

#else

long TimeMillisec(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

#endif

}
