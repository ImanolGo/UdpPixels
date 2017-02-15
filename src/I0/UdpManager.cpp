/*
 *  UdpManager.cpp
 *  Udp Pixels
 *
 *  Created by Imanol Gomez on 15/02/17.
 *
 */


#include "UdpManager.h"
#include "AppManager.h"


UdpManager::UdpManager(): Manager()
{
    //Intentionally left empty
}

UdpManager::~UdpManager()
{
   ofLogNotice() << "UdpManager::destructor";
}


//--------------------------------------------------------------

void UdpManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupUdp();
    
    ofLogNotice() <<"UdpManager::initialized" ;
}


void UdpManager::setupUdp()
{
    int port = AppManager::getInstance().getSettingsManager().getPort();
    string ip = AppManager::getInstance().getSettingsManager().getIpAddress();
    //create the socket and set to send to 127.0.0.1:11999
    m_udpConnection.Create();
    m_udpConnection.Connect("127.0.0.1",port);
    m_udpConnection.SetNonBlocking(true);
}

void UdpManager::update()
{
    ofPixels pixels;
    AppManager::getInstance().getVideoOutputManager().getVideoFbo().readToPixels(pixels);

}
