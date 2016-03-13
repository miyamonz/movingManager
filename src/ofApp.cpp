#include "ofApp.h"
#define MOVING_NUM 4
//--------------------------------------------------------------
void ofApp::setup(){
    sa = new SceneApp();
    sa->setup();
    sa->load();
    sa->selectScene(0);
    //sa->sm->toVar();
    
    sender.setup("localhost", 3003);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0; i<MOVING_NUM; i++){
    ofxOscMessage m;
    m.setAddress("/movingManager/" + ofToString(i));
        ofPoint p = sa->getCurrentPoints()[i];
        m.addIntArg(p.x);
        m.addIntArg(p.y);
    sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    ofDrawRectangle(0,0,640,480);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's')
        sa->save();
    if(key == 'l')
        sa->load();

        
    if(key == 'i'){
        sa->insertScene();
//        sm->add(sm->getNewScene());
    }
    
    if(key == OF_KEY_UP)
        sa->previusScene();
    if(key == OF_KEY_DOWN)
        sa->nextScene();
    
    if(key == ' '){
        sa->resume();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
