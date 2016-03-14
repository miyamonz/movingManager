#include "SceneManager.h"
#include "scroll.h"
class SceneApp {
public:
    SceneManager* sm;
    ScrollManager* scm;
    
    SceneApp(){
        sm = new SceneManager();
        scm = new ScrollManager();
        
        ofAddListener(ofEvents().update,  this, &SceneApp::update);
        ofAddListener(ofEvents().draw,    this, &SceneApp::draw);
    }
    void setup(){
        sm->setup();
    };
    void update(ofEventArgs &e){
        scm->draw();
        scm->select(currentSceneNum);
    }
    void draw(ofEventArgs &e){
        scm->draw();
    }
    void load(){
        sm->load();
        scm->setButtons(getSceneNum());
        scm->load();

    };
    void save(){
        sm->save();
        scm->save();
    };
    
    
    //scene
    float currentSceneNum=0;
    void selectScene(int i){
        int sceneNum = sm->root->children.size();
        if(i <= 0)          i = 0;
        if(i >= sceneNum-1) i = sceneNum-1;
        currentSceneNum = i;
        sm->selectScene(i);
    }
    Scene* getCurrentScene(){
        return sm->root->children[currentSceneNum];
    }
    void nextScene(){
        selectScene(currentSceneNum+1);
    }
    void previusScene(){
        selectScene(currentSceneNum-1);
    }
    
    void insertScene(){
        sm->insertScene(currentSceneNum);
        scm->setButtons(getSceneNum());
    }
    
    int getSceneNum(){
        return sm->root->children.size();
    }
    
    vector<ofPoint> getCurrentPoints() {
        vector <ofPoint> points;
        for(int i=0; i<4; i++){
            ofPoint p = sm->root->children[currentSceneNum]->children[i]->draggable->getCurrentPoint();
            points.push_back(p);
        }
        return points;
    }
    
    //anim
    void resume(){
        Scene* currentScene = sm->root->children[currentSceneNum];
        currentScene->animInitAll();
        currentScene->animResumeAll();
    }
    
    //osc
    void resumeByText(string text){
        int index = scm->findText(text);
        if(index == -1) return;
        selectScene(index);
        resume();
        

    }
};
