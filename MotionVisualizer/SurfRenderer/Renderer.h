// Renderer.h: interface for the Renderer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GEOHASH_RENDERER_
#define _GEOHASH_RENDERER_

#include "StdAfx.h"

#define CALLBACK_FILE_OUTPUT 1000
#define CALLBACK_FILE_INPUT 2000
#define CALLBACK_BACKGROUND_CHANGE 4000
#define CALLBACK_CENTERING 5000

#define MAX_OBJECTS 30

class SphereLattice;

class Renderer  
{
public:
	Renderer();
	virtual ~Renderer();
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
	static void beginRendering(PocketAlignment * palign);

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
	static int * useCentroid;
	static float aspectRatio;


	//rendering options
	static char * outputFileName;
	static char * inputFileName;

	//point-based rendering
//	static int numProts;
	static set_t drawProt;		//int ** drawProt;
	static set_t lists;			//AtomList ** lists;
	static set_t list_pos;		//float ** list_pos;
	static set_t list_rot;		//float ** list_rot;

	///surface-based rendering
//	static int numSurfs;
	static set_t drawSurf;		//int ** drawSurf;
	static set_t transSurf;		//int ** transSurf;
	static set_t surfs;			//SurfaceObject ** surfs;
	static set_t surf_pos;		//float ** surf_pos;
	static set_t surf_rot;		//float ** surf_rot;
	static double * centroid;	///double * centroid
	
	static void addProt(char * fn);
	static void addSurf(char * fn);
	static void addStruct(char * fn);
	static void addStruct(SurfaceObject * surf, float * pos, float * rot, char * fn);
	static void addStruct(AtomList * list, float * pos, float * rot, char * fn);
	static void changeBackGround();
	static int background;

};

#endif


