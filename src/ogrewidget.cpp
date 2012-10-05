#include "ogrewidget.h"

namespace ogrubik {

OgreWidget::OgreWidget() :
	Glib::ObjectBase("grubik::OgreWidget"),
	Gtk::Widget()
{
	set_flags(Gtk::NO_WINDOW);
	mRenderWindow = NULL;
}

OgreWidget::~OgreWidget()
{
}

void OgreWidget::on_size_allocate(Gtk::Allocation& allocation)
{
	set_allocation(allocation);

	if(mRefGdkWindow)
	{
		mRefGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
								   allocation.get_width(), allocation.get_height());
	}

	if (mRenderWindow)
	{
		mRenderWindow->windowMovedOrResized();
		mCamera->setAspectRatio(Ogre::Real(allocation.get_width()) / Ogre::Real(allocation.get_height()));
		on_expose_event(NULL);
	}
}

void OgreWidget::on_map()
{
	//Call base class:
	Gtk::Widget::on_map();
}

void OgreWidget::on_unmap()
{
	//Call base class:
	Gtk::Widget::on_unmap();
}

void OgreWidget::on_realize()
{
	//Call base class:
	Gtk::Widget::on_realize();

	Gtk::Allocation allocation = get_allocation();

	if(!mRefGdkWindow)
	{
		//Create the GdkWindow:
		GdkWindowAttr attributes;
		memset(&attributes, 0, sizeof(attributes));

		//Set initial position and size of the Gdk::Window:
		attributes.x = allocation.get_x();
		attributes.y = allocation.get_y();
		attributes.width = allocation.get_width();
		attributes.height = allocation.get_height();

		attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK | Gdk::ALL_EVENTS_MASK ;
		attributes.window_type = GDK_WINDOW_CHILD;
		attributes.wclass = GDK_INPUT_OUTPUT;

		mRefGdkWindow = Gdk::Window::create(get_window(), &attributes, GDK_WA_X | GDK_WA_Y);
	}

	if (!mRenderWindow)
	{
		Ogre::NameValuePairList params;
		params["FSAA"] = "2";
		params["externalWindowHandle"] = ExternalWindowHandle(mRefGdkWindow->gobj());

		mRenderWindow = Ogre::Root::getSingleton().createRenderWindow("Gtk+Ogre Widget",
			allocation.get_width(), allocation.get_height(), false, &params);
		mRenderWindow->setAutoUpdated(false);
		unset_flags(Gtk::NO_WINDOW);
		set_window(mRefGdkWindow);
		set_double_buffered(true);
		//make the widget receive expose events
		mRefGdkWindow->set_user_data(gobj());
		mRefGdkWindow->set_back_pixmap(Glib::RefPtr<Gdk::Pixmap>(),false);

		createScene();
		// Start idle function for frame update/rendering
		Glib::signal_idle().connect( sigc::mem_fun(*this, &OgreWidget::on_idle) );
	}
}

void OgreWidget::on_unrealize()
{
	mRefGdkWindow.clear();
	//Call base class:
	Gtk::Widget::on_unrealize();
}

bool OgreWidget::on_expose_event(GdkEventExpose* event)
{
	if (mRenderWindow)
	{
		Ogre::Root::getSingletonPtr()->_fireFrameStarted();
		mRenderWindow->update();
		Ogre::Root::getSingletonPtr()->_fireFrameEnded();
	}
	return true;
}

bool OgreWidget::on_idle()
{
	on_expose_event(0);
	return true;
}

} // namespace ogrubik
