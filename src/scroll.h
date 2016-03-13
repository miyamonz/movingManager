#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"

class ScrollManager {
public:
    ofxDatGuiScrollView* scroll;
    vector<ofxDatGuiButton* > buttons;
    int pressedIndex;
    
    ScrollManager(){
        scroll = new ofxDatGuiScrollView("scenes", 18);
        scroll->setWidth(70);
        scroll->setPosition(640, 0);
        setButtons(1);
    };
    
    void update(){
        scroll->update();
    }
    void draw(){
        scroll->draw();
    }
    void setButtons(int buttonNum){
        scroll->clear();
        buttons.clear();
        for(int i=0; i<buttonNum; i++){
            scroll->add(ofToString(i));
            ofxDatGuiButton* b = scroll->get(i);
            buttons.push_back(b);
        }
        for(auto button : buttons){
            button->onButtonEvent(this, &ScrollManager::buttonEvent);
        }
        
    }
    
    void select(int index){
        if(index >= buttons.size()) index = buttons.size()-1;
        for(auto button : buttons)
            button->setTheme(new ofxDatGuiThemeWireframe);
        buttons[index]->setTheme(new ofxDatGuiThemeCandy);
    }
    void buttonEvent(ofxDatGuiButtonEvent e){
        ofLog() << "button "<<e.target->getLabel();
        int index;
        for(int i=0; i<buttons.size(); i++){
            if(e.target->getLabel() == ofToString(i))
                index = i;
        }
        pressedIndex = index;
    }
};
