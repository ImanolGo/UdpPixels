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
    
    this->setupHeader();
    this->setupUdp();
    
    ofLogNotice() <<"UdpManager::initialized" ;
}


void UdpManager::setupHeader()
{
    m_header.f1 = 0x10;
    m_header.f2 = 0x41;
    m_header.f3 = 0x37;
    m_header.size = 0;
    m_header.channel = 0;
}
    
void UdpManager::setupUdp()
{
    int port = AppManager::getInstance().getSettingsManager().getPort();
    string ip = AppManager::getInstance().getSettingsManager().getIpAddress();
    //create the socket and set to send to 127.0.0.1:11999
    m_udpConnection.Create();
    m_udpConnection.Connect(ip.c_str(),port);
    m_udpConnection.SetNonBlocking(true);
    
    ofLogNotice() <<"UdpManager::setupUdp << Connecting to ip address: " << ip << ", port " << port;

}

void UdpManager::update()
{
    const auto & leds = AppManager::getInstance().getLedsManager().getLeds();
//    const int length = leds.size()*3;
//    const char* pixels[length];
    
    string message="";
    message+= m_header.f1; message+= m_header.f2; message+= m_header.f3;
    m_header.size = 3*leds.size();
    unsigned char * s = (unsigned char*)& m_header.size;
    message+= s[1] ;  message+=  s[0];
    message+=m_header.channel;
    
    for(int i = 0; i< leds.size(); i++)
    {
//        pixels[i*3] = (const char *)leds[i]->getColor().r;
//        pixels[i*3 + 1] = (const char *) leds[i]->getColor().g;
//        pixels[i*3 + 2] = (const char *)leds[i]->getColor().b;
        
        message+=leds[i]->getColor().r;
        message+=leds[i]->getColor().g;
        message+=leds[i]->getColor().b;

    }
    
    
   // const char* pixelsChar = (const char*)pixels;
    m_udpConnection.Send(message.c_str(),message.length());

}
