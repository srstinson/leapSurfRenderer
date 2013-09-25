// Renderer.cpp: implementation of the Renderer class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjRenderer.h"
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int ObjRenderer::main_window;		///referenced by GLUI to get back to the main window

//GLUI windows
GLUI * ObjRenderer::glui_controls;
float ObjRenderer::aspectRatio;
float * ObjRenderer::obj_pos;
float * ObjRenderer::obj_rot;
int * ObjRenderer::drawAxes;
GLUI_EditText * ObjRenderer::glui_input_file_field;
GLUI_EditText * ObjRenderer::glui_output_file_field;

///my stuff
char * ObjRenderer::outputFileName;
SurfaceObject * ObjRenderer::surf;
int * ObjRenderer::drawSurf;
int * ObjRenderer::surfTrans;


//	static int numProts;
set_t ObjRenderer::drawSphere;		//int ** do we draw them or not;
set_t ObjRenderer::transSphere;		//float ** are they transparent or not;
set_t ObjRenderer::spheres	;		//float ** location of the spheres
set_t ObjRenderer::radii;

set_t ObjRenderer::drawCube;		//int ** do we draw them or not;
set_t ObjRenderer::transCube;		//float ** are they transparent or not;
set_t ObjRenderer::cubes	;		//float ** location of the spheres
set_t ObjRenderer::cubeSize;

int ObjRenderer::background;


ObjRenderer::ObjRenderer()
{
	obj_pos = new float[3];
	obj_pos[0] = 0.0;
	obj_pos[1] = 0.0;
	obj_pos[2] = 0.0;

	obj_rot = new float[16];
	obj_rot[0] = 1.0;	obj_rot[1] = 0.0;	obj_rot[2] = 0.0;	obj_rot[3] = 0.0;
	obj_rot[4] = 0.0;	obj_rot[5] = 1.0;	obj_rot[6] = 0.0;	obj_rot[7] = 0.0;
	obj_rot[8] = 0.0;	obj_rot[9] = 0.0;	obj_rot[10] = 1.0;	obj_rot[11] = 0.0;
	obj_rot[12] = 0.0;	obj_rot[13] = 0.0;	obj_rot[14] = 0.0;	obj_rot[15] = 1.0;

	drawAxes = new int[1]; drawAxes[0] = 1;


	outputFileName = new char[30]; strcpy(outputFileName, "");
	surf = NULL;
	drawSurf = new int[1];  drawSurf[0] = 1;
	surfTrans = new int[1]; surfTrans[0] = 1;

	drawSphere = alloc_set(SP_MAP);
	transSphere = alloc_set(SP_MAP);
	spheres = alloc_set(SP_MAP);
	radii = alloc_set(SP_MAP);

	drawCube = alloc_set(SP_MAP);
	transCube = alloc_set(SP_MAP);
	cubes = alloc_set(SP_MAP);
	cubeSize = alloc_set(SP_MAP);

}

ObjRenderer::~ObjRenderer()
{

	delete(obj_pos);
	delete(obj_rot);

}

void ObjRenderer::init(void)
{

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LEQUAL);									// The Type Of Depth Testing To Do	
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);								// Enable T
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
	GLfloat light_position2[] = { -20.0, 20.0, 20.0, 0.0 };
    GLfloat model_ambient[] = { 0.8, 0.8, 0.8, 1.0 };
	glClearDepth(1.0f);										// Depth Buffer Setup
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(POINTSIZE);
	glLineWidth(LINEWIDTH);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_STENCIL | GLUT_DOUBLE); 
//	glutInitDisplayString("rgba alpha=8 stencil=8 double");


}

void ObjRenderer::idle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
	if ( glutGetWindow() != main_window ){
		glutSetWindow(main_window);  
	}

	glutPostRedisplay();

}

