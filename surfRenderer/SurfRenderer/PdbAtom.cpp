// PdbAtom.cpp: implementation of the PdbAtom class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PdbAtom::PdbAtom()
{

	atom_number = 0;
	atom_name = new char[15];
	residue_name = new char[15];
	residue_number = 0;
	coords = new double[3];

	significance = 0;
	spread_color = 0;

	fileLine = new char[NUMCOLUMNS];
	assocAA = NULL;							///in MatchXpander this is vestigial.  it is used as a convenience for parsing.

}

PdbAtom::~PdbAtom()
{

	delete[](atom_name);
	delete[](residue_name);
	delete[](fileLine);
	delete[](coords);
	if(assocAA != NULL){
		delete[](assocAA);
	}

}

PdbAtom * PdbAtom::copy()
{
	PdbAtom * result = new PdbAtom();
	strcpy(result->atom_name, atom_name);
	strcpy(result->residue_name, residue_name);
	strcpy(result->fileLine, fileLine);
	if(assocAA != NULL){
		result->assocAA = new char[strlen(assocAA)+1];
		strcpy(result->assocAA, assocAA);
	}else{
		result->assocAA = NULL;
	}

	result->atom_number = atom_number;
	result->residue_number = residue_number;
	result->significance = significance;
	result->spread_color = spread_color;
	result->coords[0] = coords[0];
	result->coords[1] = coords[1];
	result->coords[2] = coords[2];

	return result;
}

void PdbAtom::toString(void)
{
	printf("%i ", atom_number);
	printf("%s ", atom_name);
	printf("%s ", residue_name);
	printf("%i ", residue_number);
	printf("%lf ", coords[0]);
	printf("%lf ", coords[1]);
	printf("%lf ", coords[2]);
	printf("%i \n", significance);

}



/*
---------------------------------------------------------------------------
Field |    Column    | FORTRAN |                                         
  No. |     range    | format  | Description                                   
---------------------------------------------------------------------------
   1. |    1 -  6    |   A6    | Record ID (eg ATOM, HETATM)       
   2. |    7 - 11    |   I5    | Atom serial number                            
   -  |   12 - 12    |   1X    | Blank                                         
   3. |   13 - 16    |   A4    | Atom name (eg " CA " , " ND1")   
   4. |   17 - 17    |   A1    | Alternative location code (if any)            
   5. |   18 - 20    |   A3    | Standard 3-letter amino acid code for residue 
   -  |   21 - 21    |   1X    | Blank                                         
   6. |   22 - 22    |   A1    | Chain identifier code                         
   7. |   23 - 26    |   I4    | Residue sequence number                       
   8. |   27 - 27    |   A1    | Insertion code (if any)                       
   -  |   28 - 30    |   3X    | Blank                                         
   9. |   31 - 38    |  F8.3   | Atom's x-coordinate                         
  10. |   39 - 46    |  F8.3   | Atom's y-coordinate                         
  11. |   47 - 54    |  F8.3   | Atom's z-coordinate                         
  12. |   55 - 60    |  F6.2   | Occupancy value for atom                      
  13. |   61 - 66    |  F6.2   | B-value (thermal factor)                    
   -  |   67 - 67    |   1X    | Blank                                         
  14. |   68 - 70    |   I3    | Footnote number                               
---------------------------------------------------------------------------
*/
char * PdbAtom::pdbLine(void)
{
	char * result = new char[100];
	char * s = new char[20];

	int i = 0;
	for(i = 0; i<100; i++){ result[i] = ' '; }
	result[98] = '\n';
	result[99] = '\0';

	result[0]='A'; result[1]='T'; result[2]='O'; result[3]='M';

	sprintf(s, "% 5i", atom_number);
//	printf("atom number S: [%s]\n", s);
	result[6]=s[0]; result[7]=s[1]; result[8]=s[2]; result[9]=s[3]; result[10]=s[4];

	sprintf(s, "%s", atom_name);
//	printf("atom name S: [%s]\n", s);
	for(i = 0; i<strlen(s); i++){
		result[12+i] = s[i];
	}

	sprintf(s, "%s", residue_name);
//	printf("residue name S: [%s]\n", s);
	result[17]=s[0]; result[18]=s[1]; result[19]=s[2];

	sprintf(s, "% 4i", residue_number);
//	printf("residue numberS: [%s]\n", s);
	result[22]=s[0]; result[23]=s[1]; result[24]=s[2]; result[25]=s[3];

	sprintf(s, "% 8.3lf", coords[0]);
//	printf("X S: [%s]\n", s);
	result[30]=s[0]; result[31]=s[1]; result[32]=s[2]; result[33]=s[3]; result[34]=s[4]; result[35]=s[5]; result[36]=s[6]; result[37]=s[7];
	sprintf(s, "% 8.3lf", coords[1]);
//	printf("Y S: [%s]\n", s);
	result[38]=s[0]; result[39]=s[1]; result[40]=s[2]; result[41]=s[3]; result[42]=s[4]; result[43]=s[5]; result[44]=s[6]; result[45]=s[7];
	sprintf(s, "% 8.3lf", coords[2]);
//	printf("Z S: [%s]\n", s);
	result[46]=s[0]; result[47]=s[1]; result[48]=s[2]; result[49]=s[3]; result[50]=s[4]; result[51]=s[5]; result[52]=s[6]; result[53]=s[7];

//	printf("Result: [%s]\n", result);

	delete[](s);

	return result;
}



