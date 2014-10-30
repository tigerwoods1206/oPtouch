#ifndef __ImagePicker__ImagePicker__
#define __ImagePicker__ImagePicker__

#include "cocos2d.h"

using namespace cocos2d;

class ImagePickerDelegate {
public:
    virtual void didFinishPickingWithResult(Texture2D* result) = 0;
};

class ImagePicker{
public:
    ImagePicker();
    static ImagePicker *getInstance();
    
    void pickImage();
    void finishImage(cocos2d::Texture2D *image);
    CC_SYNTHESIZE(ImagePickerDelegate*,m_delegate,Delegate);//◎◎
private:
    ImagePickerDelegate *_delegate;
};

#endif /* defined(__ImagePicker__ImagePicker__) */
