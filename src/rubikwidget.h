#ifndef _RUBIKWIDGET_H
#define _RUBIKWIDGET_H

#include "ogrewidget.h"
#include "windowhandle.h"
#include "transforms.h"
#include "millisec.h"
#include "kcube/kocicube.h"
#include "kcube/solver.h"

#include <string>
#include <cstdlib>
#include <Ogre.h>
#include <exception>

namespace ogrubik
{

class RubikWidget : public OgreWidget
{
public:
	RubikWidget();

	void newCube();
	void scrambleCube();

	void showKCube();
	void showSolving();

	sigc::signal<void> signal_solved;

private:
	struct rotation {
		Ogre::Vector3 axis;
		int sign;
		int degrees;
	};
	struct face {
		Cube::EdgeCubie edges[4];
		Cube::CornerCubie corners[4];
	};
	struct coords {
		int x;
		int y;
		int z;
	};
	static const struct rotation Rotations[Cube::NumberOfMoves];
	static const struct face Faces[Cube::NumberOfClockwiseQuarterTurnMoves];
	static const struct coords CornerCoords[Cube::NumberOfCornerCubies];
	static const struct coords EdgeCoords[Cube::NumberOfEdgeCubies];
	static const struct coords FaceCoords[Cube::NumberOfMoves];

	void on_size_request(Gtk::Requisition* requisition);
	bool on_motion_notify_event(GdkEventMotion * event);
	bool on_button_press_event(GdkEventButton * event);
	bool on_button_release_event(GdkEventButton * event);
	void createScene();

	// The animation take place there
	bool on_idle();

	void attach(Cube::Move face);
	void detach(Cube::Move face);

	KociembaCube kcube;
	Solver solver;

	Ogre::SceneManager * mSceneMgr;
	Ogre::Viewport * mViewport;
	Ogre::SceneNode * mCameraYaw;
	Ogre::SceneNode * mCameraPitch;
	Ogre::SceneNode * corners[Cube::NumberOfCornerCubies];
	Ogre::SceneNode * edges[Cube::NumberOfEdgeCubies];
	Ogre::SceneNode * faces[Cube::NumberOfClockwiseQuarterTurnMoves];

	Ogre::SceneNode * rotatingNode;
	Ogre::Vector3 rotationAxis;
	int rotationSign;
	int degreeAmmount;
	bool buttonPressed;
	double lastX, lastY;
	long startTime;
	bool solving;
};

} // namespace ogrubik

#endif
