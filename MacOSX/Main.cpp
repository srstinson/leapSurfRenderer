/******************************************************************************\
 * Copyright (C) Leap Motion, Inc. 2011-2013.                                   *
 * Leap Motion proprietary and  confidential.  Not for distribution.            *
 * Use subject to the terms of the Leap Motion SDK Agreement available at       *
 * https://developer.leapmotion.com/sdk_agreement, or another agreement between *
 * Leap Motion and you, your company or other organization.                     *
 \******************************************************************************/
#include "../JuceLibraryCode/JuceHeader.h"
#include "Leap.h"
#include "LeapUtilGL.h"
#include <cctype>
#include "StdAfx.h"
#include <string>
#include <math.h>
#include <dirent.h>
#include <iostream>

class MotionVisualizerWindow;
class OpenGLCanvas;

CriticalSection mutex;

std::vector<std::string> GetAllFilesWithExtension(const std::string & ext);
void setSurfaces(Boolean loadSurfaces);
void groupPointerRight();
void groupPointerLeft();
void surfacePointerRight(int surfFoc);
void surfacePointerLeft(int surfFoc);
void moveSurface();
void saveSurfSets();

static const float kfNumGrids   = 15.0f;
static const float kfGridScale  = 120.0f;

int main_window;		///referenced by GLUI to get back to the main window

//GLUI windows
//GLUI * Renderer::glui_controls;

float aspectRatio;
float * obj_pos;
float * obj_rot;
float * obj_rotx;
float * obj_roty;
int * drawAxes;
int * useCentroid;
//GLUI_EditText * Renderer::glui_input_file_field;
//GLUI_EditText * Renderer::glui_output_file_field;

SurfaceObject * surf = NULL;
SurfaceObject * surfCompared = NULL;

///my stuff
char * outputFileName;
char * inputFileName;

//	static int numProts;
set_t drawProt;		//int ** drawProt;
set_t lists;			//AtomList ** lists;
set_t list_pos;		//float ** list_pos;
set_t list_rot;		//float ** list_rot;

///surface-based rendering
//	static int numSurfs;
set_t drawSurf;		//int ** drawSurf;
set_t transSurf;		//int ** transSurf;
set_t surfs;			//SurfaceObject ** surfs;
set_t surf_pos;		//float ** surf_pos;
set_t surf_rot;		//float ** surf_rot;
double * centroid;	///double * centroid

int keyFlag;

int background;

std::vector<std::string> surfSets;
std::vector<std::vector<std::string>> surfsInSet;

std::string currentFile;
std::string comparedFile;

int surfSetIndex = 0;
int surfIndex1 = -1;
int surfIndex2 = -1;

float angleX = 0;
float angleY = 0;

//==============================================================================
class MotionVisualizerApplication  : public JUCEApplication
{
public:
    //==============================================================================
    MotionVisualizerApplication()
    {
    }
    
    ~MotionVisualizerApplication()
    {
    }
    
    //==============================================================================
    void initialise (const String& commandLine);
    
    void shutdown()
    {
        // Do your application's shutdown code here..
        
    }
    
    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }
    
    //==============================================================================
    const String getApplicationName()
    {
        return "Leap Motion Visualizer";
    }
    
    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }
    
    bool moreThanOneInstanceAllowed()
    {
        return true;
    }
    
    void anotherInstanceStarted (const String& commandLine)
    {
        (void)commandLine;
    }
    
    static Leap::Controller& getController()
    {
        static Leap::Controller s_controller;
        
        return  s_controller;
    }
    
private:
    ScopedPointer<MotionVisualizerWindow>  m_pMainWindow;
};

