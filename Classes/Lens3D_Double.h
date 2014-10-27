//
//  Lens3D_Double.h
//  touch_OP
//
//  Created by ohtaisao on 2014/10/27.
//
//

#ifndef __touch_OP__Lens3D_Double__
#define __touch_OP__Lens3D_Double__

#include "2d/CCActionGrid.h"

NS_CC_BEGIN

class CC_DLL Lens3D_Double : public Grid3DAction
{
public:
    /** creates the action with center position, radius, a grid size and duration */
    static Lens3D_Double* create(float duration, const Size& gridSize, const Vector<Vec2>& pos_arr,  const Vector<float>& radiuses);
    
    /** Get lens center position */
    inline float getLensEffect() const { return _lensEffect; }
    /** Set lens center position */
    inline void setLensEffect(float lensEffect) { _lensEffect = lensEffect; }
    /** Set whether lens is concave */
    inline void setConcave(bool concave) { _concave = concave; }
    
    inline const Vec2& getPosition() const { return _position; }
    void setPosition(const Vector<Vec2>& pos_arr);
    
    // Overrides
    virtual Lens3D_Double* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Lens3D_Double() {}
    virtual ~Lens3D_Double() {}
    
    /** initializes the action with center position, radius, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, const Vector<Vec2>& pos_arr, const Vector<float>& radiuses);
    
protected:
    /* lens center position */
    Vec2 _position;
    Vector<Vec2> _pos_arr;
    
    float _radius;
    Vector<float> _radiuses;
    /** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect */
    float _lensEffect;
    /** lens is concave. (true = concave, false = convex) default is convex i.e. false */
    bool _concave;
    
    bool _dirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Lens3D_Double);

};

NS_CC_END

#endif /* defined(__touch_OP__Lens3D_Double__) */
