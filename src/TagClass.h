#pragma once
#include "ofMain.h"
#include "ofxDraggableBezier.h"
#include "ofxDatGui.h"
#include "ofxAnimatableFloat.h"
#include "innoPocket.h"
#include "Composite.h"
//setting
template <class T>
class Leaf {
public:
    string tag;
    T value;
    float min=0;
    float max=255;
    Leaf(string _tag, float _min, float _max) : Leaf(_tag){
        min = _min;
        max = _max;
    }
    Leaf(string _tag) : tag(_tag){};
    
    int toVar(ofxXmlSettings &xml){
        ofLog() << "toVar " << tag << " value " << value;
        T defaultValue;
        xml.popTag();
        value = xml.getValue(tag, defaultValue);
        xml.pushTag(tag);
    }
    int toXml(ofxXmlSettings &xml){
        ofLog() << tag << " " << value;
        xml.addValue(tag, value);
        return 1;
    }
};
class Settings : public Composite<Leaf<float>* >{
public:
    Settings(string _tag) : Composite<Leaf<float>* >(_tag) {};
};
class ColorSettings : public Composite<Leaf<string>* >{
public:
    ColorSettings(string _tag) : Composite<Leaf<string>* >(_tag) {};
};
//point
class PointDefault{
public:
    string tag;
    ofPoint p;
    PointDefault(string _tag) : tag(_tag){};
    
    int toVar(ofxXmlSettings &xml){
//        xml.pushTag(tag);
        p.x = xml.getValue("x", 0.);
        p.y = xml.getValue("y", 0.);
//        xml.popTag();
    }
    int toXml(ofxXmlSettings &xml){
        int index = xml.addTag(tag);
        xml.pushTag(tag,index);
        xml.addValue("x",p.x);
        xml.addValue("y",p.y);
        xml.popTag();
        return index;
    }
};

class MovingLight :public Composite<PointDefault* > {
public:
    //other child
    Settings* settings;
    ColorSettings* colorSetting;
    void addSettings(Settings* _settings){
        settings = _settings;
    }
    void addColorSettings(ColorSettings* _cSetting){
        colorSetting = _cSetting;
    }
    ofxDraggableBezier* draggable   = new ofxDraggableBezier();
    ofxDatGui*          gui         = new ofxDatGui();
    ofxAnimatableFloat* anim        = new ofxAnimatableFloat();
    string              colorString = "white";
    ofColor             color;
    MovingLight(string _tag) : Composite<PointDefault* >(_tag){};
    
    void setupGui(){
        gui->setWidth(160);
        gui->addDropdown("color", inno::getColorStrings());
        for(auto i:settings->children){
            gui->addSlider(i->tag,i->min,i->max)->bind(i->value);
        }
        gui->setVisible(false);
        
        gui->onDropdownEvent(this, &MovingLight::onDropdown);
        ofAddListener(ofEvents().update, this, &MovingLight::update);
    }
    void onDropdown(ofxDatGuiDropdownEvent e){
        //color dropdown
        colorSetting->children[0]->value = ofToLower(gui->getDropdown("color")->getSelected()->getLabel());
        color       = inno::stringToColor(colorSetting->children[0]->value);
        draggable->setInnerColor(color);  

    }
    void update(ofEventArgs &e){
        gui->setVisible(draggable->isPressed);
        ofPoint p = draggable->getBezierPoints()[2];
        gui->setPosition(p.x, p.y);
        
        //draggable->expand = getByTag("expand").getValue();
        draggable->expand = settings->children[1]->value;
        draggable->param  = anim->val();
        anim->update(1.0f/ofGetFrameRate());
        
    }
    virtual int toVar(ofxXmlSettings &xml){
        int index = Composite<PointDefault*>::toVar(xml);
        //settings
        xml.pushTag(settings->tag);
        settings->toVar(xml);
        xml.popTag();
        //color settings
        xml.pushTag(colorSetting->tag);
        colorSetting->toVar(xml);
        xml.popTag();
        
        color       = inno::stringToColor(colorSetting->children[0]->value);
        draggable->setInnerColor(color);
        
        //draggable <- points
        for(auto i:{0,1,2,3}){
            draggable->setBezierPoint(i, children[i]->p);
        }
    }
    virtual int toXml(ofxXmlSettings &xml){
        for(auto i:{0,1,2,3})
            children[i]->p = draggable->getBezierPoints()[i];

        int index = Composite<PointDefault*>::toXml(xml);
        xml.pushTag(tag,index);
        settings->toXml(xml);
        xml.popTag();
        
        xml.pushTag(tag,index);
        colorSetting->toXml(xml);
        xml.popTag();
        return index;
    }
    
    //anim
    void animInit(){
        anim->reset(0.0f);
        anim->setRepeatType(PLAY_ONCE);
        anim->setCurve(EASE_IN_EASE_OUT);
        //float duration = getByTag("duration")->getFloat();
        float duration = settings->children[2]->value;
        anim->setDuration(duration);
        anim->animateTo(1.0f);
        anim->pause();
    }
    void resume(){
        anim->resume();
    }
};

class Scene : public Composite<MovingLight* > {
public:
    Scene() : Scene("scene"){};
    Scene(string _tag) : Composite<MovingLight* >(_tag){};
    
    void enable(){
        for(auto moving : children){
            moving->draggable->enable();
            moving->draggable->ofxDraggable::show();
        }
    }
    void disable(){
        for(auto moving : children){
            moving->draggable->disable();
            moving->draggable->ofxDraggable::hide();
            moving->gui->setVisible(false);
        }
    }
    void animInitAll(){
        for(auto moving : children)
            moving->animInit();
    }
    void animResumeAll(){
        for(auto moving : children)
            moving->resume();
    }
};

class Root : public Composite<Scene* > {
public:
    Root(string _tag) : Composite<Scene* >(_tag){};

};