//==============================================================================
class OpenGLCanvas  : public Component,
public OpenGLRenderer,
Leap::Listener
{
public:
    enum
    {
        kFlag_FPS         = 1 << 0,
        kFlag_Help        = 1 << 1,
        kFlag_RedBlue3D   = 1 << 2,
        
        kFlag_Transparent   = 1 << 3,
        kFlag_Rotate      = 1 << 4,
        kFlag_Scale       = 1 << 5,
        kFlag_Automatic   = 1 << 6,
        
        kFlag_AutoDetectedTranslate   = 1 << 7,
        kFlag_AutoDetectedRotate      = 1 << 8,
        kFlag_AutoDetectedScale       = 1 << 9,
        kFlags_AutoDetectedTransforms = kFlag_AutoDetectedTranslate|kFlag_AutoDetectedRotate|kFlag_AutoDetectedScale,
    };
    
    enum eDrawMode
    {
        kDraw_Normal,
        kDraw_3DLeft,
        kDraw_3DRight
    };
    
    OpenGLCanvas()
    : Component( "OpenGLCanvas" )
    {
        m_openGLContext.setRenderer (this);
        m_openGLContext.setComponentPaintingEnabled (true);
        m_openGLContext.attachTo (*this);
        setBounds( 0, 0, 1024, 768 );
        
        m_fLastUpdateTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
        m_fLastRenderTimeSeconds = m_fLastUpdateTimeSeconds;
        
        MotionVisualizerApplication::getController().addListener( *this );
        
        resetCamera();
        
        setWantsKeyboardFocus( true );
        
        m_uiFlags = kFlag_Rotate | kFlag_Scale | kFlag_Transparent | kFlag_Automatic;
        
        updateStateStr();
        
        m_strPrompt = "Press 'H' for help";
        
        m_strHelp = "ESC - quit\n"
        "H - Toggle help and frame rate display\n"
        "A - Toggle automatic motion tracking\n"
        "R - Toggle rotation tracking\n"
        "S - Toggle scale tracking\n"
        "T - Toggle translation tracking\n"
        "3 - Toggle red/blue 3D mode\n"
        "Page Up   - Increase left/right eye separation\n"
        "Page Down - Decrease left/right eye separation\n"
        "Space     - Reset the scene and camera";
        
        m_fTotalMotionScale = 1.0f;
        
        m_fLeftRightEyeShift = 2.0f;
        
        m_strSave = "[S]ave";
        
        m_strFile = "[F]ile: ";
    }
    
    ~OpenGLCanvas()
    {
        MotionVisualizerApplication::getController().removeListener( *this );
        m_openGLContext.detach();
    }
    
    void newOpenGLContextCreated()
    {
        glEnable(GL_BLEND);
        
        glEnable(GL_DEPTH_TEST);
        glDepthMask(true);
        glDepthFunc(GL_LESS);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        
        m_fixedFont = Font("Courier New", 24, Font::plain );
        m_uiFlags ^= kFlag_Transparent;
        m_uiFlags ^= kFlag_Rotate;
        m_uiFlags ^= kFlag_Scale;
    }
    
    void openGLContextClosing()
    {
    }
    
    bool keyPressed( const KeyPress& keyPress )
    {
        if (keyFlag == 0){
            int iKeyCode = toupper(keyPress.getKeyCode());
            
            if ( iKeyCode == KeyPress::escapeKey )
            {
                JUCEApplication::quit();
                return true;
            }
            
            if ( iKeyCode == KeyPress::pageUpKey )
            {
                float fStep = (m_fLeftRightEyeShift < 1.0f) ? 0.05f : ((m_fLeftRightEyeShift < 5.0f)  ? 0.25f : 1.0f);
                m_fLeftRightEyeShift = LeapUtil::Min( m_fLeftRightEyeShift + fStep, 50.0f );
                updateStateStr();
                return true;
            }
            
            if ( iKeyCode == KeyPress::pageDownKey )
            {
                float fStep = (m_fLeftRightEyeShift > 5.0f) ? 1.0f : ((m_fLeftRightEyeShift > 1.0f)  ? 0.25f : 0.05f);
                m_fLeftRightEyeShift = LeapUtil::Max( m_fLeftRightEyeShift - fStep, 0.0f );
                updateStateStr();
                return true;
            }
            
            if ( iKeyCode == KeyPress::rightKey )
            {
                groupPointerRight();
                return true;
            }
            
            if ( iKeyCode == KeyPress::leftKey )
            {
                groupPointerLeft();
                return true;
            }
            
            if ( iKeyCode == KeyPress::upKey )
            {
                surfacePointerRight(0);
                return true;
            }
            
            if ( iKeyCode == KeyPress::downKey )
            {
                surfacePointerLeft(0);
                return true;
            }
            
            if ( iKeyCode == '.' )
            {
                surfacePointerRight(1);
                return true;
            }
            
            if ( iKeyCode == ',' )
            {
                surfacePointerLeft(1);
                return true;
            }
            
            switch ( iKeyCode )
            {
                case ' ':
                    resetScene();
                    resetCamera();
                    return true;
                    
                case '3':
                    m_uiFlags ^= kFlag_RedBlue3D;
                    break;
                    
                case 'A':
                    m_uiFlags ^= kFlag_Automatic;
                    break;
                    
                case 'H':
                    //m_uiFlags ^= (kFlag_Help | kFlag_FPS);
                    return true;
                    
                case 'R':
                    m_uiFlags ^= kFlag_Rotate;
                    break;
                    
                case 'Z':
                    m_uiFlags ^= kFlag_Scale;
                    break;
                    
                case 'S':
                    saveSurfSets();
                    break;
                    
                case 'T':
                    m_uiFlags ^= kFlag_Transparent;
                    break;
                    
                case 'F':
                    currentFile = "";
                    surfIndex1 = -1;
                    surfIndex2 = -2;
                    surfSetIndex = 0;
                    keyFlag = 1;
                    break;
                    
                case 'C':
                    comparedFile = "";
                    surfIndex1 = -1;
                    surfIndex2 = -2;
                    surfSetIndex = 0;
                    keyFlag = 2;
                    break;
                    
                case 'M':
                    moveSurface();
                    break;
                    
                default:
                    return false;
            }
            
            updateStateStr();
        }
        else if(keyFlag == 1){
            int iKeyCode = keyPress.getKeyCode();
            if(iKeyCode == KeyPress::returnKey){
                setSurfaces(false);
                /*obj_rotx[0] = 1.0;	obj_rotx[1] = 0.0;	obj_rotx[2] = 0.0;	obj_rotx[3] = 0.0;
                 obj_rotx[4] = 0.0;	obj_rotx[5] = 1.0;	obj_rotx[6] = 0.0;	obj_rotx[7] = 0.0;
                 obj_rotx[8] = 0.0;	obj_rotx[9] = 0.0;	obj_rotx[10] = 1.0;	obj_rotx[11] = 0.0;
                 obj_rotx[12] = 0.0;	obj_rotx[13] = 0.0;	obj_rotx[14] = 0.0;	obj_rotx[15] = 1.0;
                 obj_roty[0] = 1.0;	obj_roty[1] = 0.0;	obj_roty[2] = 0.0;	obj_roty[3] = 0.0;
                 obj_roty[4] = 0.0;	obj_roty[5] = 1.0;	obj_roty[6] = 0.0;	obj_roty[7] = 0.0;
                 obj_roty[8] = 0.0;	obj_roty[9] = 0.0;	obj_roty[10] = 1.0;	obj_roty[11] = 0.0;
                 obj_roty[12] = 0.0;	obj_roty[13] = 0.0;	obj_roty[14] = 0.0;	obj_roty[15] = 1.0;*/
                keyFlag = 0;
            }
            else if(iKeyCode == KeyPress::backspaceKey){
                if (currentFile.size() > 0)  currentFile.resize(currentFile.size () - 1);
                //std::cout<<"Yep"<<std::endl;
            }
            else{
                char cKeyCode = keyPress.getTextCharacter();
                currentFile += cKeyCode;
                std::cout<<cKeyCode<<std::endl;
            }
        }
        else{
            int iKeyCode = keyPress.getKeyCode();
            if(iKeyCode == KeyPress::returnKey){
                setSurfaces(false);
                /*obj_rotx[0] = 1.0;	obj_rotx[1] = 0.0;	obj_rotx[2] = 0.0;	obj_rotx[3] = 0.0;
                 obj_rotx[4] = 0.0;	obj_rotx[5] = 1.0;	obj_rotx[6] = 0.0;	obj_rotx[7] = 0.0;
                 obj_rotx[8] = 0.0;	obj_rotx[9] = 0.0;	obj_rotx[10] = 1.0;	obj_rotx[11] = 0.0;
                 obj_rotx[12] = 0.0;	obj_rotx[13] = 0.0;	obj_rotx[14] = 0.0;	obj_rotx[15] = 1.0;
                 obj_roty[0] = 1.0;	obj_roty[1] = 0.0;	obj_roty[2] = 0.0;	obj_roty[3] = 0.0;
                 obj_roty[4] = 0.0;	obj_roty[5] = 1.0;	obj_roty[6] = 0.0;	obj_roty[7] = 0.0;
                 obj_roty[8] = 0.0;	obj_roty[9] = 0.0;	obj_roty[10] = 1.0;	obj_roty[11] = 0.0;
                 obj_roty[12] = 0.0;	obj_roty[13] = 0.0;	obj_roty[14] = 0.0;	obj_roty[15] = 1.0;*/
                keyFlag = 0;
            }
            else if(iKeyCode == KeyPress::backspaceKey){
                if (comparedFile.size() > 0)  comparedFile.resize(comparedFile.size () - 1);
                //std::cout<<"Yep"<<std::endl;
            }
            else{
                char cKeyCode = keyPress.getTextCharacter();
                comparedFile += cKeyCode;
                std::cout<<cKeyCode<<std::endl;
            }
        }
        return true;
    }
    
    void updateStateStr()
    {
        m_aStrState[0] = String::empty;
        m_aStrState[1] = String::empty;
        m_aStrState[2] = String::empty;
        
        m_aStrState[0]  << "[T]ransparency: " << LeapUtil::BoolToStr( m_uiFlags & kFlag_Transparent );
        m_aStrState[1]  << "[R]otate: "    << LeapUtil::BoolToStr( m_uiFlags & kFlag_Rotate );
        m_aStrState[2]  << "[Z]oom: "     << LeapUtil::BoolToStr( m_uiFlags & kFlag_Scale );
        
    }
    
    void mouseDown (const MouseEvent& e)
    {
        (void)e;
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        (void)e;
        double angleDirectionX = e.getDistanceFromDragStartX();
        double angleDirectionY = e.getDistanceFromDragStartY();
        
        int direction = 0;
        
        
        if (fabs(angleDirectionX) > fabs(angleDirectionY)){
            //rotate about y
            direction = 1;
        }
        else if(fabs(angleDirectionY) > fabs(angleDirectionX)){
            //rotate  about x
            direction = 2;
        }
        
        if (direction == 1){
            if(angleDirectionX > 0){
                angleY = fmod((angleY + 0.05),2*PI);
            }
            else{
                angleY = fmod((angleY - 0.05),2*PI);
            }
            obj_roty[0] = cos(angleY);
            obj_roty[2] = -1*sin(angleY);
            obj_roty[8] = sin(angleY);
            obj_roty[10] = cos(angleY);
        }
        else if (direction == 2){
            if(angleDirectionY > 0){
                angleX = fmod((angleX + 0.05),2*PI);
            }
            else{
                angleX = fmod((angleX - 0.05),2*PI);
            }
            obj_rotx[5] = cos(angleX);
            obj_rotx[6] = sin(angleX);
            obj_rotx[9] = -1*sin(angleX);
            obj_rotx[10] = cos(angleX);
        }
    }
    
    void mouseWheelMove ( const MouseEvent& e,
                         const MouseWheelDetails& wheel )
    {
        (void)e;
        (void)wheel;
        static const float kfMinScale = 0.1f;
        static const float kfMaxScale = 2.0f;
        bool scaleDirection = wheel.deltaY >= 0;
        if(scaleDirection){
            m_fTotalMotionScale = LeapUtil::Clamp(  m_fTotalMotionScale * float(1.05),kfMinScale,kfMaxScale );
        }
        else{
            m_fTotalMotionScale = LeapUtil::Clamp(  m_fTotalMotionScale * float(0.95),kfMinScale,kfMaxScale );
        }
    }
    
    void resized()
    {
    }
    
    void paint(Graphics& g)
    {
        (void)g;
    }
    
    void renderOpenGL2D()
    {
        LeapUtilGL::GLAttribScope attribScope( GL_ENABLE_BIT );
        
        // when enabled text draws poorly.
        glDisable(GL_CULL_FACE);
        
        ScopedPointer<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (m_openGLContext, getWidth(), getHeight()));
        
        if (glRenderer == nullptr)
        {
            return;
        }
        
        Graphics g(glRenderer);
        
        int iMargin   = 10;
        int iFontSize = static_cast<int>(m_fixedFont.getHeight());
        int iLineStep = iFontSize + (iFontSize >> 2);
        int iBaseLine = 20;
        Font origFont = g.getCurrentFont();
        
        const Rectangle<int>& rectBounds = getBounds();
        
        g.setFont( static_cast<float>(iFontSize) );
        
        g.setColour( Colours::salmon );
        //g.drawSingleLineText( m_strPrompt, iMargin, iBaseLine );
        m_strFile += currentFile.c_str();
        m_strCompFile += comparedFile.c_str();
        g.drawSingleLineText( m_strSave, iMargin, iBaseLine);
        g.drawSingleLineText( m_strFile, iMargin, iBaseLine + iLineStep );
        g.drawSingleLineText( m_strCompFile, iMargin, iBaseLine + 2*iLineStep );
        m_strFile = "[F]ile: ";
        m_strCompFile = "[C]ompare File: ";
        
        if ( m_uiFlags & kFlag_FPS )
        {
            g.setColour( Colours::seagreen );
            g.drawSingleLineText( m_strUpdateFPS, iMargin, iBaseLine + iLineStep );
            g.drawSingleLineText( m_strRenderFPS, iMargin, iBaseLine + iLineStep*2 );
        }
        
        if ( m_uiFlags & kFlag_Help )
        {
            g.setFont( m_fixedFont );
            g.setColour( Colours::slateblue );
            g.drawMultiLineText( m_strHelp,
                                iMargin,
                                iBaseLine + iLineStep * 3,
                                rectBounds.getWidth() - iMargin*2 );
        }
        
        g.setFont( origFont );
        g.setFont( static_cast<float>(iFontSize) );
        
        g.setColour( Colours::orange );
        
        for ( int i = 2, uiTotalWidth = 0; i >= 0; i-- )
        {
            if ( !m_aStrState[i].isEmpty() )
            {
                const uint32_t uiStrWidth = g.getCurrentFont().getStringWidth( m_aStrState[i] );
                
                if ( (i < 3) && (m_uiFlags & kFlag_Automatic) )
                {
                    const uint32_t uiXformFlags = (kFlag_Transparent << i)|(kFlag_AutoDetectedTranslate << i);
                    const bool bDidTransform =  (m_uiFlags & uiXformFlags) == uiXformFlags;
                    g.setColour( bDidTransform ? Colours::gold : Colours::grey );
                }
                
                g.drawSingleLineText( m_aStrState[i],
                                     rectBounds.getRight() - iMargin - uiTotalWidth,
                                     rectBounds.getBottom() - (iFontSize*2),
                                     Justification::right );
                
                uiTotalWidth += uiStrWidth + iFontSize;
            }
        }
        m_strGroup = "Group: ";
        //std::cout<<surfSetIndex<<std::endl;
        for(int i = 0; i < surfSets.size() + 1; i++){
            if(i ==surfSetIndex){m_strGroup += "[";}
            m_strGroup += i;
            if(i ==surfSetIndex){m_strGroup += "]";}
            m_strGroup += " ";
        }
        g.setColour( Colours::orange );
        g.drawSingleLineText( m_strGroup,
                             rectBounds.getCentreX(),
                             rectBounds.getBottom() - 2*(iFontSize*2),
                             Justification::horizontallyCentred );
        m_strIndividual = "Surfs: ";
        //std::cout<<surfSets.size()<<std::endl;
        if(surfSetIndex >= 1){
            for(int i = 0; i < surfsInSet[surfSetIndex-1].size(); i++){
                if(i ==surfIndex1){m_strIndividual += "[";}
                if(i ==surfIndex2){m_strIndividual += "{";}
                m_strIndividual += i;
                if(i ==surfIndex2){m_strIndividual += "}";}
                if(i ==surfIndex1){m_strIndividual += "]";}
                m_strIndividual += " ";
            }
            g.setColour( Colours::orange );
            g.drawSingleLineText( m_strIndividual,
                                 rectBounds.getCentreX(),
                                 rectBounds.getBottom() - 3*(iFontSize*2),
                                 Justification::horizontallyCentred );
        }
    }
    
    //
    // calculations that should only be done once per leap data frame but may be drawn many times should go here.
    //
    void update( Leap::Frame frame )
    {
        ScopedLock sceneGraphLock(m_renderMutex);
        
        double curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
        
        float deltaTimeSeconds = static_cast<float>(curSysTimeSeconds - m_fLastUpdateTimeSeconds);
        
        m_fLastUpdateTimeSeconds = curSysTimeSeconds;
        
        float fUpdateDT  = m_avgUpdateDeltaTime.AddSample( deltaTimeSeconds );
        float fUpdateFPS = (fUpdateDT > 0) ? 1.0f/fUpdateDT : 0.0f;
        m_strUpdateFPS = String::formatted( "UpdateFPS: %4.2f", fUpdateFPS );
        
        static const float kfMinScale = 0.1f;
        
        static const float kfMaxScale = 2.0f;
        
        //If automatic motion type detection is enabled, check if motion probabilities are above threshold amounts
        bool bShouldTranslate = true;
        bool bShouldRotate    = true;
        bool bShouldScale     = true;
        
        m_uiFlags &= ~(kFlags_AutoDetectedTransforms);
        
        if ( m_uiFlags & kFlag_Automatic )
        {
            bShouldTranslate = false;//frame.translationProbability(m_lastFrame) > 0.40;
            bShouldRotate    = frame.translationProbability(m_lastFrame)    > 0.60;
            bShouldScale     = frame.translationProbability(m_lastFrame)    > 0.80;
            
            m_uiFlags |= bShouldTranslate ? kFlag_AutoDetectedTranslate : 0;
            m_uiFlags |= bShouldRotate ? kFlag_AutoDetectedRotate : 0;
            m_uiFlags |= bShouldScale ? kFlag_AutoDetectedScale : 0;
        }
        
        //Update the translation in the current reference frame
        if (( m_uiFlags & kFlag_Transparent ) && bShouldTranslate)
        {
            //m_vTotalMotionTranslation += m_mtxTotalMotionRotation.rigidInverse().transformDirection(frame.translation(m_lastFrame));
        }
        
        //Update the rotation
        if (( m_uiFlags & kFlag_Rotate ) && bShouldRotate && !frame.fingers().isEmpty())
        {
            double angleDirectionX = frame.translation(m_lastFrame).x;
            double angleDirectionY = frame.translation(m_lastFrame).z;
            
            int direction = 0;
            
            if ((fabs(angleDirectionX) > fabs(angleDirectionY))){
                //rotate about y
                direction = 1;
            }
            else if ((fabs(angleDirectionY) > fabs(angleDirectionX))){
                //rotate about x
                direction = 2;
            }
            
            if (direction == 1){
                if(angleDirectionX > 0){
                    angleY = fmod((angleY + 0.05),2*PI);
                }
                else{
                    angleY = fmod((angleY - 0.05),2*PI);
                }
                obj_roty[0] = cos(angleY);
                obj_roty[2] = -1*sin(angleY);
                obj_roty[8] = sin(angleY);
                obj_roty[10] = cos(angleY);
            }
            else if (direction == 2){
                if(angleDirectionY > 0){
                    angleX = fmod((angleX + 0.05),2*PI);
                }
                else{
                    angleX = fmod((angleX - 0.05),2*PI);
                }
                obj_rotx[5] = cos(angleX);
                obj_rotx[6] = sin(angleX);
                obj_rotx[9] = -1*sin(angleX);
                obj_rotx[10] = cos(angleX);
            }
            
        }
        
        //Update the scale
        if (( m_uiFlags & kFlag_Scale ) && bShouldScale && !frame.fingers().isEmpty())
        {
            bool scaleDirection = frame.translation(m_lastFrame).y >= 0;
            if(scaleDirection){
                m_fTotalMotionScale = LeapUtil::Clamp(  m_fTotalMotionScale * float(1.05),kfMinScale,kfMaxScale );
            }
            else{
                m_fTotalMotionScale = LeapUtil::Clamp(  m_fTotalMotionScale * float(0.95),kfMinScale,kfMaxScale );
            }
        }
        
    }
    
    /// affects model view matrix.  needs to be inside a glPush/glPop matrix block!
    void setupScene()
    {
        OpenGLHelpers::clear( Colours::black.withAlpha(0.0f) );
        
        m_camera.SetAspectRatio( getWidth() / static_cast<float>(getHeight()) );
        
        m_camera.SetupGLProjection();
        
        m_camera.SetupGLView();
        
        /// JUCE turns off the depth test every frame when calling paint.
        glEnable(GL_DEPTH_TEST);
        glDepthMask(true);
        glDepthFunc(GL_LESS);
        
        glEnable(GL_BLEND);
        glDisable(GL_LIGHTING);
        
        
    }
    
    void drawScene( eDrawMode drawMode )
    {
        LeapUtilGL::GLMatrixScope sceneMatrixScope;
        
        Leap::Vector vColor( 0.5, 1, 1 );
        
        //Set the 3D grid transformation matrix
        //        glMultMatrixf(m_mtxTotalMotionRotation.toArray4x4());
        //        glTranslatef(m_vTotalMotionTranslation.x, m_vTotalMotionTranslation.y, m_vTotalMotionTranslation.z);
        glScalef(m_fTotalMotionScale, m_fTotalMotionScale, m_fTotalMotionScale);
        
        //Draw the infinite grid
        static const float kfSide = kfNumGrids*kfGridScale*0.5f;
        static const float kfAtten = kfGridScale*kfGridScale;
        
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        
        for ( float i = -kfSide; i < kfSide; i += kfGridScale)
        {
            for ( float j = -kfSide; j < kfSide; j += kfGridScale)
            {
                for ( float k = -kfSide; k < kfSide; k += kfGridScale)
                {
                    const float fIntens1 = kfAtten/((m_vTotalMotionTranslation + Leap::Vector(i, j, k)).magnitudeSquared() + kfAtten);
                    const float fIntens2 = kfAtten/((m_vTotalMotionTranslation + Leap::Vector(i+kfGridScale, j, k)).magnitudeSquared() + kfAtten);
                    const float fIntens3 = kfAtten/((m_vTotalMotionTranslation + Leap::Vector(i, j+kfGridScale, k)).magnitudeSquared() + kfAtten);
                    const float fIntens4 = kfAtten/((m_vTotalMotionTranslation + Leap::Vector(i, j, k+kfGridScale)).magnitudeSquared() + kfAtten);
                    
                    const Leap::Vector vColor1 = vColor * fIntens1;
                    const Leap::Vector vColor2 = vColor * fIntens2;
                    const Leap::Vector vColor3 = vColor * fIntens3;
                    const Leap::Vector vColor4 = vColor * fIntens4;
                    
                    glColor3fv( vColor1.toFloatPointer() );
                    glVertex3f(i, j, k);
                    
                    glColor3fv( vColor2.toFloatPointer() );
                    glVertex3f(i + kfGridScale, j, k);
                    
                    glColor3fv( vColor1.toFloatPointer() );
                    glVertex3f(i, j, k);
                    
                    glColor3fv( vColor3.toFloatPointer() );
                    glVertex3f(i, j + kfGridScale, k);
                    
                    glColor3fv( vColor1.toFloatPointer() );
                    glVertex3f(i, j, k);
                    
                    glColor3fv( vColor4.toFloatPointer() );
                    glVertex3f(i, j, k + kfGridScale);
                }
            }
        }
        
        glEnd();
        
        background = 0;
        
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
        
        
        if (currentFile.compare("") != 0 && keyFlag == 0){
            
            if(surf == NULL){
                printf("File not found! Try again.\n");
            }
            else{
                glMultMatrixf(obj_rotx);
                glMultMatrixf(obj_roty);
                glTranslatef(m_vTotalMotionTranslation.x, m_vTotalMotionTranslation.y, m_vTotalMotionTranslation.z);
                glPushMatrix(); ///store global position on the matrix stack
                
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
                
                glTranslatef(-surf->centroid[0], -surf->centroid[1], -surf->centroid[2]);
                mutex.enter();
                surf->draw(false, false, (m_uiFlags & kFlag_Transparent), true, NULL, NULL);
                if(comparedFile != ""){
                    //glTranslatef(-surfCompared->centroid[0], -surfCompared->centroid[1], -surfCompared->centroid[2]);
                    surfCompared->draw(false, false, true, true, NULL, NULL);
                }
                mutex.exit();
                glPopMatrix();
            }
        }
    }
    
    // data should be drawn here but no heavy calculations done.
    // any major calculations that only need to be updated per leap data frame
    // should be handled in update and cached in members.
    void renderOpenGL()
    {
        {
            MessageManagerLock mm (Thread::getCurrentThread());
            if (! mm.lockWasGained())
                return;
        }
        
        Leap::Frame frame = m_lastFrame;
        
        double  fCurSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
        float   fRenderDT = static_cast<float>(fCurSysTimeSeconds - m_fLastRenderTimeSeconds);
        fRenderDT = m_avgRenderDeltaTime.AddSample( fRenderDT );
        
        m_fLastRenderTimeSeconds = fCurSysTimeSeconds;
        
        float fRenderFPS = (fRenderDT > 0) ? 1.0f/fRenderDT : 0.0f;
        
        m_strRenderFPS = String::formatted( "RenderFPS: %4.2f", fRenderFPS );
        
        LeapUtilGL::GLMatrixScope sceneMatrixScope;
        
        setupScene();
        
        {
            LeapUtilGL::GLAttribScope sceneAttribScope( GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
            
            if ( m_uiFlags & kFlag_RedBlue3D )
            {
                glEnable(GL_BLEND);
                glDisable(GL_DEPTH_TEST);
                glBlendFunc(GL_ONE, GL_ONE);
                drawScene( kDraw_3DLeft );
                drawScene( kDraw_3DRight );
            }
            else
            {
                drawScene( kDraw_Normal );
            }
        }
        
        {
            float fBottomPos      = -0.35f;
            float fLeftPos        = fBottomPos * m_camera.GetAspectRatio();
            Leap::Vector vAxisPos = m_camera.GetPOV().transformPoint( Leap::Vector( fLeftPos, fBottomPos, -1.0f ) );
            
            // draw the frame transform orientation axes
            glTranslatef( vAxisPos.x, vAxisPos.y, vAxisPos.z );
            glMultMatrixf( m_mtxTotalMotionRotation.toArray4x4() );
            glScalef( 0.05f, 0.05f, 0.05f );
            
            LeapUtilGL::drawAxes();
        }
        
        {
            ScopedLock renderLock(m_renderMutex);
            
            // draw the text overlay
            renderOpenGL2D();
        }
    }
    
    virtual void onInit(const Leap::Controller&)
    {
    }
    
    virtual void onConnect(const Leap::Controller&)
    {
    }
    
    virtual void onDisconnect(const Leap::Controller&)
    {
    }
    
    virtual void onFocusGained(const Leap::Controller& controller)
    {
        m_lastFrame = controller.frame();
    }
    
    virtual void onFocusLost(const Leap::Controller&)
    {
    }
    
    virtual void onFrame(const Leap::Controller& controller)
    {
        Leap::Frame frame = controller.frame();
        
        update( frame );
        m_lastFrame = frame;
        m_openGLContext.triggerRepaint();
    }
    
    void resetScene()
    {
        m_mtxTotalMotionRotation  = Leap::Matrix::identity();
        m_vTotalMotionTranslation = Leap::Vector::zero();
        m_fTotalMotionScale       = 1.0f;
    }
    
    void resetCamera()
    {
        m_camera.SetVerticalFOVDegrees( 45.0f );
        m_camera.SetClipPlanes( 0.1f, 2000.0f );
        m_camera.SetOrbitTarget( Leap::Vector::zero() );
        m_camera.SetPOVLookAt( Leap::Vector( 0, 0, 120 ), m_camera.GetOrbitTarget() );
    }
    
private:
    OpenGLContext               m_openGLContext;
    LeapUtilGL::CameraGL        m_camera;
    Leap::Frame                 m_lastFrame;
    double                      m_fLastUpdateTimeSeconds;
    double                      m_fLastRenderTimeSeconds;
    
    /// accumulated rotation/translation and scale from Leap Motion API
    Leap::Matrix                m_mtxTotalMotionRotation;
    Leap::Vector                m_vTotalMotionTranslation;
    float                       m_fTotalMotionScale;
    float                       m_fLeftRightEyeShift;
    
    Font                        m_fixedFont;
    LeapUtil::RollingAverage<>  m_avgUpdateDeltaTime;
    LeapUtil::RollingAverage<>  m_avgRenderDeltaTime;
    String                      m_strUpdateFPS;
    String                      m_strRenderFPS;
    String                      m_strHelp;
    String                      m_aStrState[3];
    String                      m_strGroup;
    String                      m_strIndividual;
    String                      m_strPrompt;
    String                      m_strSave;
    String                      m_strFile;
    String                      m_strCompFile;
    uint32_t                    m_uiFlags;
    CriticalSection             m_renderMutex;
};