void ObjRenderer::beginRendering(SurfaceObject * s)
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 250);

	main_window = glutCreateWindow("Interactive Protein Renderer by Brian Chen, Honig Lab 2007");

	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
		////mouse commands
	glutMouseFunc(processMouse);
		////keyboard commands
	glutKeyboardFunc(normalKeys);
		//creates and registers GLUI windows
	setUpGLUI();

	surf = s;

	init();
	glutMainLoop();
}

void ObjRenderer::render(int renderMode)
{

/////////////////////////////////////////////////////////////////////

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, aspectRatio, 0.1f, CLIPPINGVOL);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	///Transform for Basic rotation/translation
	///translation
	glTranslatef(0.0, 0.0, ZDISPLACEMENT);			///to make viewing easier
	glTranslatef(obj_pos[0], obj_pos[1], obj_pos[2]);
	///rotation
	glMultMatrixf(obj_rot);

	glPushMatrix();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	if(drawAxes[0]){
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 1000.0, 0.0, 0.0 );
		glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 1000.0, 0.0 );
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.0, 1000.0 );
		glEnd();
	}


	////////////////////////////////////////////////////////////////////////////////////////////
	////render solids first///////////////////////////////////////////
	if(surfTrans[0]==0 && drawSurf[0]==1){
		surf->draw(false, false, false, false, surf->centroid, NULL);
	}

	int i = 0;
	for(i = 0; i<size_set(spheres); i++){
		glColor4f(1, 0, 1, .5);
		int * transTest = (int *) mapsto_set(transSphere, i);
		int * drawTest = (int *) mapsto_set(drawSphere, i);
		if(transTest[0]==0 && drawTest[0]==1){
			float * vector = (float *) mapsto_set(spheres, i);
			float * radius = (float *) mapsto_set(radii, i);
			glPushMatrix();
			glTranslatef( vector[0], vector[1], vector[2] );
			glutSolidSphere  ( radius[0], ((int)radius[0])+4, ((int)(radius[0]/2))+4) ;
			glPopMatrix();
		}	
	}
	renderCubes(0);

//	static set_t drawCube;		//int ** [1] draw yes/no
//	static set_t transCube;		//int ** [1] transparent yes/no
//	static set_t cubes;			//float ** coordinates
//	static set_t cubeSize;

	////////////////////////////////////////////////////////////////////////////////////////////
	////then render transparents///////////////////////////////////////////
	if(surfTrans[0]==1 && drawSurf[0]==1){
//		surf->draw(false, false, true, true, surf->centroid, NULL);
		surf->draw(false, false, true, false, surf->centroid, NULL);
	}

	GLfloat mat_solid[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_transparent[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 0.0 };
	GLfloat low_shininess[] = { .5 };
	float amb[] = {0.20f, 0.50f, 1.0f, 0.1f};
	float diff[] = {0.20f, 0.50f, 1.0f, 0.1f};
	float spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float shine[] = {0.8 * 128.0f}; // The glass is very shiny

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 0, 1, .5);
	
	for(i = 0; i<size_set(spheres); i++){
		int * transTest = (int *) mapsto_set(transSphere, i);
		int * drawTest = (int *) mapsto_set(drawSphere, i);
		if(transTest[0]==1 && drawTest[0]==1){
			float * vector = (float *) mapsto_set(spheres, i);
			float * radius = (float *) mapsto_set(radii, i);
			glPushMatrix();
			glTranslatef( vector[0], vector[1], vector[2] );
			glutSolidSphere  ( radius[0], ((int)radius[0])+4, ((int)(radius[0]/2))+4) ;
			glPopMatrix();
		}	
	}
	renderCubes(1);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	glPopMatrix();

	glutSwapBuffers();

	glFlush ();

}

