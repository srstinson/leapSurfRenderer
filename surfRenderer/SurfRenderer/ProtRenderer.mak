# Microsoft Developer Studio Generated NMAKE File, Based on ProtRenderer.dsp
!IF "$(CFG)" == ""
CFG=ProtRenderer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ProtRenderer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ProtRenderer - Win32 Release" && "$(CFG)" != "ProtRenderer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProtRenderer.mak" CFG="ProtRenderer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProtRenderer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ProtRenderer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ProtRenderer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ProtRenderer.exe"


CLEAN :
	-@erase "$(INTDIR)\_lalgebra.obj"
	-@erase "$(INTDIR)\aminoAcid.obj"
	-@erase "$(INTDIR)\atomBag.obj"
	-@erase "$(INTDIR)\AtomList.obj"
	-@erase "$(INTDIR)\atomRadiusLookup.obj"
	-@erase "$(INTDIR)\caList.obj"
	-@erase "$(INTDIR)\funclib.obj"
	-@erase "$(INTDIR)\GeometryParser.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\mathlib.obj"
	-@erase "$(INTDIR)\ObjRenderer.obj"
	-@erase "$(INTDIR)\outputFile.obj"
	-@erase "$(INTDIR)\PdbAtom.obj"
	-@erase "$(INTDIR)\pdbParser.obj"
	-@erase "$(INTDIR)\PocketAlignment.obj"
	-@erase "$(INTDIR)\prime.obj"
	-@erase "$(INTDIR)\Renderer.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SurfaceObject.obj"
	-@erase "$(INTDIR)\SurfaceOutput.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ProtRenderer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ProtRenderer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProtRenderer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ProtRenderer.pdb" /machine:I386 /out:"$(OUTDIR)\ProtRenderer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\_lalgebra.obj" \
	"$(INTDIR)\aminoAcid.obj" \
	"$(INTDIR)\atomBag.obj" \
	"$(INTDIR)\AtomList.obj" \
	"$(INTDIR)\atomRadiusLookup.obj" \
	"$(INTDIR)\caList.obj" \
	"$(INTDIR)\funclib.obj" \
	"$(INTDIR)\GeometryParser.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\mathlib.obj" \
	"$(INTDIR)\ObjRenderer.obj" \
	"$(INTDIR)\outputFile.obj" \
	"$(INTDIR)\PdbAtom.obj" \
	"$(INTDIR)\pdbParser.obj" \
	"$(INTDIR)\PocketAlignment.obj" \
	"$(INTDIR)\prime.obj" \
	"$(INTDIR)\Renderer.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SurfaceObject.obj" \
	"$(INTDIR)\SurfaceOutput.obj" \
	".\glui32.lib"

"$(OUTDIR)\ProtRenderer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ProtRenderer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ProtRenderer.exe"


CLEAN :
	-@erase "$(INTDIR)\_lalgebra.obj"
	-@erase "$(INTDIR)\aminoAcid.obj"
	-@erase "$(INTDIR)\atomBag.obj"
	-@erase "$(INTDIR)\AtomList.obj"
	-@erase "$(INTDIR)\atomRadiusLookup.obj"
	-@erase "$(INTDIR)\caList.obj"
	-@erase "$(INTDIR)\funclib.obj"
	-@erase "$(INTDIR)\GeometryParser.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\mathlib.obj"
	-@erase "$(INTDIR)\ObjRenderer.obj"
	-@erase "$(INTDIR)\outputFile.obj"
	-@erase "$(INTDIR)\PdbAtom.obj"
	-@erase "$(INTDIR)\pdbParser.obj"
	-@erase "$(INTDIR)\PocketAlignment.obj"
	-@erase "$(INTDIR)\prime.obj"
	-@erase "$(INTDIR)\Renderer.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SurfaceObject.obj"
	-@erase "$(INTDIR)\SurfaceOutput.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ProtRenderer.exe"
	-@erase "$(OUTDIR)\ProtRenderer.ilk"
	-@erase "$(OUTDIR)\ProtRenderer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "OPENGL_RENDERING" /D "INTERACTIVEMODE" /Fp"$(INTDIR)\ProtRenderer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProtRenderer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ProtRenderer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ProtRenderer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\_lalgebra.obj" \
	"$(INTDIR)\aminoAcid.obj" \
	"$(INTDIR)\atomBag.obj" \
	"$(INTDIR)\AtomList.obj" \
	"$(INTDIR)\atomRadiusLookup.obj" \
	"$(INTDIR)\caList.obj" \
	"$(INTDIR)\funclib.obj" \
	"$(INTDIR)\GeometryParser.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\mathlib.obj" \
	"$(INTDIR)\ObjRenderer.obj" \
	"$(INTDIR)\outputFile.obj" \
	"$(INTDIR)\PdbAtom.obj" \
	"$(INTDIR)\pdbParser.obj" \
	"$(INTDIR)\PocketAlignment.obj" \
	"$(INTDIR)\prime.obj" \
	"$(INTDIR)\Renderer.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SurfaceObject.obj" \
	"$(INTDIR)\SurfaceOutput.obj" \
	".\glui32.lib"

"$(OUTDIR)\ProtRenderer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ProtRenderer.dep")
!INCLUDE "ProtRenderer.dep"
!ELSE 
!MESSAGE Warning: cannot find "ProtRenderer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ProtRenderer - Win32 Release" || "$(CFG)" == "ProtRenderer - Win32 Debug"
SOURCE=.\_lalgebra.cpp

"$(INTDIR)\_lalgebra.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\aminoAcid.cpp

"$(INTDIR)\aminoAcid.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\atomBag.cpp

"$(INTDIR)\atomBag.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AtomList.cpp

"$(INTDIR)\AtomList.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\atomRadiusLookup.cpp

"$(INTDIR)\atomRadiusLookup.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\caList.cpp

"$(INTDIR)\caList.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\funclib.cpp

"$(INTDIR)\funclib.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GeometryParser.cpp

"$(INTDIR)\GeometryParser.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mathlib.cpp

"$(INTDIR)\mathlib.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ObjRenderer.cpp

"$(INTDIR)\ObjRenderer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\outputFile.cpp

"$(INTDIR)\outputFile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PdbAtom.cpp

"$(INTDIR)\PdbAtom.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pdbParser.cpp

"$(INTDIR)\pdbParser.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PocketAlignment.cpp

"$(INTDIR)\PocketAlignment.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\prime.c

"$(INTDIR)\prime.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Renderer.cpp

"$(INTDIR)\Renderer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\set.c

"$(INTDIR)\set.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SurfaceObject.cpp

"$(INTDIR)\SurfaceObject.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SurfaceOutput.cpp

"$(INTDIR)\SurfaceOutput.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

