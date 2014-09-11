#include "HelloWorldScene.h"

USING_NS_CC;

float pMMM = 0.0f;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    sprite->setScale(5.0);
    this->addChild(sprite, 0);
    
    
    // 初始化开始
    initPlanes(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
//    this->setPosition3D(cocos2d::Vertex3F(0, 0, 200));
//    this->setRotation3D(cocos2d::Vertex3F(-35, 0, 0));
    
    initEvents();
    
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::initPlanes(Point center){
    for (int i=0; i < nums; i++) {
        auto* plane = Plane::create();
        float angle = 360.0/nums*i - pMMM;
        float rad = angle * 3.14/180;
        plane->setPosition3D(cocos2d::Vertex3F(center.x + radio*cos(rad), center.y + 50*sin((-angle)* 3.14/180), 150.0 + radio*sin(rad)));
//        plane->setRotation3D(cocos2d::Vertex3F(90, 90-angle, 0));
        plane->setScale(1+ sin((180-angle)* 3.14/180)/2);
        planes[i] = plane;
        this->addChild(plane);
    }
}

void HelloWorld::update(float dt){
//    // 自转
//    pMMM += 0.5;
//    for (int i=0; i < nums; i++) {
//        auto plane = planes[i];
//        float angle = 360.0/nums*i - pMMM;
//        float ratio = angle * 3.14/180;
//        plane->setPosition3D(cocos2d::Vertex3F(450.0 + 100*cos(ratio), 250 + 50*sin((180-angle)* 3.14/180), 150.0 + 100*sin(ratio)));
////        plane->setRotation3D(cocos2d::Vertex3F(90, 90-angle, 0));
//        plane->setScale(.6+ sin((-angle)* 3.14/180)/2);
//    }
//    log("==========================");
    for (int i=0; i < nums; i++) {
        auto plane = planes[i];
        plane->update(dt);
        // reset order
//        int zz = plane->getPositionZ();
//        log("%d,", zz);
//        this->reorderChild(plane, zz);
    }
    
//    log("==========================");
}


void HelloWorld::initEvents(){
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}


bool HelloWorld::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    lastTouchP = pTouch->getLocation();
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
}

void HelloWorld::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    Point pt = pTouch->getLocation();
    int endX = lastTouchP.x - pt.x;
    if(endX > 20){
        trans(1);
    }
    else if(endX < -20){
        trans(-1);
    }
}

void HelloWorld::trans(int dir){
    if (dir > 0) {
        Vertex3F p0 = planes[0]->getTargetPos();
        Vertex3F r0 = planes[0]->getTargetRot();
        float f0 = planes[0]->getTargetScal();
        for (int i=0; i<nums; i++) {
            auto plane = planes[i];
            if (i < nums-1) {
                auto pnext = planes[i+1];
                Vertex3F p = pnext->getTargetPos();
                Vertex3F r = pnext->getTargetRot();
                float f = pnext->getTargetScal();
                plane->setTarget(p, f, r);
            }else{
                plane->setTarget(p0, f0, r0);
            }
        }
    }
    else {
        Vertex3F p0 = planes[nums-1]->getTargetPos();
        Vertex3F r0 = planes[nums-1]->getTargetRot();
        float f0 = planes[nums-1]->getTargetScal();
        for (int i=nums-1; i >= 0; i--) {
            auto plane = planes[i];
            if (i > 0) {
                auto pnext = planes[i-1];
                Vertex3F p = pnext->getTargetPos();
                Vertex3F r = pnext->getTargetRot();
                float f = pnext->getTargetScal();
                plane->setTarget(p, f, r);
            }else{
                plane->setTarget(p0, f0, r0);
            }
        }
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
