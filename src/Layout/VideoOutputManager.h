/*
 *  VideoOutputManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxBlur.h"

//========================== class VideoOutputManager ==============================
//============================================================================
/** \class VideoOutputManager VideoOutputManager.h
 *	\brief Class managing the preview of the application
 *	\details It reads the render visuals in the other windows and previews them in the main window
 */

class VideoOutputManager: public Manager
{
    static const int FBO_WIDTH = 600;
    static const int FBO_HEIGHT= 600;
    
public:

    //! Constructor
    VideoOutputManager();

    //! Destructor
    ~VideoOutputManager();

    //! Set-up the layout
    void setup();
    
    //! Draw Layer
    void draw();
    
    //! Draw a specific fbo
    void draw(int windowIndex);
    
    //! Begin fbo for a specific window
    void begin();
    
    //! End fbo for a specific window
    void end();
    
    const ofFbo& getVideoFbo() {return m_fboVideoOutput;}
    
    void onBlurScaleChange(float& value);
    
    void drawPreview();
    
    void drawContent();
    
   
    
private:

    //! Set-up the fbo
    void setupFbo();
    
    //! Set-up the blur filter
    void setupBlur();

private:
    
    ofFbo               m_fboVideoOutput;
    ofxBlur             m_blur;
    float               m_blurScale;
    
};

//==========================================================================


