// Renderer.cpp: implementation of the Renderer class.
//
//////////////////////////////////////////////////////////////////////

#include "Renderer.h"
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Renderer::main_window;		///referenced by GLUI to get back to the main window

//GLUI windows
GLUI * Renderer::glui_controls;
float Renderer::aspectRatio;
float * Renderer::obj_pos;
float * Renderer::obj_rot;
int * Renderer::drawAxes;
int * Renderer::useCentroid;
GLUI_EditText * Renderer::glui_input_file_field;
GLUI_EditText * Renderer::glui_output_file_field;



///my stuff
char * Renderer::outputFileName;
char * Renderer::inputFileName;

//	static int numProts;
set_t Renderer::drawProt;		//int ** drawProt;
set_t Renderer::lists;			//AtomList ** lists;
set_t Renderer::list_pos;		//float ** list_pos;
set_t Renderer::list_rot;		//float ** list_rot;

	///surface-based rendering
//	static int numSurfs;
set_t Renderer::drawSurf;		//int ** drawSurf;
set_t Renderer::transSurf;		//int ** transSurf;
set_t Renderer::surfs;			//SurfaceObject ** surfs;
set_t Renderer::surf_pos;		//float ** surf_pos;
set_t Renderer::surf_rot;		//float ** surf_rot;
double * Renderer::centroid;	///double * centroid


int Renderer::background;

Renderer::Renderer()
{
	background = 0;
	
	outputFileName = new char[30]; strcpy(outputFileName, "");
	inputFileName = new char[50]; strcpy(inputFileName, "");

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
	useCentroid = new int[1]; useCentroid [0] = 1;

	drawProt = alloc_set(SP_MAP);
	lists = alloc_set(SP_MAP);
	list_pos = alloc_set(SP_MAP);
	list_rot = alloc_set(SP_MAP);

	drawSurf = alloc_set(SP_MAP);
	transSurf = alloc_set(SP_MAP);
	surfs = alloc_set(SP_MAP);
	surf_pos = alloc_set(SP_MAP);
	surf_rot = alloc_set(SP_MAP);

	centroid = new double[3];
	centroid[0] = 0;
	centroid[1] = 0;
	centroid[2] = 0;


}

Renderer::~Renderer()
{

	delete(obj_pos);
	delete(obj_rot);
//	delete(motifVar_GLUIsaveName);
//	delete(motifVar_GLUIloadName);


}

void Renderer::init(void)
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

}

void Renderer::idle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
	if ( glutGetWindow() != main_window ){
		glutSetWindow(main_window);  
	}

	glutPostRedisplay();

}

void Renderer::beginRendering(PocketAlignment * palign)
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

	///insert the data from the pocketAlignment if it isnt NULL
	if(palign != NULL){
		int i = 0;
		for(i = 0; i<palign->numPockets; i++){
			SurfaceObject * surf = (SurfaceObject *) mapsto_set(palign->pockets, i);
			AtomList * alist = (AtomList *) mapsto_set(palign->aLists, i);		
			double * align = (double *) mapsto_set(palign->alignments, i);
			char * fn = (char *) mapsto_set(palign->names, i);

			float * new_pos = new float[3];
			new_pos[0] = (float) align[12];
			new_pos[1] = (float) align[13];
			new_pos[2] = (float) align[14];
//			new_pos[0] = 0.0;
//			new_pos[1] = 0.0;
//			new_pos[2] = 0.0;
			float * new_rot = new float[16];
			new_rot[0] = (float) align[0];
			new_rot[1] = (float) align[1];
			new_rot[2] = (float) align[2];
			new_rot[3] = (float) align[3];
			new_rot[4] = (float) align[4];
			new_rot[5] = (float) align[5];
			new_rot[6] = (float) align[6];
			new_rot[7] = (float) align[7];
			new_rot[8] = (float) align[8];
			new_rot[9] = (float) align[9];
			new_rot[10] = (float) align[10];
			new_rot[11] = (float) align[11];
			new_rot[12] = 0.0;
			new_rot[13] = 0.0;
			new_rot[14] = 0.0;
			new_rot[15] = (float) align[15];

			//if the surface is null, insert the structure.
			if(surf == NULL){
				addStruct(alist, new_pos, new_rot, fn);
			}
			//otherwise insert the surface
			else{
				addStruct(surf, new_pos, new_rot, fn);
			}
		}
	}

	init();
	glutMainLoop();
}