//==============================================================================
/**
 This is the top-level window that we'll pop up. Inside it, we'll create and
 show a component from the MainComponent.cpp file (you can open this file using
 the Jucer to edit it).
 */
class MotionVisualizerWindow : public DocumentWindow
{
public:
    //==============================================================================
    MotionVisualizerWindow()
    : DocumentWindow ("Leap Motion Visualizer",
                      Colours::lightgrey,
                      DocumentWindow::allButtons,
                      true)
    {
        setContentOwned (new OpenGLCanvas(), true);
        
        // Centre the window on the screen
        centreWithSize (getWidth(), getHeight());
        
        // And show it!
        setVisible (true);
        
        getChildComponent(0)->grabKeyboardFocus();
    }
    
    ~MotionVisualizerWindow()
    {
        // (the content component will be deleted automatically, so no need to do it here)
    }
    
    //==============================================================================
    void closeButtonPressed()
    {
        // When the user presses the close button, we'll tell the app to quit. This
        JUCEApplication::quit();
    }
};

void MotionVisualizerApplication::initialise (const String& commandLine)
{
    (void) commandLine;
    // Do your application's initialisation code here..
    currentFile = "";
    obj_rotx = new float[16];
    obj_rotx[0] = 1.0;	obj_rotx[1] = 0.0;	obj_rotx[2] = 0.0;	obj_rotx[3] = 0.0;
    obj_rotx[4] = 0.0;	obj_rotx[5] = 1.0;	obj_rotx[6] = 0.0;	obj_rotx[7] = 0.0;
    obj_rotx[8] = 0.0;	obj_rotx[9] = 0.0;	obj_rotx[10] = 1.0;	obj_rotx[11] = 0.0;
    obj_rotx[12] = 0.0;	obj_rotx[13] = 0.0;	obj_rotx[14] = 0.0;	obj_rotx[15] = 1.0;
    obj_roty = new float[16];
    obj_roty[0] = 1.0;	obj_roty[1] = 0.0;	obj_roty[2] = 0.0;	obj_roty[3] = 0.0;
    obj_roty[4] = 0.0;	obj_roty[5] = 1.0;	obj_roty[6] = 0.0;	obj_roty[7] = 0.0;
    obj_roty[8] = 0.0;	obj_roty[9] = 0.0;	obj_roty[10] = 1.0;	obj_roty[11] = 0.0;
    obj_roty[12] = 0.0;	obj_roty[13] = 0.0;	obj_roty[14] = 0.0;	obj_roty[15] = 1.0;
    keyFlag = 0;
    surfSets = GetAllFilesWithExtension(".SURFSET");
    for(int i =  0; i < surfSets.size(); i++){
        std::vector<std::string> surfaces;
        ifstream file;
        file.open(surfSets[i].c_str());
        std::string surfLoc;
        while (file.good())
        {
            getline (file, surfLoc, ',');
            surfLoc = std::string(surfLoc, 0, surfLoc.length());
            std::cout<<surfLoc<<std::endl;
            surfaces.push_back(surfLoc);
        }
        surfsInSet.push_back(surfaces);
    }
    m_pMainWindow = new MotionVisualizerWindow();
}

