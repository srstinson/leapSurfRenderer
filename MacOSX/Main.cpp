/******************************************************************************\
 * Copyright (C) Leap Motion, Inc. 2011-2013.                                   *
 * Leap Motion proprietary and  confidential.  Not for distribution.            *
 * Use subject to the terms of the Leap Motion SDK Agreement available at       *
 * https://developer.leapmotion.com/sdk_agreement, or another agreement between *
 * Leap Motion and you, your company or other organization.                     *
 \******************************************************************************/
#include "Main.h"

class MotionVisualizerWindow;
class OpenGLCanvas;

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
        return "LeapRenderer";
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
        
        m_fTotalMotionScale = 1.0f;
        
        m_fLeftRightEyeShift = 2.0f;
        
        m_strSave = "Up to Date";
        
        m_strFile = "[F]ile: ";
        
        m_strSet = "Set: ";
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
                surfaces.groupPointerRight();
                return true;
            }
            
            if ( iKeyCode == KeyPress::leftKey )
            {
                surfaces.groupPointerLeft();
                return true;
            }
            
            if ( iKeyCode == KeyPress::upKey )
            {
                surfaces.surfacePointerRight(0);
                return true;
            }
            
            if ( iKeyCode == KeyPress::downKey )
            {
                surfaces.surfacePointerLeft(0);
                return true;
            }
            
            if ( iKeyCode == '.' )
            {
                surfaces.surfacePointerRight(1);
                return true;
            }
            
            if ( iKeyCode == ',' )
            {
                surfaces.surfacePointerLeft(1);
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
                                        
                case 'M':
                    if (mode == 0){
                        mode = 1;
                        m_uiFlags ^= kFlag_Rotate;
                    }
                    else if (mode == 1){
                        m_uiFlags ^= kFlag_Rotate;
                        m_uiFlags ^= kFlag_Scale;
                        mode = 2;
                    }
                    else if (mode == 2){
                        m_uiFlags ^= kFlag_Scale;
                        mode = 0;
                    }
                    break;
                    
                case 'N':
                    if(surfaces.getSurfSetIndex() == 0 && (surfaces.getCurrentFileName() != "" || surfaces.getComparedFileName() != "")){
                        surfaces.newSet();
                        m_strSave = "Not [S]aved";
                        keyFlag = 3;
                    }
                    break;
                case 'S':
                    surfaces.saveSurfSets();
                    m_strSave = "Up to Date";
                    break;
                    
                case 'T':
                    m_uiFlags ^= kFlag_Transparent;
                    break;
                    
                case 'F':
                    surfaces.setCurrentFileName("");
                    surfaces.setSurfIndex(1,-1);
                    surfaces.setSurfIndex(2,-2);
                    surfaces.setSurfSetIndex(0);
                    keyFlag = 1;
                    break;
                    
                case 'C':
                    surfaces.setComparedFileName("");
                    surfaces.setSurfIndex(1,-1);
                    surfaces.setSurfIndex(2,-2);
                    surfaces.setSurfSetIndex(0);
                    keyFlag = 2;
                    break;
                    
                case 'P':
                    //moveSurface();
                    m_strSave = "Not [S]aved";
                    break;
                    
                case 'V':
                    if(fingerFlag){
                        fingerFlag = false;
                    }
                    else{
                        fingerFlag = true;
                    }
                    break;
                    
                default:
                    return false;
            }
            
            updateStateStr();
        }
        else if(keyFlag == 1){
            int iKeyCode = keyPress.getKeyCode();
            if(iKeyCode == KeyPress::returnKey){
                surfaces.setSurfaces(false);
                keyFlag = 0;
            }
            else if(iKeyCode == KeyPress::backspaceKey){
                string currentFile = surfaces.getCurrentFileName();
                if (currentFile.size() > 0){
                    currentFile.resize(currentFile.size () - 1);
                    surfaces.setCurrentFileName(currentFile);
                }
            }
            else{
                char cKeyCode = keyPress.getTextCharacter();
                string currentFile = surfaces.getCurrentFileName();
                currentFile += cKeyCode;
                surfaces.setCurrentFileName(currentFile);
            }
        }
        else if(keyFlag == 2){
            int iKeyCode = keyPress.getKeyCode();
            if(iKeyCode == KeyPress::returnKey){
                surfaces.setSurfaces(false);
                keyFlag = 0;
            }
            else if(iKeyCode == KeyPress::backspaceKey){
                string comparedFile = surfaces.getComparedFileName();
                if (comparedFile.size() > 0){
                    comparedFile.resize(comparedFile.size () - 1);
                    surfaces.setComparedFileName(comparedFile);
                }
            }
            else{
                string comparedFile = surfaces.getComparedFileName();
                char cKeyCode = keyPress.getTextCharacter();
                comparedFile += cKeyCode;
                surfaces.setComparedFileName(comparedFile);
            }
        }
        else if(keyFlag == 3){
            int iKeyCode = keyPress.getKeyCode();
            if(iKeyCode == KeyPress::returnKey){
                surfaces.newSet();
                keyFlag = 0;
            }
            else if(iKeyCode == KeyPress::backspaceKey){
                string setName = surfaces.getSetFileName();
                if (setName.size() > 0){
                    setName.resize(setName.size () - 1);
                    surfaces.setSetFileName(setName);
                }
            }
            else if(keyPress.isValid()){
                string setName = surfaces.getSetFileName();
                char cKeyCode = keyPress.getTextCharacter();
                setName += cKeyCode;
                surfaces.setSetFileName(setName);
            }
        }
        return true;
    }
    
    void updateStateStr()
    {
        m_aStrState[0] = String::empty;
        m_aStrState[1] = String::empty;
        
        m_aStrState[0]  << "[T]ransparency: " << LeapUtil::BoolToStr( m_uiFlags & kFlag_Transparent );
        m_aStrState[1]  << "Next [M]ode: "    << mode;//LeapUtil::BoolToStr( m_uiFlags & kFlag_Rotate );
        
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
                glm::vec3 eulerAngles(0, 0.05, 0);
                myQuaternion = glm::quat(eulerAngles) * myQuaternion;
            }
            else{
                glm::vec3 eulerAngles(0, -0.05, 0);
                myQuaternion = glm::quat(eulerAngles) * myQuaternion;
            }
        }
        else if (direction == 2){
            if(angleDirectionY > 0){
                glm::vec3 eulerAngles(0.05, 0, 0);
                myQuaternion = glm::quat(eulerAngles) * myQuaternion;
            }
            else{
                glm::vec3 eulerAngles(-0.05, 0, 0);
                myQuaternion = glm::quat(eulerAngles) * myQuaternion;
            }
        }
    }
    
    void mouseWheelMove ( const MouseEvent& e,
                         const MouseWheelDetails& wheel )
    {
        (void)e;
        (void)wheel;
        static const float kfMinScale = 0.1f;
        static const float kfMaxScale = 3.0f;
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
        m_strFile += surfaces.getCurrentFileName().c_str();
        m_strCompFile += surfaces.getComparedFileName().c_str();
        int surfSetIndex = surfaces.getSurfSetIndex();
        if(surfSetIndex != 0){
            vector<string> surfSets = surfaces.getSurfSets();
            m_strSet += surfSets[surfSetIndex-1].c_str();
        }
        else if(keyFlag == 3){
            m_strSet += surfaces.getSetFileName().c_str();
        }
        g.drawSingleLineText( m_strSave, iMargin, iBaseLine);
        g.drawSingleLineText( m_strFile, iMargin, iBaseLine + iLineStep );
        g.drawSingleLineText( m_strCompFile, iMargin, iBaseLine + 2*iLineStep );
        g.drawSingleLineText( m_strSet, iMargin, iBaseLine + 3*iLineStep );
        m_strFile = "[F]ile: ";
        m_strCompFile = "[C]ompare File: ";
        m_strSet = "Set: ";
        
        if ( m_uiFlags & kFlag_FPS )
        {
            g.setColour( Colours::seagreen );
            g.drawSingleLineText( m_strUpdateFPS, iMargin, iBaseLine + iLineStep );
            g.drawSingleLineText( m_strRenderFPS, iMargin, iBaseLine + iLineStep*2 );
        }
        
        g.setFont( origFont );
        g.setFont( static_cast<float>(iFontSize) );
        
        g.setColour( Colours::orange );
        
        for ( int i = 1, uiTotalWidth = 0; i >= 0; i-- )
        {
            if ( !m_aStrState[i].isEmpty() )
            {
                const uint32_t uiStrWidth = g.getCurrentFont().getStringWidth( m_aStrState[i] );
                
                if ( (i < 2) && (m_uiFlags & kFlag_Automatic) )
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
        vector<string> surfSets = surfaces.getSurfSets();
        for(int i = 0; i < surfSets.size() + 1; i++){
            if(i == surfSetIndex){
                m_strGroup += "[";
            }
            m_strGroup += i;
            if(i ==surfSetIndex){
                m_strGroup += "]";
            }
            m_strGroup += " ";
        }
        g.setColour( Colours::orange );
        g.drawSingleLineText( m_strGroup,
                             rectBounds.getCentreX(),
                             rectBounds.getBottom() - 2*(iFontSize*2),
                             Justification::horizontallyCentred );
        m_strIndividual = "Surfs: ";

        if(surfSetIndex >= 1){
            vector<vector<string>> surfsInSet = surfaces.getSurfsInSet();
            int surfIndex1 = surfaces.getSurfIndex(1);
            int surfIndex2 = surfaces.getSurfIndex(2);
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
        
        static const float kfMaxScale = 3.0f;
        
        //If automatic motion type detection is enabled, check if motion probabilities are above threshold amounts
        bool bShouldTranslate = true;
        bool bShouldRotate    = true;
        bool bShouldScale     = true;
        
        //recognitionEngine current coord to the Gesture Recognition Engine
        
        
        
        if(frameCount < 3){
            frameCount++;
        }
        else{
            frameCount = 0;
        }
        
        bool gestureFlag = false;
        
        if(frameCount == 0){
            if (frame.fingers().count() == 1){
                float x,y;
                
                Leap::FingerList fingers = frame.fingers();
                
                x = fingers[0].tipPosition().x;
                y = -fingers[0].tipPosition().y;
                
                float distance = pow((previousX - x),2) + pow((previousY - y),2);
                                
                if(distance > 5){
                    recognitionEngine->updateCoord(frame);
                }
                else{
                    pauseCounter++;
                    if (pauseCounter == 3){
                        gestureFlag = true;
                        pauseCounter = 0;
                    }
                }
                previousX = x;
                previousY = y;
            }
            if(frame.fingers().count() == 0 || gestureFlag){
                string dollarGestureName = recognitionEngine->recognize().name;
                double dollarGestureScore = recognitionEngine->recognize().score;
                if(dollarGestureName != "Unknown"){
                    std::cout<<dollarGestureName<<" "<<dollarGestureScore<<std::endl;
                }
                if(dollarGestureName == "Arrow"){
                    if (mode == 0){
                        mode = 1;
                        m_uiFlags ^= kFlag_Rotate;
                    }
                    else if (mode == 1){
                        m_uiFlags ^= kFlag_Rotate;
                        m_uiFlags ^= kFlag_Scale;
                        mode = 2;
                    }
                    else if (mode == 2){
                        m_uiFlags ^= kFlag_Scale;
                        mode = 0;
                    }
                    updateStateStr();
                }
                else if(dollarGestureName == "Pigtail" && mode == 0){
                    surfaces.moveSurface();
                    m_strSave = "Not [S]aved";
                }
                else if(dollarGestureName == "CheckMark" && mode == 0){
                    surfaces.saveSurfSets();
                    m_strSave = "Up to Date";
                }
                else if(dollarGestureName == "Rectangle"){
                    m_uiFlags ^= kFlag_Transparent;
                    updateStateStr();
                }
                else if(dollarGestureName == "Caret"){
                    string currentFile = surfaces.getCurrentFileName();
                    string comparedFile = surfaces.getComparedFileName();
                    int surfSetIndex = surfaces.getSurfSetIndex();
                    if(surfSetIndex == 0 && (currentFile != "" || comparedFile != "")){
                        m_strSave = "Not [S]aved";
                        keyFlag = 3;
                        keyPressed( KeyPress() );
                    }
                }
                recognitionEngine->clear();
            }
        }
        
        const Leap::GestureList gestures = frame.gestures();
        if(gestures.count() > 0) {
            Leap::Gesture gesture = gestures[0];
            time_t timerEnd = time(NULL);
            switch (gesture.type()) {
                case Leap::Gesture::TYPE_CIRCLE:
                {
                    if (mode == 0){
                        Leap::CircleGesture circle = gesture;
                        std::string clockwiseness;
                        if (gesture.id() != lastCircle){
                            lastCircle = gesture.id();
                            if (frame.fingers().count() == 2){
                                if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
                                    surfaces.surfacePointerRight(0);
                                    clockwiseness = "clockwise";
                                } else {
                                    surfaces.surfacePointerLeft(0);
                                    clockwiseness = "counterclockwise";
                                }
                            }
                            else if(frame.fingers().count() == 3){
                                if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
                                    surfaces.surfacePointerRight(1);
                                    clockwiseness = "clockwise";
                                } else {
                                    surfaces.surfacePointerLeft(1);
                                    clockwiseness = "counterclockwise";
                                }
                            }
                        }
                    }
                    break;
                }
                case Leap::Gesture::TYPE_SWIPE:
                {
                    if (mode == 0  && frame.fingers().count() >= 5){
                        Leap::SwipeGesture swipe = gesture;
                        if (gesture.id() != lastSwipe && difftime(timerEnd,timerStart) >= 2 && !frame.fingers().isEmpty()){
                            lastSwipe = gesture.id();
                            if (swipe.direction().x > 0){
                                surfaces.groupPointerRight();
                            }
                            else{
                                surfaces.groupPointerLeft();
                            }
                            timerStart = time(NULL);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        
        
        m_uiFlags &= ~(kFlags_AutoDetectedTransforms);
        
        if ( m_uiFlags & kFlag_Automatic )
        {
            bShouldTranslate = false;
            bShouldRotate    = frame.translationProbability(m_lastFrame)    > 0.60;
            bShouldScale     = frame.translationProbability(m_lastFrame)    > 0.80;
            
            m_uiFlags |= bShouldTranslate ? kFlag_AutoDetectedTranslate : 0;
            m_uiFlags |= bShouldRotate ? kFlag_AutoDetectedRotate : 0;
            m_uiFlags |= bShouldScale ? kFlag_AutoDetectedScale : 0;
        }
        
        //Update the rotation
        if (( m_uiFlags & kFlag_Rotate ) && bShouldRotate && frame.fingers().count() >= 5)
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
                    glm::vec3 eulerAngles(0, 0.05, 0);
                    myQuaternion = glm::quat(eulerAngles) * myQuaternion;
                }
                else{
                    glm::vec3 eulerAngles(0, -0.05, 0);
                    myQuaternion = glm::quat(eulerAngles) * myQuaternion;
                }
            }
            else if (direction == 2){
                if(angleDirectionY > 0){
                    glm::vec3 eulerAngles(0.05, 0, 0);
                    myQuaternion = glm::quat(eulerAngles) * myQuaternion;
                }
                else{
                    glm::vec3 eulerAngles(-0.05, 0, 0);
                    myQuaternion = glm::quat(eulerAngles) * myQuaternion;
                }
            }
            
        }
        
        //Update the scale
        if (( m_uiFlags & kFlag_Scale ) && bShouldScale && frame.fingers().count() >= 5)
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
        
        glScalef(m_fTotalMotionScale, m_fTotalMotionScale, m_fTotalMotionScale);
        
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
        
        
        surfaces.draw(myQuaternion,keyFlag,(m_uiFlags & kFlag_Transparent));
    }
    
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
        
        if(fingerFlag){
            drawPointables(frame);
        }
        
        {
            ScopedLock renderLock(m_renderMutex);
            
            // draw the text overlay
            renderOpenGL2D();
        }
    }
    
    void drawPointables(Leap::Frame frame){
        
        const Leap::FingerList& pointables = frame.fingers();
        
        
        for ( size_t i = 0, e = pointables.count(); i < e; i++ ){
            
            const Leap::Finger&  pointable   = pointables[i];

            Leap::Vector stabilizedPosition = pointable.stabilizedTipPosition();
            
            Leap::InteractionBox iBox = frame.interactionBox();
            Leap::Vector normalizedPosition = iBox.normalizePoint(stabilizedPosition);
            float x0 = normalizedPosition.x * 20;
            float y0 = normalizedPosition.y * 15;
            
            glBegin(GL_TRIANGLE_FAN);
            
            glVertex2f(x0, y0);
            
            for( int angle = 0; angle <= 360; angle += 5){
                glVertex2f(x0 + sin(angle * PI/180) * 0.25, y0 + cos(angle* PI/180) * 0.25);
            }
            
            glEnd();
        
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
    String                      m_aStrState[2];
    String                      m_strGroup;
    String                      m_strIndividual;
    String                      m_strSave;
    String                      m_strFile;
    String                      m_strCompFile;
    String                      m_strSet;
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
    : DocumentWindow ("LeapRenderer",
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
    keyFlag = 0;
    getController().enableGesture(Leap::Gesture::TYPE_CIRCLE);
    getController().enableGesture(Leap::Gesture::TYPE_SWIPE);
    glm::vec3 eulerAngles(0, 0, 0);
    myQuaternion = glm::quat(eulerAngles);
    timerStart = time(NULL);
    recognitionEngine->Instance();
    m_pMainWindow = new MotionVisualizerWindow();
}

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(MotionVisualizerApplication)
