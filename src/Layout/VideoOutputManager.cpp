/*
 *  VideoOutputManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "VideoOutputManager.h"

const int FBO_WIDTH = 600;
const int FBO_HEIGHT= 600;

VideoOutputManager::VideoOutputManager(): Manager(), m_blurScale(0.0)
{
	//Intentionally left empty
}


VideoOutputManager::~VideoOutputManager()
{
    ofLogNotice() <<"VideoOutputManager::Destructor";
}


void VideoOutputManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();
    
    this->setupFbo();
    this->setupBlur();
    
    ofLogNotice() <<"VideoOutputManager::initialized";

}

void VideoOutputManager::setupFbo()
{
    
    float width =  FBO_WIDTH;
    float height = FBO_HEIGHT;
    
    m_fboVideoOutput.allocate(width, height);
    m_fboVideoOutput.begin(); ofClear(0); m_fboVideoOutput.end();
}


void VideoOutputManager::setupBlur()
{
    float radius = 10; float shape = .2; float passes = 1;
    m_blur.setup(m_fboVideoOutput.getWidth(), m_fboVideoOutput.getHeight(), radius, shape, passes);
    m_blur.setScale(m_blurScale);
}

void VideoOutputManager::draw()
{
    this->drawPreview();
    //this->drawContent();
}

void VideoOutputManager::drawPreview()
{
    auto pos = AppManager::getInstance().getGuiManager().getPosition();
    pos.y += AppManager::getInstance().getGuiManager().getHeight() + 20;
    int w = AppManager::getInstance().getGuiManager().getWidth();
    int h = 9*w/16;
    
    m_fboVideoOutput.draw(pos.x, pos.y, w, h);
}

void VideoOutputManager::drawContent()
{
    int x = AppManager::getInstance().getGuiManager().getWidth() + 40;
    int y = 0;
    int w = ofGetWidth() - x;
    int h = ofGetHeight();
    
    ofPushStyle();
        ofSetColor(100);
        m_fboVideoOutput.draw(x, y, w, h);
    ofPopStyle();
}



void VideoOutputManager::begin()
{
    int brightness = 255*AppManager::getInstance().getAudioManager().getAudioMax();
    
    //ofLogNotice() <<"VideoOutputManager::setupSyphon << brightness: " << brightness;

    
    ofPushStyle();
    m_fboVideoOutput.begin();
    m_blur.begin();
    ofClear(0);
    ofSetColor(brightness);
}

void VideoOutputManager::end()
{
     m_blur.end();
     m_blur.draw();
     m_fboVideoOutput.end();
     ofPopStyle();
    
}

void VideoOutputManager::onBlurScaleChange(float& value)
{
    m_blurScale = value;
    m_blur.setScale(m_blurScale);
}