std::vector<std::string> GetAllFilesWithExtension(const std::string & ext)
{
    std::vector<std::string> surfSets2;
    DIR* dirp = opendir(".");
    dirent* dp;
    while ((dp = readdir(dirp)) != NULL){
        std::string filePathString = dp->d_name;
        if(filePathString.find(".SURFSET") != filePathString.npos){
            surfSets2.push_back(filePathString);
            //std::cout<<filePathString<<std::endl;
        }
    }
    (void)closedir(dirp);
    
    return surfSets2;
}

void setSurfaces(Boolean loadSurfaces){
    mutex.enter();
    SurfaceObject * surfTemp = NULL;
    SurfaceObject * surfTemp2 = NULL;
    
    std::cout<<surf<<" "<<surfCompared<<std::endl;
    
    if(surf != NULL){
        surfTemp = surf;
    }
    if(surfCompared != NULL){
        surfTemp2 = surfCompared;
    }
    
    std::cout<<surfTemp<<" "<<surfTemp2<<std::endl;
    
    if(surfIndex1 != -1 && surfSetIndex > 0){
        currentFile = surfsInSet[surfSetIndex-1][surfIndex1];
    }
    if(surfIndex2 != -1 && surfSetIndex > 0){
        comparedFile = surfsInSet[surfSetIndex-1][surfIndex2];
    }
    if(currentFile != ""){
        char *cstr = new char[currentFile.length() + 1];
        strcpy(cstr, currentFile.c_str());
        surf = parseGeometryFile(cstr);
        delete [] cstr;
    }
    if(comparedFile != ""){
        char *cstr = new char[comparedFile.length() + 1];
        strcpy(cstr, comparedFile.c_str());
        surfCompared = parseGeometryFile(cstr);
        delete [] cstr;
    }
    
    if(surfTemp != NULL){
        if(surf == surfTemp){
            surf = NULL;
        }
        std::cout<<surf<<" "<<surfTemp<<std::endl;
        surfTemp->dispose();
    }
    if(surfTemp2 != NULL){
        if(surfCompared == surfTemp2){
            surfCompared = NULL;
        }
        std::cout<<surfCompared<<" "<<surfTemp2<<std::endl;
        surfTemp2->dispose();
    }
    mutex.exit();
}