void Renderer::render(int renderMode)
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

	if(drawAxes[0]){
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 1000.0, 0.0, 0.0 );
		glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 1000.0, 0.0 );
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.0, 1000.0 );
		glEnd();
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f);	glVertex3f( 0.0, 0.0, 0.0 );
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 1.0, 0.0, 0.0 );  glVertex3f( 2.0, 0.0, 0.0 );
		glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f( 0.0, 1.0, 0.0 );  glVertex3f( 0.0, 2.0, 0.0 );
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 0.0, 0.0, 1.0 );  glVertex3f( 0.0, 0.0, 2.0 );
		glEnd();



	}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	double * cent = new double[3]; cent[0] = 0; cent[1] = 0; cent[2] = 0; 
	if(useCentroid[0]==1){
		cent[0] = centroid[0];
		cent[1] = centroid[1];
		cent[2] = centroid[2];
	}

	glColor3f(1, 1, 1);


	////////////////////////////////////////////////////////////////////////////////////////////
	////render solids first///////////////////////////////////////////
	int i = 0;
	for(i = 0; i<size_set(lists); i++){
		int * drawList = (int*) mapsto_set(drawProt, i);
		if(drawList[0]){
			float * pos = (float *) mapsto_set(list_pos, i);
			float * rot = (float *) mapsto_set(list_rot, i);

			glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);
			glMultMatrixf(rot);
			glPushMatrix();

			AtomList * list = (AtomList *) mapsto_set(lists, i);
			list->renderMolecule(cent);
			glPopMatrix();
			glPopMatrix();
		}
	}

	for(i = 0; i<size_set(surfs); i++){
		int * drawSurfs = (int*) mapsto_set(drawSurf, i);
		if(drawSurfs[0]){
			int * transSurfs = (int*) mapsto_set(transSurf, i);
			if(!transSurfs[0]){
				float * pos = (float *) mapsto_set(surf_pos, i);
				float * rot = (float *) mapsto_set(surf_rot, i);
				glPushMatrix();
				glTranslatef(pos[0], pos[1], pos[2]);
				glMultMatrixf(rot);
				glPushMatrix();

				SurfaceObject * surf = (SurfaceObject *) mapsto_set(surfs, i);
				surf->draw(false, false, transSurfs[0], true, cent, NULL);
				glPopMatrix();
				glPopMatrix();
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	////then render transparents///////////////////////////////////////////
	for(i = 0; i<size_set(surfs); i++){
		int * drawSurfs = (int*) mapsto_set(drawSurf, i);
		if(drawSurfs[0]){
			int * transSurfs = (int*) mapsto_set(transSurf, i);
			if(transSurfs[0]){
				float * pos = (float *) mapsto_set(surf_pos, i);
				float * rot = (float *) mapsto_set(surf_rot, i);
				glPushMatrix();
				glTranslatef(pos[0], pos[1], pos[2]);
				glMultMatrixf(rot);
				glPushMatrix();

				SurfaceObject * surf = (SurfaceObject *) mapsto_set(surfs, i);
				surf->draw(false, false, transSurfs[0], true, cent, NULL);
				glPopMatrix();
				glPopMatrix();
			}
		}
	}

	delete[](cent);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	glPopMatrix();

	glutSwapBuffers();

	glFlush ();

}

void Renderer::display(void)
{
	render(GL_RENDER);

}

////////////////////////////////////////////////
//////Used for mouse selection
void Renderer::pickObjects(int x, int y)
{

} 


void Renderer::processHits(GLint hits, GLuint buffer[])
{

}

void Renderer::reshape(int w, int h)
{
	if (h==0) h=1;					//prevent divide by zero
	aspectRatio = ( (GLfloat) w/(GLfloat) h );
	
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glutPostRedisplay();

}

void Renderer::normalKeys(unsigned char key, int x, int y)
{

}

void Renderer::processMouse(int button, int state, int x, int y)
{

}

void Renderer::controlCB(int control){
	switch(control){
	case CALLBACK_FILE_INPUT:
		addStruct(inputFileName);
		break;
	case CALLBACK_FILE_OUTPUT:
		if(size_set(lists)>0){ outputFileAtomList(outputFileName, lists, list_pos, list_rot); }
		if(size_set(surfs)>0){ outputFileSurfObj(outputFileName, surfs, surf_pos, surf_rot); }
		glui_output_file_field->set_text("");
		break;
	case CALLBACK_BACKGROUND_CHANGE:
		changeBackGround();
		break;
	case CALLBACK_DRAW_AXES:
		if(drawAxes[0]==0){ drawAxes[0]=1; }
		else{ drawAxes[0]=0; }
		break;
	case CALLBACK_CENTERING:
		if(useCentroid[0]==0){ useCentroid[0]=1; }
		else{ useCentroid[0]=0; }
		break;
	}
}






///adds a point-based protein from PDB file, rendering via AtomList.
void Renderer::addProt(char * fn)
{
	char * temp = new char[1000];
	strcpy(temp, fn);
	char * ptr = strtok(temp, " \a\b\f\n\r\t\v\'\\");
	char * filename = new char[1000];
	strcpy(filename, ptr);

	pdbParser * parse = new pdbParser(filename);
	AtomList * list = parse->getAtomList();

	if(list == NULL){
		delete[](parse);
		printf("File [%s] not found! Try again.\n", filename);
		glui_input_file_field->set_text("");
		sprintf(inputFileName, "");
		return;
	}
	delete[](parse);

	float * new_pos = new float[3];
	new_pos[0] = 0.0;
	new_pos[1] = 0.0;
	new_pos[2] = 0.0;

	float * new_rot = new float[16];
	new_rot[0] = 1.0;	new_rot[1] = 0.0;	new_rot[2] = 0.0;	new_rot[3] = 0.0;
	new_rot[4] = 0.0;	new_rot[5] = 1.0;	new_rot[6] = 0.0;	new_rot[7] = 0.0;
	new_rot[8] = 0.0;	new_rot[9] = 0.0;	new_rot[10] = 1.0;	new_rot[11] = 0.0;
	new_rot[12] = 0.0;	new_rot[13] = 0.0;	new_rot[14] = 0.0;	new_rot[15] = 1.0;

	int * t = new int[1];
	t[0] = 1;

	int numProts = size_set(lists);
	drawProt = associate_set(drawProt, numProts, t);
	list_pos = associate_set(list_pos, numProts, new_pos);
	list_rot = associate_set(list_rot, numProts, new_rot);
	lists = associate_set(lists, numProts, list);

	printf("File [%s] found and displayed!\n", filename);
	glui_input_file_field->set_text("");
	sprintf(inputFileName, "");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLUI_Panel * vcontrols = glui_controls->add_panel( filename, GLUI_PANEL_EMBOSSED );

	glui_controls->add_checkbox_to_panel( vcontrols, "draw ", t, -1, NULL);
	glui_controls->add_column_to_panel( vcontrols, false );

//	glui_controls->add_translation( "XY Control", GLUI_TRANSLATION_XY, obj_pos );
//	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, new_pos, -1, NULL );
//		view_trans->set_speed( .1 );
//		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
//		view_trans->set_x( new_pos[0] );
//		view_trans->set_y( new_pos[1] );
//	glui_controls->add_column_to_panel( vcontrols, false );
//
//	//Zoom Arrows
//	glui_controls->add_translation( "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
//	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &new_pos[2], -1, NULL );
//		trans_z->set_speed( .2 );
//		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
//		trans_z->set_z( new_pos[2] );
//	glui_controls->add_column_to_panel( vcontrols, false );
//
//	//Rotation ArcBall
//	glui_controls->add_rotation( "Rotation", obj_rot );
//	GLUI_Rotation *view_rot = glui_controls->add_rotation_to_panel( vcontrols, "Rotation", new_rot, -1, NULL );
//		view_rot->set_float_array_val(new_rot);
//		view_rot->set_alignment( GLUI_ALIGN_RIGHT );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void Renderer::addSurf(char * fn)
{
	char * temp = new char[1000];
	strcpy(temp, fn);
	char * ptr = strtok(temp, " \a\b\f\n\r\t\v\'\\");
	char * filename = new char[1000];
	strcpy(filename, ptr);

	SurfaceObject * surf = parseGeometryFile(filename); 

	if(surf == NULL){
		printf("File [%s] not found! Try again.\n", filename);
		glui_input_file_field->set_text("");
		sprintf(inputFileName, "");
		return;
	}

	float * new_pos = new float[3];
	new_pos[0] = 0.0;
	new_pos[1] = 0.0;
	new_pos[2] = 0.0;

	float * new_rot = new float[16];
	new_rot[0] = 1.0;	new_rot[1] = 0.0;	new_rot[2] = 0.0;	new_rot[3] = 0.0;
	new_rot[4] = 0.0;	new_rot[5] = 1.0;	new_rot[6] = 0.0;	new_rot[7] = 0.0;
	new_rot[8] = 0.0;	new_rot[9] = 0.0;	new_rot[10] = 1.0;	new_rot[11] = 0.0;
	new_rot[12] = 0.0;	new_rot[13] = 0.0;	new_rot[14] = 0.0;	new_rot[15] = 1.0;
	int * t = new int[1];
	t[0] = 1;
	int * t2 = new int[1];
	t2[0] = 0;

	int numTotalObjects = size_set(lists) + size_set(surfs);
	double * newCentroid = new double[3];
	newCentroid[0] = numTotalObjects * centroid[0] + surf->centroid[0];
	newCentroid[1] = numTotalObjects * centroid[1] + surf->centroid[1];
	newCentroid[2] = numTotalObjects * centroid[2] + surf->centroid[2];
	newCentroid[0] /= numTotalObjects + 1;
	newCentroid[1] /= numTotalObjects + 1;
	newCentroid[2] /= numTotalObjects + 1;
	delete[](centroid);
	centroid = newCentroid;

	int numSurfs = size_set(surfs);
	drawSurf = associate_set(drawSurf, numSurfs, t);
	transSurf = associate_set(transSurf, numSurfs, t2);
	surfs = associate_set(surfs, numSurfs, surf);
	surf_pos = associate_set(surf_pos, numSurfs, new_pos);
	surf_rot = associate_set(surf_rot, numSurfs, new_rot);

	printf("File [%s] found and displayed!\n", filename);
	glui_input_file_field->set_text("");
	sprintf(inputFileName, "");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLUI_Panel * vcontrols = glui_controls->add_panel( filename, GLUI_PANEL_EMBOSSED );

	glui_controls->add_checkbox_to_panel( vcontrols, "draw ", t, -1, NULL);
	glui_controls->add_column_to_panel( vcontrols, false );
	glui_controls->add_checkbox_to_panel( vcontrols, "trans", t2, -1, NULL);
//	glui_controls->add_column_to_panel( vcontrols, false );

//	glui_controls->add_translation( "XY Control", GLUI_TRANSLATION_XY, obj_pos );
//	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, new_pos, -1, NULL );
//		view_trans->set_speed( .1 );
//		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
//		view_trans->set_x( new_pos[0] );
//		view_trans->set_y( new_pos[1] );
//	glui_controls->add_column_to_panel( vcontrols, false );
//
//	//Zoom Arrows
//	glui_controls->add_translation( "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
//	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &new_pos[2], -1, NULL );
//		trans_z->set_speed( .2 );
//		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
//		trans_z->set_z( new_pos[2] );
//	glui_controls->add_column_to_panel( vcontrols, false );
//
//	//Rotation ArcBall
//	glui_controls->add_rotation( "Rotation", obj_rot );
//	GLUI_Rotation *view_rot = glui_controls->add_rotation_to_panel( vcontrols, "Rotation", new_rot, -1, NULL );
//		view_rot->set_float_array_val(new_rot);
//		view_rot->set_alignment( GLUI_ALIGN_RIGHT );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void Renderer::addStruct(char * fn)
{
	char * tempString = new char[1000];
	strcpy(tempString, fn);
	char * ptr;
	ptr = strtok(tempString, ".\r\t\n\b");
	ptr = strtok(NULL, ".\r\t\n\b");

	bool foundFormat = false;
	if( strcmp(ptr, "pdb") == 0){
		addProt(fn);
		foundFormat = true;
	}
	if( strcmp(ptr, "SURF") == 0){
		addSurf(fn);
		foundFormat = true;
	}

	if(!foundFormat){
		printf("ERROR: The filename does not end with .pdb or .SURF, or the\n");
		printf("ERROR: filename has more than one period in it! No file added.\n");
	}

	delete[](tempString);
}



void Renderer::addStruct(SurfaceObject * surf, float * pos, float * rot, char * fn)
{
	int * t = new int[1];
	t[0] = 1;
	int * t2 = new int[1];
	t2[0] = 0;

	int numSurfs = size_set(surfs);
	drawSurf = associate_set(drawSurf, numSurfs, t);
	transSurf = associate_set(transSurf, numSurfs, t2);
	surfs = associate_set(surfs, numSurfs, surf);
	surf_pos = associate_set(surf_pos, numSurfs, pos);
	surf_rot = associate_set(surf_rot, numSurfs, rot);

	printf("New SURF [%s] file imported from Alignment File! (numSurfs: %i)\n", fn, numSurfs);

	float * rot_copy = new float[16];
	int i = 0;
	for(i = 0; i<16; i++){rot_copy[i] = rot[i];}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLUI_Panel * vcontrols = glui_controls->add_panel( fn, GLUI_PANEL_EMBOSSED );

	glui_controls->add_checkbox_to_panel( vcontrols, "draw ", t, -1, NULL);
	glui_controls->add_column_to_panel( vcontrols, false );
	glui_controls->add_checkbox_to_panel( vcontrols, "trans", t2, -1, NULL);
//	glui_controls->add_column_to_panel( vcontrols, false );

//	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, pos, -1, NULL );
//		view_trans->set_speed( .1 );
//		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
//		view_trans->set_x( pos[0] );
//		view_trans->set_y( pos[1] );
//	glui_controls->add_column_to_panel( vcontrols, false );
//
//	//Zoom Arrows
//	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &pos[2], -1, NULL );
//		trans_z->set_speed( .2 );
//		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
//		trans_z->set_z( pos[2] );
//	glui_controls->add_column_to_panel( vcontrols, false );
//
//
//	//Rotation ArcBall
//	GLUI_Rotation *view_rot = glui_controls->add_rotation_to_panel( vcontrols, "Rotation", rot, -1, NULL );
//		view_rot->set_alignment( GLUI_ALIGN_RIGHT );
//		view_rot->set_float_array_val(rot_copy);
//
	delete[](rot_copy);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}








void Renderer::addStruct(AtomList * list, float * pos, float * rot, char * fn)
{
	int * t = new int[1];
	t[0] = 1;

	int numTotalObjects = size_set(lists) + size_set(surfs);
	double * newCentroid = new double[3];
	double * atomListCentroid = list->getAtomListCentroid();
	newCentroid[0] = numTotalObjects * centroid[0] + atomListCentroid[0];
	newCentroid[1] = numTotalObjects * centroid[1] + atomListCentroid[1];
	newCentroid[2] = numTotalObjects * centroid[2] + atomListCentroid[2];
	newCentroid[0] /= numTotalObjects + 1;
	newCentroid[1] /= numTotalObjects + 1;
	newCentroid[2] /= numTotalObjects + 1;
	delete[](atomListCentroid);
	delete[](centroid);
	centroid = newCentroid;

	int numProts = size_set(lists);
	drawProt = associate_set(drawProt, numProts, t);
	list_pos = associate_set(list_pos, numProts, pos);
	list_rot = associate_set(list_rot, numProts, rot);
	lists = associate_set(lists, numProts, list);

	float * rot_copy = new float[16];
	int i = 0;
	for(i = 0; i<16; i++){rot_copy[i] = rot[i];}

	printf("New AtomList [%s] imported from Alignment File!\n", fn);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLUI_Panel * vcontrols = glui_controls->add_panel( fn, GLUI_PANEL_EMBOSSED );

	glui_controls->add_checkbox_to_panel( vcontrols, "draw ", t, -1, NULL);
//	glui_controls->add_column_to_panel( vcontrols, false );

//	glui_controls->add_translation( "XY Control", GLUI_TRANSLATION_XY, obj_pos );
//	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, pos, -1, NULL );
//		view_trans->set_speed( .1 );
//		view_trans->set_alignment( GLUI_ALIGN_RIGHT );
//		view_trans->set_x( pos[0] );
//		view_trans->set_y( pos[1] );
//	glui_controls->add_column_to_panel( vcontrols, false );

	//Zoom Arrows
//	glui_controls->add_translation( "Z Control", GLUI_TRANSLATION_Z, &obj_pos[2] );
//	GLUI_Translation *trans_z = glui_controls->add_translation_to_panel( vcontrols, "Z Control", GLUI_TRANSLATION_Z, &pos[2], -1, NULL );
//		trans_z->set_speed( .2 );
//		trans_z->set_alignment( GLUI_ALIGN_RIGHT );
//		trans_z->set_z( pos[2] );
//	glui_controls->add_column_to_panel( vcontrols, false );

	//Rotation ArcBall
//	glui_controls->add_rotation( "Rotation", obj_rot );
//	GLUI_Rotation *view_rot = glui_controls->add_rotation_to_panel( vcontrols, "Rotation", rot, -1, NULL );
//		view_rot->set_alignment( GLUI_ALIGN_RIGHT );
//		view_rot->set_float_array_val(rot_copy);
//
	delete[](rot_copy);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}


void Renderer::changeBackGround()
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







void Renderer::setUpGLUI(void)
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
//	GLUI_Translation *view_trans = glui_controls->add_translation_to_panel( vcontrols, "XY Control", GLUI_TRANSLATION_XY, obj_pos, -1, NULL );
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
	GLUI_Rotation *view_rot = glui_controls->add_rotation_to_panel( vcontrols, "Rotation", obj_rot, -1, controlCB );
		view_rot->set_spin( 0.0 );
		view_rot->set_alignment( GLUI_ALIGN_RIGHT );
	glui_controls->add_column_to_panel( vcontrols, false );

	GLUI_Button * button1 = glui_controls->add_button_to_panel( vcontrols, "background", CALLBACK_BACKGROUND_CHANGE, controlCB);
	GLUI_Button * button2 = glui_controls->add_button_to_panel( vcontrols, "draw Axes", CALLBACK_DRAW_AXES, controlCB);
	GLUI_Button * button3 = glui_controls->add_button_to_panel( vcontrols, "centering", CALLBACK_CENTERING, controlCB);

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	///Rendering Controls////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	GLUI_Panel * rcontrols = glui_controls->add_panel( "Add a new Protein:", GLUI_PANEL_EMBOSSED );

	glui_input_file_field = glui_controls->add_edittext_to_panel( rcontrols, "new protein", GLUI_EDITTEXT_TEXT, inputFileName, CALLBACK_FILE_INPUT, controlCB);
	glui_controls->add_column_to_panel( rcontrols, false );
	glui_output_file_field = glui_controls->add_edittext_to_panel( rcontrols, "output header", GLUI_EDITTEXT_TEXT, outputFileName, CALLBACK_FILE_OUTPUT, controlCB);





}






