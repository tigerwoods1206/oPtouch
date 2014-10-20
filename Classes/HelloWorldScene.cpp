#include "HelloWorldScene.h"

USING_NS_CC;

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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto changeImageItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuChangeImageCallback, this));
    
    changeImageItem->setPosition(Vec2(origin.x + visibleSize.width - changeImageItem->getContentSize().width/2 ,
                                origin.y + changeImageItem->getContentSize().height + 50));
    
    // create menu, it's an autorelease object
    auto menu2 = Menu::create(changeImageItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 2);


    /////////////////////////////
    // 3. add your codes below...

    // add "HelloWorld" splash screen"
    one_sprite = Sprite::create("slimewallpaper1024x768.jpg");
    //one_sprite->setScale(0.7, 0.7);

    // position the sprite on the center of the screen
    one_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    spriteCenter = one_sprite->getPosition();
    opSize       = one_sprite->getContentSize().width * 0.2;
    touchPower   = opSize;
    touchPos     = spriteCenter;
    // create a Waved3D action
    //ActionInterval* waves = Waves3D::create(10, Size(15,10), 18, 15);
    
    one_nodeGrid = NodeGrid::create();
    one_nodeGrid->addChild(one_sprite);
    
    //this->setTotu(one_sprite, one_nodeGrid);
    
    this->scheduleUpdate();
    
    //event listener
    //イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create();
    
    //イベントを飲み込むかどうか
    listener->setSwallowTouches(true);
    
    //タッチメソッド設定
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    //優先度100でディスパッチャーに登録
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    this->addChild(one_nodeGrid);
    
    return true;
}

//-------------------------
// タップ時
bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    /*
    Point location = touch->getLocation();
    CCLOG("x:%f, y:%f", location.x, location.y);
    
    // create a Waved3D action
    
    Size spsize = one_sprite->getContentSize();
     log("%f, %f", one_sprite->getContentSize().width, one_sprite->getContentSize().height);
    //one_sprite->getPosition();
    Action* waves = Lens3D::create(1, Size(10,10),location, 200);
    one_nodeGrid->runAction(waves);
     */
    
    isTouched = true;
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    
    Point location = touch->getLocation();
    CCLOG("x:%f, y:%f, r%f", location.x, location.y, touch->getMajorRadius());
    touchPos = location;
    
    // create a Waved3D action
    
    Size spsize = one_sprite->getContentSize();
    //log("%f, %f", one_sprite->getContentSize().width, one_sprite->getContentSize().height);
    //one_sprite->getPosition();
    float radius = touch->getMajorRadius();
    //touchPower = opSize * (1.0 - radius / opSize);
    touchPower = radius*3;
    /*
    float power  = opSize * (1.0 - radius / opSize);
    Action* waves = Lens3D::create(1/60, Size(10,10),location, power);
    one_nodeGrid->runAction(waves);
     */
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    
    isTouched = false;
    
    Point location = touch->getLocation();
    CCLOG("x:%f, y:%f", location.x, location.y);
    touchPos = location;
    
    // create a Waved3D action
    
    float radius = touch->getMajorRadius();
    //touchPower = opSize * (1.0 - radius*radius / (opSize*opSize));
    touchPower = radius*3;
    Size spsize = one_sprite->getContentSize();
    //log("%f, %f", one_sprite->getContentSize().width, one_sprite->getContentSize().height);
    //one_sprite->getPosition();
    
    ActionInterval* lipple = CCRipple3D::create(0.2, Size(10, 10), touchPos, touchPower, 1, 20);
    
    //ActionInterval* waves = Waves3D::create(0.2, Size(10,10), 2, 30);
    ActionInterval* lens = Lens3D::create(0.5, Size(100,100),touchPos, opSize);
    Sequence* sequence = Sequence::create(lipple, lens, NULL);

    one_nodeGrid->runAction(sequence);
    
    //this->setTotu(one_sprite, one_nodeGrid);
}

void HelloWorld::setTotu(Sprite *sp, NodeGrid *gr ){
    if (sp== nullptr) {
        return;
    }
    
    if (gr== nullptr) {
        return;
    }
    
   // Size spsize = one_sprite->getContentSize();
    Action* waves = Lens3D::create(0.5, Size(100,100),spriteCenter, opSize);
    one_nodeGrid->runAction(waves);
}

void HelloWorld::update(float delta)
{
    if (isTouched) {
        Action* waves = Lens3D::create(0.5, Size(100,100),touchPos, touchPower);
        waves->startWithTarget(one_nodeGrid);
        waves->update(delta);
    }
}

void HelloWorld::menuChangeImageCallback(Ref* pSender)
{
    if(!toggleImage) {
        toggleImage = true;
        this->replaceImage(one_sprite, "g_sample.png");
        
    }
    else {
        toggleImage = false;
        this->replaceImage(one_sprite, "slimewallpaper1024x768.jpg");
    }
    //one_sprite->setScale(0.7, 0.7);
}

void HelloWorld::replaceImage(Sprite *sprite, const char *imageFileName)
{
    Texture2D *tex = TextureCache::sharedTextureCache()->addImage(imageFileName);
    sprite->setTexture(tex);
    Size contentSize = tex->getContentSize();
    sprite->setTextureRect(CCRectMake(0, 0, contentSize.width, contentSize.height));
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
