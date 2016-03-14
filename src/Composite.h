#include "ofMain.h"
#include "ofxXmlSettings.h"

template <class T>
class Composite {
public:
    string tag;
    vector<T > children;
    Composite(string _tag) : tag(_tag){
        
    }
    
    virtual void add(T e){
        children.push_back(e);
    }
    virtual void remove(int index){
        
    }
    
    //xml
    virtual int toVar(ofxXmlSettings &xml){
        int counter = 0;
        int r=0;
        string sameTagName = "";
        for(int i=0; i<children.size(); i++){
            string childTag = children[i]->tag;
            if(!xml.tagExists(childTag)) {
                xml.addTag(childTag);
            }
            if(childTag == sameTagName) {
                counter++;
                r = xml.pushTag(childTag,counter);
            }else{
                r = xml.pushTag(childTag,0);
                sameTagName = childTag;
            }
            children[i]->toVar(xml);
            xml.popTag();
        }
        return r;
    }
    virtual int toXml(ofxXmlSettings &xml){
        int index = xml.addTag(tag);
        xml.pushTag(tag,index);
        for(int i=0; i<children.size(); i++){
            children[i]->toXml(xml);
        }
        xml.popTag();
        return index;
    }
    
};
