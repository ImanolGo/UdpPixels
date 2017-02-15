/*
 *  UdpManager.h
 *  Udp Pixels
 *
 *  Created by Imanol Gomez on 15/02/17.
 *
 */


#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "Manager.h"

//========================== class UdpManager =======================================
//==============================================================================
/** \class UdpManager UdpManager.h
 *	\brief class for managing the udp connection
 *	\details It writes and send udp data
 */


class UdpManager: public Manager
{

public:
    //! Constructor
    UdpManager();

    //! Destructor
    virtual ~UdpManager();

    //! setups the udp manager
    void setup();
    
    //! updates the udp manager
    void update();


private:
    
    void setupUdp();
    
private:
    
    ofxUDPManager m_udpConnection;
    
    
};

