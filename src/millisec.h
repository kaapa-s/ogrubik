#ifndef TIMEMS_H
#define	TIMEMS_H

#ifdef WIN32
#	include "window.h"
#else
#	include <string.h>
#	include <sys/time.h>
#endif

namespace ogrubik {

long TimeMillisec(void);

}

#endif	/* TIMEMS_H */

