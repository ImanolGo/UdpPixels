/*
 *  DressManager.cpp
 *  UDP Pixels
 *
 *  Created by Imanol Gomez on 15/02/17.
 *
 */



#include "ofMain.h"

#include "DressManager.h"
#include "AppManager.h"


DressManager::DressManager(): Manager(), m_isAltPressed(false), m_showChannels(false)
{
	//Intentionally left empty
}


DressManager::~DressManager()
{
    ofLogNotice() <<"DressManager::Destructor" ;
}


void DressManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupImages();
    this->setupScrollView();
    
    ofLogNotice() <<"DressManager::initialized" ;
    
}


void DressManager::setupImages()
{
    string resourceName = "DressLayout";
    ofPoint position;
    m_costumeImage =  ofPtr<ImageVisual> (new ImageVisual(position,resourceName));
    //m_costumeImage->setHeight(700,true);
    
}


void DressManager::setupScrollView()
{
    int margin = 40;
    ofRectangle contentRect;
    contentRect.width = m_costumeImage->getOriginalWidth();
    contentRect.height = m_costumeImage->getOriginalHeight();
    
    float ratio = m_costumeImage->getOriginalWidth()/ m_costumeImage->getOriginalHeight();
    
    ofRectangle windowRect;
    windowRect.width = ofGetWidth() - AppManager::getInstance().getGuiManager().getWidth() - 3*margin;
    windowRect.height =  windowRect.width / ratio;
    
    windowRect.x = margin;
    windowRect.y = ofGetHeight()*0.5 - windowRect.height*0.5;
    
    
    //----------------------------------------------------------
    m_scrollView.setWindowRect(windowRect); // window size and position of scroll view.
    m_scrollView.setContentRect(contentRect); // the pixel size of the content being displayed in scroll view.
    m_scrollView.fitContentToWindow(OF_ASPECT_RATIO_KEEP); // fits content into window, works with ofAspectRatioMode values.
    
    m_scrollView.setScrollEasing(0.3); // smoothness of scrolling, between 0 and 1.
    m_scrollView.setBounceBack(0.3); // the speed of bounce back, between 0 and 1.
    m_scrollView.setDragVelocityDecay(0.9); // the speed of decay of drag velocity after release, between 0 and 1.
    m_scrollView.setUserInteraction(true); // enable / disable mouse or touch interaction.
    m_scrollView.setPinchZoom(true);
    
    m_scrollView.setDoubleTapZoom(true); // enable double tap zoom.
    m_scrollView.setDoubleTapZoomIncrement(1.0); // the increment value of zoom on double tap, between 0 and 1.
    m_scrollView.setDoubleTapZoomIncrementTimeInSec(0.3); // the time amount of time for zoom increment.
    m_scrollView.setDoubleTapRegistrationTimeInSec(0.25); // the time threshold between taps for double tap event to register.
    m_scrollView.setDoubleTapRegistrationDistanceInPixels(20); // the distance threshold between taps for double tap event to register.
    
    m_scrollView.setup(); // setup must always be called at the end of scroll view config.
    
}

void DressManager::update()
{
    m_scrollView.update();
}


void DressManager::draw()
{
    ofEnableAlphaBlending();
    m_scrollView.begin();
    
        m_costumeImage->draw();
        this->drawCostumeLeds();
    
    m_scrollView.end();
    ofDisableAlphaBlending();
    
}

void DressManager::drawCostumeLeds()
{
    AppManager::getInstance().getLedsManager().draw(m_costumeImage->getOriginalWidth(), m_costumeImage->getOriginalHeight());
}


void DressManager::pressedMouse(ofMouseEventArgs &e)
{
    ofLogNotice() <<"DressManager::pressedMouse" ;
    
    ofPoint pos(e.x,e.y,0.0);
    AppManager::getInstance().getLedsManager().addLed(pos);
}


void DressManager::pressedBackSpace()
{
    if(m_isAltPressed){
        AppManager::getInstance().getLedsManager().deleteLastLed();
    }
}

void DressManager::toggleShowChannels()
{
    m_showChannels = !m_showChannels;
    
    AppManager::getInstance().getLedsManager().showChannels(m_showChannels);
    
}



