#ifndef _WINDOWHANDLE_H
#define _WINDOWHANDLE_H

#include <string.h>
#include <Ogre.h>
#include <gtkmm.h>
#include <gdkmm/drawable.h>
#include <gdkmm/general.h>

#ifdef WIN32
#	include <string>
#	include <gdk/gdkwin32.h>
#else
#	include <gdk/gdkx.h>
#endif

namespace ogrubik {

std::string ExternalWindowHandle(GdkWindow * gobj);

} // namespace ogrubik

#endif
