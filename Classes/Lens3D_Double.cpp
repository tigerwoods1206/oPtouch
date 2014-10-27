//
//  Lens3D_Double.cpp
//  touch_OP
//
//  Created by ohtaisao on 2014/10/27.
//
//

#include "Lens3D_Double.h"

// implementation of Lens3D_Double

NS_CC_BEGIN

Lens3D_Double* Lens3D_Double::create(float duration, const Size& gridSize, const std::vector<Vec2>& pos_arr,  const std::vector<float>& radiuses)
{
    Lens3D_Double *action = new Lens3D_Double();
    
    if (action)
    {
        if (action->initWithDuration(duration, gridSize, pos_arr, radiuses))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }
    
    return action;
}

bool Lens3D_Double::initWithDuration(float duration, const Size& gridSize, const std::vector<Vec2>& pos_arr,  const std::vector<float>& radiuses)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        
        for(int i = 0; i < pos_arr.size();i++){
            //log("tag %d",position.at(i)->equals());
            Vec2 tmp = Vec2(-1, -1);
            _pos_arr.push_back(tmp);
        }
        
       // _position = Vec2(-1, -1);
        
        setPosition(pos_arr);
        //_radius = radius;
        _radiuses = radiuses;
        _lensEffect = 0.7f;
        _concave = false;
        _dirty = true;
        
        return true;
    }
    
    return false;
}

Lens3D_Double* Lens3D_Double::clone() const
{
    // no copy constructor
    auto a = new Lens3D_Double();
    a->initWithDuration(_duration, _gridSize, _pos_arr, _radiuses);
    a->autorelease();
    return a;
}

void Lens3D_Double::setPosition(const std::vector<Vec2>& pos_arr)
{
    for(int i = 0; i < pos_arr.size();i++){
        //log("tag %d",position.at(i)->equals());
        if (!pos_arr.at(i).equals(_pos_arr.at(i))) {
            _pos_arr.at(i) = pos_arr.at(i);
            _dirty = true;
        }
    }
    /*
    if( !pos.equals(_pos_arr))
    {
        _position = pos;
        _dirty = true;
    }
     */
}

void Lens3D_Double::update(float time)
{
    CC_UNUSED_PARAM(time);
    if (_dirty)
    {
        int i, j;
        
        for (i = 0; i < _gridSize.width + 1; ++i)
        {
            for (j = 0; j < _gridSize.height + 1; ++j)
            {
                Vec3 v = getOriginalVertex(Vec2(i, j));
                
                for(int i = 0; i < _pos_arr.size();i++){
                    Vec2 vect = _pos_arr.at(i) - Vec2(v.x, v.y);
                    float radius = _radiuses.at(i);
                    float r = vect.getLength();
                    
                    if (r < radius)
                    {
                        r = radius - r;
                        float pre_log = r / radius;
                        if ( pre_log == 0 )
                        {
                            pre_log = 0.001f;
                        }
                        
                        float l = logf(pre_log) * _lensEffect;
                        float new_r = expf( l ) * radius;
                        
                        if (vect.getLength() > 0)
                        {
                            vect.normalize();
                            Vec2 new_vect = vect * new_r;
                            v.z += (_concave ? -1.0f : 1.0f) * new_vect.getLength() * _lensEffect;
                        }
                    }
                    
                    setVertex(Vec2(i, j), v);
                }
            }
        }
        
        _dirty = false;
    }
}

NS_CC_END
