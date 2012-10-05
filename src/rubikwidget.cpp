#include "rubikwidget.h"

namespace ogrubik {

const struct RubikWidget::rotation
RubikWidget::Rotations[Cube::NumberOfMoves] =
{
	{ Ogre::Vector3::UNIT_X, -1,  90 }, // R
	{ Ogre::Vector3::UNIT_X,  1,  90 }, // L
	{ Ogre::Vector3::UNIT_Y, -1,  90 }, // U
	{ Ogre::Vector3::UNIT_Y,  1,  90 }, // D
	{ Ogre::Vector3::UNIT_Z, -1,  90 }, // F
	{ Ogre::Vector3::UNIT_Z,  1,  90 }, // B
	{ Ogre::Vector3::UNIT_X,  1,  90 }, // Ri
	{ Ogre::Vector3::UNIT_X, -1,  90 }, // Li
	{ Ogre::Vector3::UNIT_Y,  1,  90 }, // Ui
	{ Ogre::Vector3::UNIT_Y, -1,  90 }, // Di
	{ Ogre::Vector3::UNIT_Z,  1,  90 }, // Fi
	{ Ogre::Vector3::UNIT_Z, -1,  90 }, // Bi
	{ Ogre::Vector3::UNIT_X,  1, 180 }, // R2
	{ Ogre::Vector3::UNIT_X,  1, 180 }, // L2
	{ Ogre::Vector3::UNIT_Y,  1, 180 }, // U2
	{ Ogre::Vector3::UNIT_Y,  1, 180 }, // D2
	{ Ogre::Vector3::UNIT_Z,  1, 180 }, // F2
	{ Ogre::Vector3::UNIT_Z,  1, 180 }	// B2
};

const struct RubikWidget::face
RubikWidget::Faces[Cube::NumberOfClockwiseQuarterTurnMoves] =
{
	{{ Cube::UR, Cube::DR, Cube::FR, Cube::BR }, { Cube::URF, Cube::UBR, Cube::DFR, Cube::DRB }}, // R
	{{ Cube::UL, Cube::DL, Cube::FL, Cube::BL }, { Cube::UFL, Cube::ULB, Cube::DLF, Cube::DBL }}, // L
	{{ Cube::UL, Cube::UR, Cube::UF, Cube::UB }, { Cube::URF, Cube::UBR, Cube::UFL, Cube::ULB }}, // U
	{{ Cube::DL, Cube::DR, Cube::DF, Cube::DB }, { Cube::DFR, Cube::DRB, Cube::DLF, Cube::DBL }}, // D
	{{ Cube::FU, Cube::FD, Cube::FL, Cube::FR }, { Cube::FUR, Cube::RDF, Cube::UFL, Cube::FDL }}, // F
	{{ Cube::BU, Cube::BD, Cube::BL, Cube::BR }, { Cube::UBR, Cube::BDR, Cube::BUL, Cube::DBL }}, // B
};

const struct RubikWidget::coords
RubikWidget::CornerCoords[Cube::NumberOfCornerCubies] =
{
	{ +1, +1, +1 }, // URF
	{ -1, +1, +1 }, // UFL
	{ -1, +1, -1 }, // UBL
	{ +1, +1, -1 }, // UBR
	{ +1, -1, +1 }, // DFR
	{ -1, -1, +1 }, // DLF
	{ -1, -1, -1 }, // DBL
	{ +1, -1, -1 }	// DRB
};

const struct RubikWidget::coords
RubikWidget::EdgeCoords[Cube::NumberOfEdgeCubies] =
{
	{  0, +1, +1 }, // UF
	{ -1, +1,  0 }, // UL
	{  0, +1, -1 }, // UB
	{ +1, +1,  0 }, // UR
	{  0, -1, +1 }, // DF
	{ -1, -1,  0 }, // DL
	{  0, -1, -1 }, // DB
	{ +1, -1,  0 }, // DR
	{ +1,  0, +1 }, // RF
	{ -1,  0, +1 }, // FL
	{ -1,  0, -1 }, // LB
	{ +1,  0, -1 }	// BR
};

const struct RubikWidget::coords
RubikWidget::FaceCoords[Cube::NumberOfMoves] =
{
	{ +1,  0,  0 }, // R
	{ -1,  0,  0 }, // L
	{  0, +1,  0 }, // U
	{  0, -1,  0 }, // D
	{  0,  0, +1 }, // F
	{  0,  0, -1 }	// B
};

void
RubikWidget::attach(Cube::Move face)
{
	int i = face % Cube::NumberOfClockwiseQuarterTurnMoves;
	struct face f = Faces[i];
	for (int i = 0; i < 4; i++)
	{
		Ogre::SceneNode * cubieNode = edges[f.edges[i]];
		cubieNode->getParentSceneNode()->removeChild(cubieNode);
		rotatingNode->addChild(cubieNode);
	}
	for (int i = 0; i < 4; i++)
	{
		Ogre::SceneNode * cubieNode = corners[f.corners[i]];
		cubieNode->getParentSceneNode()->removeChild(cubieNode);
		rotatingNode->addChild(cubieNode);
	}

	Ogre::SceneNode * cubieNode = faces[i];
	cubieNode->getParentSceneNode()->removeChild(cubieNode);
	rotatingNode->addChild(cubieNode);
}

void
RubikWidget::detach(Cube::Move face)
{
	int i = face % Cube::NumberOfClockwiseQuarterTurnMoves;
	struct face f = Faces[i];
	for (int i = 0; i < 4; i++)
	{
		Ogre::SceneNode * cubieNode = edges[f.edges[i]];
		cubieNode->getParentSceneNode()->removeChild(cubieNode);
		mSceneMgr->getRootSceneNode()->addChild(cubieNode);
	}
	for (int i = 0; i < 4; i++)
	{
		Ogre::SceneNode * cubieNode = corners[f.corners[i]];
		cubieNode->getParentSceneNode()->removeChild(cubieNode);
		mSceneMgr->getRootSceneNode()->addChild(cubieNode);
	}

	Ogre::SceneNode * cubieNode = faces[i];
	cubieNode->getParentSceneNode()->removeChild(cubieNode);
	mSceneMgr->getRootSceneNode()->addChild(cubieNode);
}

RubikWidget::RubikWidget() :
	OgreWidget()
{
	buttonPressed = false;
	startTime = 0;
	solving = false;
}

void RubikWidget::newCube ()
{
	kcube.BackToHome();
	showKCube();
}

void RubikWidget::scrambleCube ()
{
	for (int i = 0; i < 100; i++)
		kcube.ApplyMove(rand() % 18);
	showKCube();
}

void RubikWidget::on_size_request(Gtk::Requisition* requisition)
{
	*requisition = Gtk::Requisition();

	requisition->width = 800;
	requisition->height = 800;
}

bool RubikWidget::on_motion_notify_event(GdkEventMotion *event)
{
	if (buttonPressed) {
		mCameraYaw->yaw((Ogre::Radian) (event->x - lastX) * -0.01);
		mCameraPitch->pitch((Ogre::Radian) (event->y - lastY) * -0.01);
	}
	lastX = event->x;
	lastY = event->y;
	return true;
}

bool RubikWidget::on_button_press_event(GdkEventButton *event)
{
	buttonPressed = true;
	return true;
}

bool RubikWidget::on_button_release_event(GdkEventButton *event)
{
	buttonPressed = false;
	return true;
}

void RubikWidget::createScene()
{
	// Create the scene manager
	mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC);
	// Create the camera
	mCamera = mSceneMgr->createCamera("Camera");
	// Create one viewport, entire window
	mViewport = mRenderWindow->addViewport(mCamera);
	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) /
							Ogre::Real(mViewport->getActualHeight()));

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// setup the camera
	mCamera->setPosition(Ogre::Vector3(0, 0, 15));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5.0f);
	mCamera->setFarClipDistance(5000.0f);

	Ogre::Light * pointLight = mSceneMgr->createLight("Light");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(0, 0, 15));
	pointLight->setDiffuseColour(1, 1, 1);
	pointLight->setSpecularColour(1, 1, 1);

	mCameraYaw = mSceneMgr->createSceneNode();
	mSceneMgr->getRootSceneNode()->addChild(mCameraYaw);
	mCameraPitch = mSceneMgr->createSceneNode();
	mCameraYaw->addChild(mCameraPitch);
	mCameraPitch->attachObject(mCamera);
	mCameraPitch->attachObject(pointLight);

	rotatingNode = mSceneMgr->createSceneNode();
	mSceneMgr->getRootSceneNode()->addChild(rotatingNode);

	for (int i = 0; i < Cube::NumberOfCornerCubies; i++)
	{
		struct coords corner = CornerCoords[i];
		Ogre::SceneNode * permutationNode = corners[i] = mSceneMgr->createSceneNode();
		Ogre::SceneNode * twistNode = mSceneMgr->createSceneNode();
		Ogre::Entity * cubieEntity = mSceneMgr->createEntity("Cubie.mesh");

		mSceneMgr->getRootSceneNode()->addChild(permutationNode);
		permutationNode->setPosition(Ogre::Vector3(corner.x * 2, corner.y * 2, corner.z * 2));
		permutationNode->addChild(twistNode);
		twistNode->attachObject(cubieEntity);
	}
	for (int i = 0; i < Cube::NumberOfEdgeCubies; i++)
	{
		struct coords edge = EdgeCoords[i];
		Ogre::SceneNode * permutationNode = edges[i] = mSceneMgr->createSceneNode();
		Ogre::SceneNode * twistNode = mSceneMgr->createSceneNode();
		Ogre::Entity * cubieEntity = mSceneMgr->createEntity("Cubie.mesh");

		mSceneMgr->getRootSceneNode()->addChild(permutationNode);
		permutationNode->setPosition(Ogre::Vector3(edge.x * 2, edge.y * 2, edge.z * 2));
		permutationNode->addChild(twistNode);
		twistNode->attachObject(cubieEntity);
	}
	for (int i = 0; i < Cube::NumberOfClockwiseQuarterTurnMoves; i++)
	{
		struct coords face = FaceCoords[i];
		Ogre::SceneNode * node = faces[i] = mSceneMgr->createSceneNode();
		Ogre::Entity * cubieEntity = mSceneMgr->createEntity("Cubie.mesh");

		mSceneMgr->getRootSceneNode()->addChild(node);
		node->setPosition(Ogre::Vector3(face.x * 2, face.y * 2, face.z * 2));
		node->attachObject(cubieEntity);
	}
	showKCube();
}