void groupPointerRight(){
    if(surfSetIndex == surfSets.size()){
        surfSetIndex = 0;
    }
    else{
        surfSetIndex++;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 1){
        surfIndex1 = 0;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 2){
        surfIndex2 = 1;
    }
    if(surfSetIndex == 0){
        currentFile = "";
        comparedFile = "";
        surfIndex1 = -1;
        surfIndex2 = -1;
    }
    setSurfaces(true);
}

void groupPointerLeft(){
    if(surfSetIndex == 0){
        surfSetIndex = surfSets.size();
    }
    else{
        surfSetIndex--;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 1){
        surfIndex1 = 0;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 2){
        surfIndex2 = 1;
    }
    if(surfSetIndex == 0){
        currentFile = "";
        comparedFile = "";
        surfIndex1 = -1;
        surfIndex2 = -1;
    }
    setSurfaces(true);
}

void surfacePointerRight(int surfFoc){
    if (surfFoc == 0){
        if(surfIndex2 != -1){
            if(surfIndex2 == surfsInSet[surfSetIndex-1].size()-1){
                surfIndex2 = 0;
            }
            else{
                surfIndex2++;
            }
        }
    }
    else{
        if(surfIndex1 != -1){
            if(surfIndex1 == surfsInSet[surfSetIndex-1].size()-1){
                surfIndex1 = 0;
            }
            else{
                surfIndex1++;
            }
        }
    }
    setSurfaces(true);
}

