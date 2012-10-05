#ifndef _OGREWIDGET_H
#define _OGREWIDGET_H

#include "windowhandle.h"

#include <string>
#include <gtkmm.h>
#include <glibmm/timer.h>
#include <Ogre.h>

namespace ogrubik {

class OgreWidget : public Gtk::Widget
{
public:
	OgreWidget();
	virtual ~OgreWidget();

protected:
	virtual void createScene() = 0;

	virtual bool on_motion_notify_event(GdkEventMotion * event) = 0;
	virtual bool on_button_press_event(GdkEventButton * event) = 0;
	virtual bool on_button_release_event(GdkEventButton * event) = 0;
	virtual bool on_idle();

	virtual void on_size_allocate(Gtk::Allocation& allocation);
	virtual void on_map();
	virtual void on_unmap();
	virtual void on_realize();
	virtual void on_unrealize();
	virtual bool on_expose_event(GdkEventExpose* event);

	Ogre::RenderWindow * mRenderWindow;
	Ogre::Camera * mCamera;
private:
	Glib::RefPtr<Gdk::Window> mRefGdkWindow;
};

} // namespace ogrubik

#endif