void RubikWidget::showKCube()
{
	const int * edgeCubiePermutations = kcube.EdgeCubiePermutations;
	const int * edgeCubieOrientations = kcube.EdgeCubieOrientations;
	const int * cornerCubiePermutations = kcube.CornerCubiePermutations;
	const int * cornerCubieOrientations = kcube.CornerCubieOrientations;

	Ogre::SceneNode * permutationNode;
	Ogre::SceneNode * twistNode;
	Ogre::Quaternion permutation;
	Ogre::Quaternion twist;

	for (int i = 0; i < Cube::NumberOfCornerCubies; i++)
	{
		permutation = Transforms::cornerPermutations[cornerCubiePermutations[i]][i];
		twistNode = corners[i];
		twistNode->setOrientation(Ogre::Quaternion());
		permutationNode = (Ogre::SceneNode *) twistNode->getChild(0);
		permutationNode->setOrientation(Ogre::Quaternion());
		permutationNode->rotate(permutation);

		twist = Transforms::cornerClockwiseTwists[i];
		for (int j = 3; j > cornerCubieOrientations[i]; j--) {
			twistNode->rotate(twist);
		}
	}
	for (int i = 0; i < Cube::NumberOfEdgeCubies; i++)
	{
		permutation = Transforms::edgePermutations[edgeCubiePermutations[i]][i];
		twistNode = edges[i];
		twistNode->setOrientation(Ogre::Quaternion());
		permutationNode = (Ogre::SceneNode *) twistNode->getChild(0);
		permutationNode->setOrientation(Ogre::Quaternion());
		permutationNode->rotate(permutation);

		if (edgeCubieOrientations[i]) {
			twist = Transforms::edgeTwists[i];
			twistNode->rotate(twist);
		}
	}
}

