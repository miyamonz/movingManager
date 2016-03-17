#include "ofApp.h"
#define MOVING_NUM 4
//--------------------------------------------------------------
void ofApp::setup(){
    sa = new SceneApp();
    sa->setup();
    sa->load();
    sa->selectScene(0);
    //sa->sm->toVar();
    
    receiver.setup(3211);
    sender.setup("localhost", 3210);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0; i<MOVING_NUM; i++){
        //position
        ofxOscMessage m;
        m.setAddress("/toMapper/" + ofToString(1) + "/" + ofToString(i) + "/point");
        ofPoint p = sa->getCurrentPoints()[i];
        m.addFloatArg(p.x);
        m.addFloatArg(p.y);
        sender.sendMessage(m);
        
        //color
        m.clear();
        m.setAddress("/toMapper/" + ofToString(1) + "/"  + ofToString(i) + "/color");
        m.addStringArg(sa->getCurrentScene()->children[i]->colorString);
        sender.sendMessage(m);
        
        //gobo
        m.clear();
        m.setAddress("/toMapper/" + ofToString(1) + "/"  + ofToString(i) + "/gobo");
        m.addStringArg(sa->getCurrentScene()->children[i]->goboString);
        sender.sendMessage(m);

        //strobe
        m.clear();
        m.setAddress("/toMapper/" + ofToString(1) + "/"  + ofToString(i) + "/strobe");
        m.addFloatArg(sa->getCurrentScene()->children[i]->floatSettings->children[3]->value);
        sender.sendMessage(m);

        //dimmer
        m.clear();
        m.setAddress("/toMapper/" + ofToString(0) + "/"  + ofToString(i) + "/dimmer");
        m.addFloatArg(sa->getCurrentScene()->children[i]->floatSettings->children[0]->value);
        sender.sendMessage(m);

        
    }
    
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(m);
        ofLog() << "in";
		if(m.getAddress() == "/sendMovingManager"){
            string receiveText = m.getArgAsString(0);
            ofLog() << receiveText;
            sa->resumeByText(receiveText);
        }
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
