

#include "StdAfx.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////  ///  // // / // /    /////    ///  //   //  ////////// //////   /   /    /   ///////////////////////////////////////////////
// /// // / // / // / // / /// //// /// / // // // // /////////  //// ///// ///// / /////////////////////////////////////////////////
// /// // / // /   // // / /// //// /// / // // // // //          //// //// //// //   ///////////////////////////////////////////////
// /// // / // / / // // /    ///// /// /    // //    //          ///// /// /// /// /////////////////////////////////////////////////
// /// // / // / // / // / //////// /// / // // // // /////////  /////// // // //// /////////////////////////////////////////////////
//   //  ///  // // //  // ////////    // // // // // ///////// /////   //   /    /   ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function looks up atom Radius.  See reference data
//in header file
//
//This could obviously be optimized, but its still hundreds of thousands of times faster than 
//calling GRASP externally and generating files, as was done earlier.
//This implementation has the advantage that new data can be easily replaced in the code.
double lookupAtomRadius(char * at, char * aat)
{
	char * ptr;
	
	bool generalizedRadii = false;
	double result = -1;

	///////////////////////////////////////////////////////////
	///Initial error fixes
	char * temp = new char[10];
	char * atomType = new char[10];
	strcpy(temp, at);
	ptr = strtok(temp, " \r\n\t");
	strcpy(atomType, ptr);
	delete[](temp);

	temp = new char[10];
	char * aaType = new char[10];
	strcpy(temp, aat);
	ptr = strtok(temp, " \r\n\t");
	strcpy(aaType, ptr);
	delete[](temp);
	
	///////////////////////////////////////////////////////////
	///quick check
	if(     (strcmp(aaType, "ALA" ) != 0) && (strcmp(aaType, "ARG" ) != 0) && (strcmp(aaType, "ASN" ) != 0) && (strcmp(aaType, "ASP" ) != 0) 
		&& (strcmp(aaType, "CYS" ) != 0) && (strcmp(aaType, "GLN" ) != 0) && (strcmp(aaType, "GLU" ) != 0) && (strcmp(aaType, "GLY" ) != 0) 
		&& (strcmp(aaType, "HSD" ) != 0) && (strcmp(aaType, "HSE" ) != 0) && (strcmp(aaType, "HIS" ) != 0) && (strcmp(aaType, "HSP" ) != 0) 
		&& (strcmp(aaType, "ILE" ) != 0) && (strcmp(aaType, "LEU" ) != 0) && (strcmp(aaType, "LYS" ) != 0) && (strcmp(aaType, "MET" ) != 0) 
		&& (strcmp(aaType, "PHE" ) != 0) && (strcmp(aaType, "PRO" ) != 0) && (strcmp(aaType, "SER" ) != 0) && (strcmp(aaType, "THR" ) != 0) 
		&& (strcmp(aaType, "TRP" ) != 0) && (strcmp(aaType, "TYR" ) != 0) && (strcmp(aaType, "VAL" ) != 0) && (strcmp(aaType, "TIP3") != 0) 
		&& (strcmp(aaType, "TP3M") != 0) && (strcmp(aaType, "CAL" ) != 0) && (strcmp(aaType, "ZN2" ) != 0) && (strcmp(aaType, "HEME") != 0) 
		&& (strcmp(aaType, " O2 "  ) != 0) && (strcmp(aaType, "CO"  ) != 0) && (strcmp(aaType, "DUM" ) != 0) )
	{
		generalizedRadii = true;
	}

	if(generalizedRadii == false){
		///////////////////////////////////////////////////////////
		///Begin formal lookup	
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB3"	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HB "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "ALA") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HG "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HD "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " NE "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HE "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "NH1 "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HH11"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HH12"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1HH1"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2HH1"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "NH2 "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HH21"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HH22"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1HH2"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2HH2"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "ARG") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OD1"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " ND2"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HD21"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HD22"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1HD2"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2HD2"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "ASN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OD1"	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OD2"	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "ASP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " SG "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.5;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.5;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "CYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OE1"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " NE2"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HE21"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HE22"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1HE2"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2HE2"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "GLN") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OE1"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OE2"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "GLU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HA1"	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HA2"	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HA "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HA "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "GLY") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " ND1"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " NE2"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.5;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 0.9;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "HSD") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " NE2"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.5;}
		if( (strcmp(atomType, " ND1"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.9;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "HSE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " NE2"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.5;}
		if( (strcmp(atomType, " ND1"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.9;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "HIS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " ND1"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " NE2"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.7;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.9;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "HSP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HB "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG2"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HG21"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG22"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG23"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG2"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG2"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HG2"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, "HG11"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG12"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " CD1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD3"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HD "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HD1"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "ILE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HG "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD1"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HD11"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HD12"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HD13"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD1"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD1"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HD1"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HD21"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HD22"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HD23"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD2"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD2"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HD2"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "LEU") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CE "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HE "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HE "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " NZ "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HZ1"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " HZ2"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " HZ3"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1HZ "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2HZ "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3HZ "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "LYS") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " SD "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " CE "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HE3"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HE "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HE "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HE "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "MET") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " CD1"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HZ "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "PHE") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HD "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HD "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "PRO") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " OG "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " HG "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "SER") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HB "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " OG1"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CG2"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HG21"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG22"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG23"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG2"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG2"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HG2"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "THR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CD1"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " NE1"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CE3"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE3"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HZ2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ3"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HZ3"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CH2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HH2"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "TRP") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HB "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HB "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " CD1"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OH "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HH "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "TYR") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1H  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "2H  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "3H  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HB "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG1"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HG11"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG12"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG13"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG1"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG1"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HG1"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG2"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HG21"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG22"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HG23"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "1HG2"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "2HG2"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "3HG2"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "VAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OH2"	) == 0) && (strcmp(aaType, "TIP3")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "TIP3")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "TIP3")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " OH2"	) == 0) && (strcmp(aaType, "TP3M")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " H1 "	) == 0) && (strcmp(aaType, "TP3M")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "TP3M")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "CAL"	) == 0) && (strcmp(aaType, "CAL") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " ZN "	) == 0) && (strcmp(aaType, "ZN2") == 0) ) {delete[](atomType); delete[](aaType); result = 1.1;}
		if( (strcmp(atomType, "FE"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.7;}
		if( (strcmp(atomType, "NA"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "NB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "NC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "ND"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "C1A"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C2A"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C3A"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C4A"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C1B"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C2B"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C3B"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C4B"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C1C"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C2C"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C3C"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C4C"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C1D"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C2D"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C3D"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "C4D"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "CHA"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CHB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HB "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CHC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "HC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CHD"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "HD"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CMA"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HMA1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMA2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMA3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CAA"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, "HAA1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HAA2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CBA"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, "HBA1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HBA2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CGA"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "O1A"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "O2A"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "CMB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HMB1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMB2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMB3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CAB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "HAB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CBB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "HBB1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HBB2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CMC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HMC1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMC2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMC3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CAC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "HAC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CBC"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "HBC1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HBC2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CMD"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HMD1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HMD3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CAD"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, "HAD1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HAD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CBD"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, "HBD1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HBD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CGD"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "O1D"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "O2D"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HT3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HT3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HA1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HA2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HN1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HN2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CAY"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HY1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HY2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HY3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CY"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "OY"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "CAY"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HY1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HY2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HY3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "CY"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "OY"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "OT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "OT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " N  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HN "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.3;}
		if( (strcmp(atomType, " HA "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "OT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "OT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, "CT"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HT3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OXT"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "NT"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "HT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "NT"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, "HNT"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "CAT"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, "HT1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HT2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, "HT3"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OD1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HG1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HG2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " CD "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OE1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " OE2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, "1CB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, "1SG"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "2SG"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, "2CB"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.9;}
		if( (strcmp(atomType, " ND1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " CB "	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 2.2;}
		if( (strcmp(atomType, " HB1"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " HB2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.3;}
		if( (strcmp(atomType, " NE2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.9;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " CD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " HD2"	) == 0) && (strcmp(aaType, "HEME")== 0) ) {delete[](atomType); delete[](aaType); result = 1.5;}
		if( (strcmp(atomType, " O1 "	) == 0) && (strcmp(aaType, " O2 ")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O2 "	) == 0) && (strcmp(aaType, " O2 ")== 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " C  "	) == 0) && (strcmp(aaType, "CO" ) == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " O  "	) == 0) && (strcmp(aaType, "CO" ) == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, "DUM"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 0.0;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OH "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " P1 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " O2 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " O3 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O4 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HG "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OH "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " P1 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " O2 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.8;}
		if( (strcmp(atomType, " H2 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 0.2;}
		if( (strcmp(atomType, " O3 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O4 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OH "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " P1 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " O2 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O3 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O4 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " CG "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HG "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE1"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " HE2"	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.4;}
		if( (strcmp(atomType, " CZ "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.0;}
		if( (strcmp(atomType, " OH "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " P1 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 2.1;}
		if( (strcmp(atomType, " O2 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O3 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}
		if( (strcmp(atomType, " O4 "	) == 0) && (strcmp(aaType, "DUM") == 0) ) {delete[](atomType); delete[](aaType); result = 1.7;}

		if(result != -1){
			delete[](atomType);
			delete[](aaType);
			return result;
		}
		else{
			generalizedRadii = true;
		}
	}

	delete[](aaType);
	char atom = atomType[1];
	delete[](atomType);
	if(generalizedRadii == true){
		switch(atom){
			case 'C': result = 2.0; break;
			case 'O': result = 1.7; break;
			case 'P': result = 2.1; break;
			case 'H': result = 0.2; break;
			case 'N': result = 1.9; break;
			case 'S': result = 2.0; break;
			default: result = 1.7; break;			
		}
	}
	
	return result;
}




