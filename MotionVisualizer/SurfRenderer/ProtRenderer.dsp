# Microsoft Developer Studio Project File - Name="ProtRenderer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ProtRenderer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProtRenderer.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProtRenderer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ProtRenderer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "OPENGL_RENDERING" /D "INTERACTIVEMODE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ProtRenderer - Win32 Release"
# Name "ProtRenderer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_lalgebra.cpp
# End Source File
# Begin Source File

SOURCE=.\aminoAcid.cpp
# End Source File
# Begin Source File

SOURCE=.\atomBag.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomList.cpp
# End Source File
# Begin Source File

SOURCE=.\atomRadiusLookup.cpp
# End Source File
# Begin Source File

SOURCE=.\caList.cpp
# End Source File
# Begin Source File

SOURCE=.\funclib.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometryParser.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\mathlib.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\outputFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PdbAtom.cpp
# End Source File
# Begin Source File

SOURCE=.\pdbParser.cpp
# End Source File
# Begin Source File

SOURCE=.\PocketAlignment.cpp
# End Source File
# Begin Source File

SOURCE=.\prime.c
# End Source File
# Begin Source File

SOURCE=.\Renderer.cpp
# End Source File
# Begin Source File

SOURCE=.\set.c
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\SurfaceObject.cpp
# End Source File
# Begin Source File

SOURCE=.\SurfaceOutput.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_lalgebra.h
# End Source File
# Begin Source File

SOURCE=.\aminoAcid.h
# End Source File
# Begin Source File

SOURCE=.\atomBag.h
# End Source File
# Begin Source File

SOURCE=.\AtomList.h
# End Source File
# Begin Source File

SOURCE=.\atomRadiusLookup.h
# End Source File
# Begin Source File

SOURCE=.\caList.h
# End Source File
# Begin Source File

SOURCE=.\conf.h
# End Source File
# Begin Source File

SOURCE=.\defs.h
# End Source File
# Begin Source File

SOURCE=.\funclib.h
# End Source File
# Begin Source File

SOURCE=.\GeometryParser.h
# End Source File
# Begin Source File

SOURCE=.\mathlib.h
# End Source File
# Begin Source File

SOURCE=.\ObjRenderer.h
# End Source File
# Begin Source File

SOURCE=.\outputFile.h
# End Source File
# Begin Source File

SOURCE=.\PdbAtom.h
# End Source File
# Begin Source File

SOURCE=.\pdbParser.h
# End Source File
# Begin Source File

SOURCE=.\PocketAlignment.h
# End Source File
# Begin Source File

SOURCE=.\prime.h
# End Source File
# Begin Source File

SOURCE=.\Renderer.h
# End Source File
# Begin Source File

SOURCE=.\set.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SurfaceObject.h
# End Source File
# Begin Source File

SOURCE=.\SurfaceOutput.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\glui32.lib
# End Source File
# End Group
# End Target
# End Project