void ObjRenderer::renderCubes(int transparent)
{
	int i = 0;
	glColor4f(1, 0, 1, .5);
	for(i = 0; i<size_set(cubes); i++){
		int * transTest = (int *) mapsto_set(transCube, i);
		int * drawTest = (int *) mapsto_set(drawCube, i);
		if( transTest[0]!= transparent && drawTest[0]!=0){ continue; }

		float * vector = (float *) mapsto_set(cubes, i);
		float * radius = (float *) mapsto_set(cubeSize, i);

		double * p0 = new double[3]; p0[0]=vector[0]-radius[0]; p0[1]=vector[1]-radius[0]; p0[2]=vector[2]-radius[0]; 
		double * p1 = new double[3]; p1[0]=vector[0]-radius[0]; p1[1]=vector[1]-radius[0]; p1[2]=vector[2]+radius[0]; 
		double * p2 = new double[3]; p2[0]=vector[0]-radius[0]; p2[1]=vector[1]+radius[0]; p2[2]=vector[2]-radius[0]; 
		double * p3 = new double[3]; p3[0]=vector[0]-radius[0]; p3[1]=vector[1]+radius[0]; p3[2]=vector[2]+radius[0]; 
		double * p4 = new double[3]; p4[0]=vector[0]+radius[0]; p4[1]=vector[1]-radius[0]; p4[2]=vector[2]-radius[0]; 
		double * p5 = new double[3]; p5[0]=vector[0]+radius[0]; p5[1]=vector[1]-radius[0]; p5[2]=vector[2]+radius[0]; 
		double * p6 = new double[3]; p6[0]=vector[0]+radius[0]; p6[1]=vector[1]+radius[0]; p6[2]=vector[2]-radius[0]; 
		double * p7 = new double[3]; p7[0]=vector[0]+radius[0]; p7[1]=vector[1]+radius[0]; p7[2]=vector[2]+radius[0]; 

		glBegin(GL_TRIANGLES);

		//floor   0, 2, 6
		glNormal3f( 0, 0, -1 );	glVertex3f( p0[0], p0[1], p0[2] );
		glNormal3f( 0, 0, -1 );	glVertex3f( p2[0], p2[1], p2[2] );
		glNormal3f( 0, 0, -1 );	glVertex3f( p6[0], p6[1], p6[2] );

		//floor   0, 6, 4
		glNormal3f( 0, 0, -1 );	glVertex3f( p0[0], p0[1], p0[2] );
		glNormal3f( 0, 0, -1 );	glVertex3f( p6[0], p6[1], p6[2] );
		glNormal3f( 0, 0, -1 );	glVertex3f( p4[0], p4[1], p4[2] );

		//cieling 1, 5, 7
		glNormal3f( 0, 0, 1 );	glVertex3f( p1[0], p1[1], p1[2] );
		glNormal3f( 0, 0, 1 );	glVertex3f( p5[0], p5[1], p5[2] );
		glNormal3f( 0, 0, 1 );	glVertex3f( p7[0], p7[1], p7[2] );

		//cieling 1, 7, 3
		glNormal3f( 0, 0, 1 );	glVertex3f( p1[0], p1[1], p1[2] );
		glNormal3f( 0, 0, 1 );	glVertex3f( p7[0], p7[1], p7[2] );
		glNormal3f( 0, 0, 1 );	glVertex3f( p3[0], p3[1], p3[2] );

		//left    0, 1, 3,
		glNormal3f( -1, 0, 0 );	glVertex3f( p0[0], p0[1], p0[2] );
		glNormal3f( -1, 0, 0 );	glVertex3f( p1[0], p1[1], p1[2] );
		glNormal3f( -1, 0, 0 );	glVertex3f( p3[0], p3[1], p3[2] );

		//left    0, 3, 2, 
		glNormal3f( -1, 0, 0 );	glVertex3f( p0[0], p0[1], p0[2] );
		glNormal3f( -1, 0, 0 );	glVertex3f( p3[0], p3[1], p3[2] );
		glNormal3f( -1, 0, 0 );	glVertex3f( p2[0], p2[1], p2[2] );

		//right   4, 6, 7,
		glNormal3f( 1, 0, 0 );	glVertex3f( p4[0], p4[1], p4[2] );
		glNormal3f( 1, 0, 0 );	glVertex3f( p6[0], p6[1], p6[2] );
		glNormal3f( 1, 0, 0 );	glVertex3f( p7[0], p7[1], p7[2] );

		//right   4, 7, 5,
		glNormal3f( 1, 0, 0 );	glVertex3f( p4[0], p4[1], p4[2] );
		glNormal3f( 1, 0, 0 );	glVertex3f( p7[0], p7[1], p7[2] );
		glNormal3f( 1, 0, 0 );	glVertex3f( p5[0], p5[1], p5[2] );

		//front   0, 5, 1,
		glNormal3f( 0, 1, 0 );	glVertex3f( p0[0], p0[1], p0[2] );
		glNormal3f( 0, 1, 0 );	glVertex3f( p5[0], p5[1], p5[2] );
		glNormal3f( 0, 1, 0 );	glVertex3f( p1[0], p1[1], p1[2] );

		//front   0, 4, 5, 
		glNormal3f( 0, 1, 0 );	glVertex3f( p0[0], p0[1], p0[2] );
		glNormal3f( 0, 1, 0 );	glVertex3f( p4[0], p4[1], p4[2] );
		glNormal3f( 0, 1, 0 );	glVertex3f( p5[0], p5[1], p5[2] );

		//back    2, 3, 7,
		glNormal3f( 0, -1, 0 );	glVertex3f( p2[0], p2[1], p2[2] );
		glNormal3f( 0, -1, 0 );	glVertex3f( p3[0], p3[1], p3[2] );
		glNormal3f( 0, -1, 0 );	glVertex3f( p7[0], p7[1], p7[2] );

		//back    2, 7, 6,
		glNormal3f( 0, -1, 0 );	glVertex3f( p2[0], p2[1], p2[2] );
		glNormal3f( 0, -1, 0 );	glVertex3f( p7[0], p7[1], p7[2] );
		glNormal3f( 0, -1, 0 );	glVertex3f( p6[0], p6[1], p6[2] );

		glEnd();
		
		delete[](p0);	delete[](p1);	delete[](p2);	delete[](p3);
		delete[](p4);	delete[](p5);	delete[](p6);	delete[](p7); 
	}


}



