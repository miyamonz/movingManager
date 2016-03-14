#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "TagClass.h"

class SceneManager {
public:
    Root* root = new Root("root");
    ofxXmlSettings xml;

    SceneManager(){};
    void setup(){
    }
    
    void selectScene(int i){
        for(auto scene : root->children) {
            scene->disable();
        }
        root->children[i]->enable();
    }
    void insertScene(int index){
        root->add(newScene());
    }
    void insertScene(){
        insertScene(0);
    }
    Scene* newScene(){
        Scene* scene = new Scene();
        
        vector<int> keys{'q','w','e','r'};
        vector<ofColor> colors{ofColor::red,ofColor::green,ofColor::blue,ofColor::gray};
        for(auto i : {0,1,2,3}){
            MovingLight* ml = new MovingLight("movingLight");
            scene->add(ml);
            ml->draggable->setKey(keys[i]);
            ml->draggable->setLineColor(colors[i]);
            
            PointDefault* startPoint     = new PointDefault("startPoint");
            PointDefault* endPoint       = new PointDefault("endPoint");
            PointDefault* controlPoint0  = new PointDefault("controlPoint0");
            PointDefault* controlPoint1  = new PointDefault("controlPoint1");
            for(auto point : {startPoint, endPoint, controlPoint0, controlPoint1})
                ml->add(point);
            FloatSettings* floatSettings      = new FloatSettings("settings");
            StringSettings* stringSettings    = new StringSettings("colors");
            ml->addFloatSettings(floatSettings);
            ml->addStringSettings(stringSettings);
            
            Leaf<float>* dimmer   = new Leaf<float>("dimmer",   0,255, 255);
            Leaf<float>* expand   = new Leaf<float>("expand",   0,20,  0);
            Leaf<float>* duration = new Leaf<float>("duration", 0,20,  0);
            Leaf<float>* strobe   = new Leaf<float>("strobe",   0,100, 100);
            Leaf<string>* color   = new Leaf<string>("color", "white");
            Leaf<string>* gobo    = new Leaf<string>("gobo", "open");
            for(auto i : {dimmer, expand, duration, strobe})
                floatSettings->add(i);
            for(auto i : {color, gobo})
                stringSettings->add(i);
         
            ml->setupGui();
        }
        scene->disable();
        return scene;
    }
    //xml
    void toVar(){
        xml.pushTag("root");
        root->toVar(xml);
        xml.popTag();
    }
    void toXml(){
        root->toXml(xml);
    }

    void load(){
        xml.clear();
        xml.loadFile("movingManager.xml");
        
        //scenenum of xml -> vector
        xml.pushTag("root");
        int sceneNum = xml.getNumTags("scene");
        xml.popTag();
        
        for(auto scene:root->children)
            scene->disable();
        
        root->children.resize(sceneNum);
        for(int i=0; i<sceneNum; i++){
            root->children[i] = newScene();
        }
        toVar();
    }
    void save(){
        xml.clear();
        toXml();
        xml.saveFile("movingManager.xml");
        ofLog() << "saved";
    }
};