void RubikWidget::showSolving()
{
	KociembaCube home;
	// if it's at the home position
	if (kcube == home) {
		signal_solved.emit();
		return;
	}
	solver.InitializeTables();
	try { solver.Solve(kcube); }
	catch (std::exception) {}

	solving = true;
}

bool RubikWidget::on_idle()
{
	if (solving)
	{
		if (startTime == 0)
		{
			startTime = TimeMillisec();
			int move = solver.solution.front();
			attach((Cube::Move) move);
			struct rotation r = Rotations[move];
			rotationAxis = r.axis;
			rotationSign = r.sign;
			degreeAmmount = r.degrees;
		}
		long currentTime = TimeMillisec();
		double rotation = (currentTime - startTime) * 90.0 / 400.0;
		if (rotation >= degreeAmmount)
			rotation = degreeAmmount;
		Ogre::Quaternion qrotation(Ogre::Degree(Ogre::Real(rotation * rotationSign)), rotationAxis);
		rotatingNode->setOrientation(Ogre::Quaternion());
		rotatingNode->rotate(qrotation);
		if (rotation == degreeAmmount)
		{
			startTime = 0;
			kcube.ApplyMove(solver.solution.front());
			detach((Cube::Move) solver.solution.front());
			solver.solution.pop_front();
			showKCube();
			if (solver.solution.empty()) {
				solving = false;
				signal_solved.emit();
			}
		}
	}

	OgreWidget::on_idle();
	return true;
}

} // namespace ogrubik
