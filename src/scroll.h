#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxXmlSettings.h"

class ScrollManager {
public:
    ofxDatGuiScrollView* scroll;
    ofxDatGui* gui;
    vector<ofxDatGuiButton* > buttons;
    int pressedIndex;
    
    ScrollManager(){
        scroll = new ofxDatGuiScrollView("scenes", 18);
        scroll->setWidth(100);
        scroll->setPosition(640, 0);
        setButtons(1);
        
        gui = new ofxDatGui();
        gui->addTextInput("scene-text");
        
//        gui->setPosition(scroll->getX() + scroll->getWidth(), scroll->getY());
        gui->setPosition(0, 480);
        gui->onTextInputEvent(this, &ScrollManager::onTextInput);
    };
    void onTextInput(ofxDatGuiTextInputEvent e){
        ofLog() << "aboabo " << e.text;
        buttons[selected]->setLabel(e.text);
        
    }
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
    int selected;
    void select(int index){
        if(index >= buttons.size()) index = buttons.size()-1;
        selected = index;
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
    
    ofxXmlSettings xml;
    string tag = "sceneText";
    void save(){
        xml.clear();

        for(auto b : buttons){
            string label = b->getLabel();
            ofLog() << label;
            //int index = xml.addTag(tag);
            xml.addValue(tag, label);
        }
        xml.saveFile("sceneText.xml");
    }
    void load(){
        xml.clear();
        xml.loadFile("sceneText.xml");
        int tagNum = xml.getNumTags(tag);
        
        setButtons(tagNum);
        for(int i=0; i<tagNum; i++){
            string label = xml.getValue(tag, ofToString(i), i);
            ofLog() << label;
            buttons[i]->setLabel(label);
        }
        
    }
    int findText(string text){
        int index = 0;
        for(auto b:buttons){
            string label = b->getLabel();
            if(text == label) return index;
            index++;
        }
        
        return -1;
    }
};