void ObjRenderer::display(void)
{
	render(GL_RENDER);

}

////////////////////////////////////////////////
//////Used for mouse selection
void ObjRenderer::pickObjects(int x, int y)
{

} 


void ObjRenderer::processHits(GLint hits, GLuint buffer[])
{

}

void ObjRenderer::reshape(int w, int h)
{
	if (h==0) h=1;					//prevent divide by zero
	aspectRatio = ( (GLfloat) w/(GLfloat) h );
	
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glutPostRedisplay();

}

void ObjRenderer::normalKeys(unsigned char key, int x, int y)
{

}

void ObjRenderer::processMouse(int button, int state, int x, int y)
{

}

void ObjRenderer::controlCB(int control){
	switch(control){
	case CALLBACK_ADD_SPHERE:
		addSphere();
		break;
	case CALLBACK_ADD_CUBE:
		addCube();
		break;
	case CALLBACK_FILE_OUTPUT:
		if(size_set(spheres)>0){ outputFileVolumePrimitives(outputFileName, spheres, radii, surf->centroid, cubes, cubeSize); }
		glui_output_file_field->set_text("");
		break;
	case CALLBACK_BACKGROUND_CHANGE:
		changeBackGround();
		break;
	case CALLBACK_DRAW_AXES:
		if(drawAxes[0]==0){ drawAxes[0]=1; }
		else{ drawAxes[0]=0; }
		break;
	}
}

void ObjRenderer::changeBackGround()
{
	if(background == 0){
		printf("Change background to white\n");
	    glClearColor(1.0, 1.0, 1.0, 1.0);
		background = 1;
		return;
	}

	if(background == 1){
		printf("Change background to black\n");
	    glClearColor(0.0, 0.0, 0.0, 0.0);
		background = 0;
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);
}






