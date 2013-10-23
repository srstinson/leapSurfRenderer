// ObjRenderer.h: interface for the ObjRenderer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GEOHASH_OBJRENDERER_
#define _GEOHASH_OBJRENDERER_

#include "StdAfx.h"

#define CALLBACK_ADD_SPHERE 3000
#define CALLBACK_ADD_CUBE   3001
#define CALLBACK_DRAW_AXES 100


class SphereLattice;

class ObjRenderer  
{
public:
	ObjRenderer();
	virtual ~ObjRenderer();
	static int main_window;		///Return pathway for GLUI to OpenGL Rendering Window

	////Glut Callbacks
	static void init(void);
	static void idle(void);
	static void display(void);
	static void reshape(int w, int h);

	//Keyboard input callbacks
	static void normalKeys(unsigned char key, int x, int y);
	static void processMouse(int button, int state, int x, int y);

	//Picking callbacks and functions
	static void pickObjects(int x, int y);
	static void processHits(GLint hits, GLuint buffer[]);

	//Rendering Functions and callback
	static void render(int mode);
	static void beginRendering(SurfaceObject * s);

	//GLUI activators and callback
	static void setUpGLUI(void);
	static void controlCB(int control);

	//GLUI windows
	static GLUI * glui_controls;
	static GLUI_EditText * glui_input_file_field;
	static GLUI_EditText * glui_output_file_field;

	//Live variables for GLUI and other User Interface
	//viewing controls
	static float * obj_pos;
	static float * obj_rot;
	static int * drawAxes;
	static float aspectRatio;

	//rendering options
	static char * outputFileName;
	static SurfaceObject * surf;
	static int * drawSurf;
	static int * surfTrans;

	//point-based rendering
	static set_t drawSphere;		//int ** [1] draw yes/no
	static set_t transSphere;		//int ** [1] transparent yes/no
	static set_t spheres;			//float ** coordinates
	static set_t radii;
	static int background;

	static void addSphere();

	//point-based rendering
	static set_t drawCube;		//int ** [1] draw yes/no
	static set_t transCube;		//int ** [1] transparent yes/no
	static set_t cubes;			//float ** coordinates
	static set_t cubeSize;
	static void renderCubes(int transparent);

	static void addCube();

	static void changeBackGround();
};

#endif


