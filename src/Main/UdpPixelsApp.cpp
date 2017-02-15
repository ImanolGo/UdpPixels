/*
 *  UdpPixelsApp.cpp
 *  UDP Pixels App
 *
 *  Created by Imanol Gomez on 14/02/17.
 *
 */

#include "AppManager.h"

#include "UdpPixelsApp.h"

//--------------------------------------------------------------
void UdpPixelsApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void UdpPixelsApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void UdpPixelsApp::draw(){
    AppManager::getInstance().draw();
}

void UdpPixelsApp::exit()
{
    ofLogNotice() <<"UdpPixelsApp::exit";

}

//--------------------------------------------------------------
void UdpPixelsApp::keyPressed(int key){

}

//--------------------------------------------------------------
void UdpPixelsApp::keyReleased(int key){

}

//--------------------------------------------------------------
void UdpPixelsApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void UdpPixelsApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void UdpPixelsApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void UdpPixelsApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void UdpPixelsApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void UdpPixelsApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void UdpPixelsApp::dragEvent(ofDragInfo dragInfo){

}
