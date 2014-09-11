//
//  Plane.cpp
//  Moon3d
//
//  Created by Rye on 14-3-13.
//
//

#include "Plane.h"
#include "3d/Sprite3D.h"

bool Plane::init(){
    bool isUsePic = false;
    bool isUse3d = true;
    if (rand()/(RAND_MAX+1.0) < 0.2){
        _Model = Sprite3D::create("boss.obj", "boss.png");
    }else{
        _Model = Sprite3D::create("playerv002.obj", "playerv002_256.png");
    }
    
    auto sp = Sprite::create("CloseSelected.png");
    if(isUse3d && _Model){
        _Model->setScale(10);
        ((Sprite3D*)_Model)->setOutline(0.05, Color3B::BLACK);
//        _Model->setRotation3D(Vertex3F(originX,originY,originZ));
//        this->setPosition3D(cocos2d::Vertex3F(300.0, 350.0, 0));
        this->setRotation3D(Vertex3F(90, 0, 0));
        this->addChild(_Model);
        this->scheduleUpdate();
    }
    if (isUsePic) {
         this->addChild(sp);   
    }
    status_ = ST_STAY;
    return true;
}
int Plane::getState(){
    return status_;
}
void Plane::setState(STATE st){
    status_ = st;
}
void Plane::setTarget(cocos2d::Vertex3F t, float scale, cocos2d::Vertex3F rotation){
    if (status_ == ST_MOVING) {
        setRotation3D(tarRotation);
        setScale(tarScale);
        setPosition3D(targetPos);
    }
    tarScale = scale;
    targetPos = t;
    tarRotation = rotation;
    isSettedValue = true;
    status_ = ST_MOVING;
}

Vertex3F Plane::getTargetPos(){
    if (isSettedValue)
    {
        return targetPos;
    }
    return getPosition3D();
    
}
Vertex3F Plane::getTargetRot(){
    if (isSettedValue)
    {
        return tarRotation;
    }
    return getRotation3D();
}
float Plane::getTargetScal(){
    if (isSettedValue)
    {
        return tarScale;
    }
    return getScale();
}

float getDist(float x, float y, float z){
    return sqrtf(x*x + y*y + z*z);
}
void Plane::update(float dt){
   pRate+=0.1;
   _Model->setRotation3D(Vertex3F(0, pRate/2, pRate));
    switch (status_) {
        case ST_MOVING:
            goMovingStat(dt);
            break;
            
        default:
            break;
    }
}

void Plane::goMovingStat(float dt){
    float ratio = 20.0;
    cocos2d::Vertex3F position = getPosition3D();
    float dx = (targetPos.x - position.x) / ratio;
    float dy = (targetPos.y - position.y) / ratio;
    float dz = (targetPos.z - position.z) / ratio;
    float scale = getScale();
    float ds = (tarScale - scale) / ratio;
    if (getDist(dx,dy,dz) < 0.01) {
        status_ = ST_STAY;
        setPosition3D(targetPos);
        setScale(tarScale);
        setRotation3D(tarRotation);
        return;
    }
    
    setScale(scale+ds);
    setPosition3D(cocos2d::Vertex3F(position.x+dx, position.y+dy, position.z+dz));
    
    // 设置角度
    cocos2d::Vertex3F rotation = getRotation3D();
    dx = (tarRotation.x - rotation.x) / ratio;
    dy = (tarRotation.y - rotation.y) / ratio;
    dz = (tarRotation.z - rotation.z) / ratio;
    setRotation3D(cocos2d::Vertex3F(rotation.x+dx, rotation.y+dy, rotation.z+dz));
}




