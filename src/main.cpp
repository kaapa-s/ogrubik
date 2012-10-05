#include <gtkmm.h>
#include <Ogre.h>

#include "rubikwidget.h"

void OnNewClicked ();
void OnScrambleClicked ();
void OnSolveClicked ();
void OnCubeSolved ();

Gtk::Button * bNew;
Gtk::Button * bScramble;
Gtk::Button * bSolve;
ogrubik::RubikWidget * widget;

int main (int argc, char * argv[])
{
	Ogre::Root * ogre = new Ogre::Root();
	// TODO don't show this dialog
	ogre->showConfigDialog();
	ogre->initialise(false);

	Gtk::Window * window;
	Gtk::Box * box;
	Gtk::Main kit(argc, argv);
	// TODO adjust the interface
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("window.glade");
	builder->get_widget("window", window);
	builder->get_widget("box", box);
	builder->get_widget("button_new_cube", bNew);
	builder->get_widget("button_scramble_cube", bScramble);
	builder->get_widget("button_solve_cube", bSolve);
	bNew->signal_clicked().connect(sigc::ptr_fun(OnNewClicked));
	bScramble->signal_clicked().connect(sigc::ptr_fun(OnScrambleClicked));
	bSolve->signal_clicked().connect(sigc::ptr_fun(OnSolveClicked));
	// setup and insert the custom widget into the window
	widget = new ogrubik::RubikWidget();
	widget->signal_solved.connect(sigc::ptr_fun(OnCubeSolved));
	box->pack_start(*widget);
	// run until the window is closed
	window->show_all();
	kit.run(*window);

	delete ogre;
	delete window;

	return 0;
}

void OnNewClicked ()
{
	widget->newCube();
}

void OnScrambleClicked ()
{
	widget->scrambleCube();
}

void OnSolveClicked ()
{
	bNew->set_sensitive(false);
	bScramble->set_sensitive(false);
	bSolve->set_sensitive(false);

	widget->showSolving();
}

void OnCubeSolved ()
{
	bNew->set_sensitive(true);
	bScramble->set_sensitive(true);
	bSolve->set_sensitive(true);
}
