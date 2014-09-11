#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Plane.h"

#define PLANE_NUM 6

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void initPlanes(Point center);
    
    void update(float dt);
    void trans(int dir);
    
    void initEvents();
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    void toggleView();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    int nums = PLANE_NUM;
    Plane* planes[PLANE_NUM];
    
    Point lastTouchP;
    
    float radio = 150.0;
};

#endif // __HELLOWORLD_SCENE_H__