void surfacePointerLeft(int surfFoc){
    if (surfFoc == 0){
        if(surfIndex2 != -1){
            if(surfIndex2 == 0){
                surfIndex2 = surfsInSet[surfSetIndex-1].size()-1;
            }
            else{
                surfIndex2--;
            }
        }
    }
    else{
        if(surfIndex1 != -1){
            if(surfIndex1 == 0){
                surfIndex1 = surfsInSet[surfSetIndex-1].size()-1;
            }
            else{
                surfIndex1--;
            }
        }
    }
    setSurfaces(true);
}

void moveSurface(){
    if(surfIndex1 != -1 && surfSets.size() > 1){
        surfsInSet[surfSetIndex - 1].erase(surfsInSet[surfSetIndex - 1].begin() + surfIndex1);
        if(surfSetIndex == surfSets.size()){
            surfSetIndex = 1;
        }
        else{
            surfSetIndex++;
        }
        surfsInSet[surfSetIndex - 1].push_back(currentFile);
        surfIndex1 = surfsInSet[surfSetIndex - 1].size()-1;
        surfIndex2 = 0;
    }
    else if(surfSets.size() > 0 && currentFile != ""){
        surfsInSet[0].push_back(currentFile);
        surfSetIndex = 1;
        surfIndex1 = surfsInSet[0].size()-1;
        surfIndex2 = 0;
    }
    setSurfaces(true);
}

void saveSurfSets(){
    //std::vector<std::string> surfSets;
    //std::vector<std::vector<std::string>> surfsInSet;
    for(int i = 0; i < surfSets.size(); i++){
        std::string setBeingSaved = surfSets[i];
        std::string fileText = "";
        std::ofstream saveFile;
        //char *cstr = new char[setBeingSaved.length() + 1];
        //strcpy(cstr, setBeingSaved.c_str());
        //std::cout<<setBeingSaved<<std::endl;
        saveFile.open(setBeingSaved.c_str());
        //delete [] cstr;
        for(int j = 0; j < surfsInSet[i].size(); j++){
            fileText += surfsInSet[i][j];
            if (j != surfsInSet[i].size() - 1){
                fileText += ",";
            }
        }
        //std::cout<<fileText<<std::endl;
        saveFile << fileText;
        saveFile.close();
    }
}

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(MotionVisualizerApplication)