///adds a point-based protein from PDB file, rendering via AtomList.
void ObjRenderer::addSphere()
{
	float * coords = new float[3];
	float * radius = new float[1];
	int * drawMe = new int[1];
	int * myTrans = new int[1];

	coords[0] = 0;	
	coords[1] = 0;	
	coords[2] = 0;	
	radius[0] = 5;
	drawMe[0] = 1;
	myTrans[0] = 0;
	
	spheres = associate_set(spheres, size_set(spheres), coords);
	radii = associate_set(radii, size_set(radii), radius);
	drawSphere = associate_set(drawSphere, size_set(drawSphere), drawMe);
	transSphere = associate_set(transSphere, size_set(transSphere), myTrans);
	
	printf("Added new sphere at 0,0,0, radius 5\n");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLUI_Panel * vcontrols = glui_controls->add_panel( "Sphere", GLUI_PANEL_EMBOSSED );

	glui_controls->add_checkbox_to_panel( vcontrols, "draw ", drawMe, -1, NULL);
	glui_controls->add_checkbox_to_panel( vcontrols, "trans", myTrans, -1, NULL);
	glui_controls->add_column_to_panel( vcontrols, false );


	
	//	glui_controls->add_translation( "XY Control", GLUI_TRANSLATION_XY, obj_pos );
	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, coords, -1, NULL );
		view_trans->set_speed( .1 );
		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
		view_trans->set_x( coords[0] );
		view_trans->set_y( coords[1] );
	glui_controls->add_column_to_panel( vcontrols, false );

	//Zoom Arrows
//	glui_controls->add_translation( "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &coords[2], -1, NULL );
		trans_z->set_speed( .1 );
		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
		trans_z->set_z( coords[2] );
	glui_controls->add_column_to_panel( vcontrols, false );

	//radius arrows
//	glui_controls->add_translation( "Radius Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
	GLUI_Translation *rad = glui_controls->add_translation_to_panel( vcontrols, "Radius", GLUI_TRANSLATION_Z, &radius[0], -1, NULL );
		rad->set_speed( .1 );
		rad->set_alignment( GLUI_ALIGN_RIGHT );
		rad->set_z( radius[0] );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


//set_t ObjRenderer::drawCube;		//int ** do we draw them or not;
//set_t ObjRenderer::transCube;		//float ** are they transparent or not;
//set_t ObjRenderer::cubes	;		//float ** location of the cubes
//set_t ObjRenderer::cubeSize;

///adds a point-based protein from PDB file, rendering via AtomList.
void ObjRenderer::addCube()
{
	float * coords = new float[3];
	float * radius = new float[1];
	int * drawMe = new int[1];
	int * myTrans = new int[1];

	coords[0] = 0;	
	coords[1] = 0;	
	coords[2] = 0;	
	radius[0] = 5;
	drawMe[0] = 1;
	myTrans[0] = 0;
	
	cubes = associate_set(cubes, size_set(cubes), coords);
	cubeSize = associate_set(cubeSize, size_set(cubeSize), radius);
	drawCube = associate_set(drawCube, size_set(drawCube), drawMe);
	transCube = associate_set(transCube, size_set(transCube), myTrans);
	
	printf("Added new cube at 0,0,0, radius 5\n");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLUI_Panel * vcontrols = glui_controls->add_panel( "Cube", GLUI_PANEL_EMBOSSED );

	glui_controls->add_checkbox_to_panel( vcontrols, "draw ", drawMe, -1, NULL);
	glui_controls->add_checkbox_to_panel( vcontrols, "trans", myTrans, -1, NULL);
	glui_controls->add_column_to_panel( vcontrols, false );


	
	//	glui_controls->add_translation( "XY Control", GLUI_TRANSLATION_XY, obj_pos );
	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, coords, -1, NULL );
		view_trans->set_speed( .1 );
		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
		view_trans->set_x( coords[0] );
		view_trans->set_y( coords[1] );
	glui_controls->add_column_to_panel( vcontrols, false );

	//Zoom Arrows
