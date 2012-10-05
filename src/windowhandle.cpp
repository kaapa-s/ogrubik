#include "windowhandle.h"

namespace ogrubik {

#ifdef WIN32

std::string ExternalWindowHandle(GdkWindow * gobj)
{
	return Ogre::StringConverter::toString((unsigned long) GDK_WINDOW_HWND(gobj));
}

#else

std::string ExternalWindowHandle(GdkWindow * gobj)
{
	GdkDisplay* display = gdk_drawable_get_display(GDK_DRAWABLE(gobj));
	GdkScreen* screen = gdk_drawable_get_screen(GDK_DRAWABLE(gobj));

	Display* xdisplay = GDK_DISPLAY_XDISPLAY(display);
	Screen* xscreen = GDK_SCREEN_XSCREEN(screen);
	int screen_number = XScreenNumberOfScreen(xscreen);
	XID xid_parent = GDK_WINDOW_XWINDOW(gobj);

	std::string externalWindowHandle =
		Ogre::StringConverter::toString(reinterpret_cast<unsigned long>(xdisplay)) + ":" +
		Ogre::StringConverter::toString(static_cast<unsigned int>(screen_number)) + ":" +
		Ogre::StringConverter::toString(static_cast<unsigned long>(xid_parent));

	return externalWindowHandle;
}

#endif

}
