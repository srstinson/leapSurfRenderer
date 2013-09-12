////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation for the Main methods for the Geometric Hashing Database search
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"


void defaultOutput()
{
		printf("=========================================================\n");
		printf("Brian Chen's Protein Structure Renderer\n");
		printf("Honig Lab, 2007\n");
		printf("=========================================================\n");
		printf("Run interactively without initial input\n");
		printf("  [executable]\n");
		printf("\n");
		printf("Run interactively with initial alignment\n");
		printf("  [executable] -renderAlignment [AlignmentFile]\n");
		printf("  ---Renders all files specified in the Alignment file.  If no .SURF file exists for a specified surface\n");
		printf("     the pdb file will be rendered instead.  All PDB and SURF files must be present in the same directory.\n");
		printf("\n");
		printf("Edit Volume Probes\n");
		printf("  [executable] -addVolumeProbes [SURFfile]\n");
		printf("  ---Interactive creation of volume probes using a SURF file\n");
		printf("\n");
		printf("=========================================================\n");
}

void errorOutput()
{
		printf("===============================================================\n");
		printf("Erroneous Input Detected.  Rerun with no command line arguments\n");
		printf("for usage description and help.\n");
		printf("===============================================================\n");
}


void testDebug()
{

	SurfaceObject * thisSurf = parseGeometryFile("1qz3.SURF");
	printf("%lf %lf %lf\n", thisSurf->centroid[0], thisSurf->centroid[1], thisSurf->centroid[2] );

	exit(1);

}




//
//-addVolumeProbes 1qz3.SURF
//-renderAlignment testAlign
//-addVolumeProbes 1M33ROT.SURF
//
//execution format : [executable name] [cabFile name]
int main(int argc, char* argv[])
{
//	testDebug();

	Renderer * myRenderer;

	if(argc == 1){
		myRenderer = new Renderer();
		myRenderer->beginRendering(NULL);
	}
	if(argc == 3 && strcmp(argv[1], "-renderAlignment")==0 ){
		myRenderer = new Renderer();
		PocketAlignment * align = new PocketAlignment(argv[2]);
		myRenderer->beginRendering(align);
	}
	if(argc == 3 && strcmp(argv[1], "-addVolumeProbes")==0 ){
		ObjRenderer * thisRenderer = new ObjRenderer();
		SurfaceObject * thisSurf = parseGeometryFile(argv[2]);
		thisRenderer->beginRendering(thisSurf);
	}


	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////