//	glui_controls->add_translation( "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &coords[2], -1, NULL );
		trans_z->set_speed( .1 );
		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
		trans_z->set_z( coords[2] );
	glui_controls->add_column_to_panel( vcontrols, false );

	//radius arrows
//	glui_controls->add_translation( "Radius Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
	GLUI_Translation *rad = glui_controls->add_translation_to_panel( vcontrols, "Size", GLUI_TRANSLATION_Z, &radius[0], -1, NULL );
		rad->set_speed( .1 );
		rad->set_alignment( GLUI_ALIGN_RIGHT );
		rad->set_z( radius[0] );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}






void ObjRenderer::setUpGLUI(void)
{
	////////////////////////////////////////////////////////////////////////////////
	///Register Callbacks with GLUI/////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	//glutReshapeFunc(reshape);
	GLUI_Master.set_glutReshapeFunc( reshape );
	//glutIdleFunc(display);	
	GLUI_Master.set_glutIdleFunc( idle );

	////////////////////////////////////////
	//Create GLUI window
	glui_controls = GLUI_Master.create_glui( "Controls", 0, 807, 200);
	glui_controls->set_main_gfx_window( main_window );
	////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	///Viewing Controls//////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	GLUI_Panel * vcontrols = glui_controls->add_panel( "Global Controls", GLUI_PANEL_EMBOSSED );

	//Translation Arrows
//	glui_controls->add_translation( "XY Control", GLUI_TRANSLATION_XY, obj_pos );
	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, obj_pos, -1, NULL );
		view_trans->set_speed( .1 );
		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
	glui_controls->add_column_to_panel( vcontrols, false );

	//Zoom Arrows
//	glui_controls->add_translation( "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2], -1, NULL );
		trans_z->set_speed( .2 );
		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
	glui_controls->add_column_to_panel( vcontrols, false );

	//Rotation ArcBall
//	glui_controls->add_rotation( "Rotation", obj_rot );
	GLUI_Rotation *view_rot = glui_controls->add_rotation_to_panel( vcontrols, "Rotation", obj_rot, -1, NULL );
		view_rot->set_spin( 0.0 );
		view_rot->set_alignment( GLUI_ALIGN_RIGHT );
	glui_controls->add_column_to_panel( vcontrols, false );

	GLUI_Button * button1 = glui_controls->add_button_to_panel( vcontrols, "background", CALLBACK_BACKGROUND_CHANGE, controlCB);
	GLUI_Button * button2 = glui_controls->add_button_to_panel( vcontrols, "draw Axes", CALLBACK_DRAW_AXES, controlCB);

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	///Rendering Controls////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	GLUI_Panel * rcontrols = glui_controls->add_panel( "Output Volume File", GLUI_PANEL_EMBOSSED );
	glui_controls->add_checkbox_to_panel( rcontrols, "draw ", drawSurf, -1, NULL);
	glui_controls->add_checkbox_to_panel( rcontrols, "trans", surfTrans, -1, NULL);
	glui_controls->add_column_to_panel( rcontrols, false );
	glui_output_file_field = glui_controls->add_edittext_to_panel( rcontrols, "output header", GLUI_EDITTEXT_TEXT, outputFileName, CALLBACK_FILE_OUTPUT, controlCB);

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	///Rendering Controls////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	GLUI_Panel * scontrols = glui_controls->add_panel( "", GLUI_PANEL_EMBOSSED );
	glui_controls->add_button_to_panel(scontrols, "Add Sphere", CALLBACK_ADD_SPHERE, controlCB);
	glui_controls->add_column_to_panel(scontrols, false );
	glui_controls->add_button_to_panel(scontrols, "Add Cube", CALLBACK_ADD_CUBE, controlCB);

}






