#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    //bool onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event);
    //void onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event);
    //void onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void menuChangeImageCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void update(float delta);
    
private:
    cocos2d::NodeGrid* one_nodeGrid;
    cocos2d::Sprite*   one_sprite;
    cocos2d::Point     spriteCenter;
    
    float opSize;
    float touchPower;
    cocos2d::Point touchPos;
    cocos2d::Vector<cocos2d::Vec2> touchPoses;
    cocos2d::Vector<float> touchRaduses;
    bool  isTouched = false;
    bool  toggleImage = true;
    
    void replaceImage(cocos2d::Sprite *sprite, const char *imageFileName);
    void setTotu(cocos2d::Sprite *sp, cocos2d::NodeGrid *gr );
    void set_Touchparams(cocos2d::Touch* touch);
    void unset_Touchparams();
    
};

#endif // __HELLOWORLD_SCENE_H__
