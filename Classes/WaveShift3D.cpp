//
//  WaveShift3D.cpp
//  touch_OP
//
//  Created by ohtaisao on 2014/10/17.
//
//

#include "WaveShift3D.h"
#include "base/CCDirector.h"
#include <stdlib.h>
#include <math.h>

NS_CC_BEGIN

WaveShift3D *WaveShift3D::create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    WaveShift3D *pAction = new WaveShift3D();
    
    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, waves, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }
    
    return pAction;
}

bool WaveShift3D::initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;
        
        return true;
    }
    
    return false;
}

WaveShift3D* WaveShift3D::clone() const
{
    // no copy constructor
    auto a = new WaveShift3D();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude);
    a->autorelease();
    return a;
}

void WaveShift3D::update(float time)
{
    Calc objCalc;
    int i, j;
    for (i = 0; i < _gridSize.width + 1; ++i)
    {
        for (j = 0; j < _gridSize.height + 1; ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i ,j));
            Vec3 v_n = getOriginalVertex(Vec2(i ,j));
            v_n.normalize();
            float y = v_n.y;
            
           // y-= _gridSize.height/2;
           // y = y/_gridSize.height;
          
            float x = v_n.x;
            //x-= _gridSize.width/2;
          //  x = x/_gridSize.width;
           // x = x*0.0001f;
          
            //float sin_time = sin(time*(float)M_PI * _waves * 2);
            float gaussian = (std::powl(10, (-( (y*y + x*x))) ));
            v.z += gaussian;
            
            //CCLOG("gaussian = %lf  v.z offset is %lf\n", gaussian,v.z);
            setVertex(Vec2(i, j), v);
        }
    }
}

double Calc::calcExp(double x)
{
    // 変数初期化
    d = 1.0;
    s = 1.0;
    e = 1.0;
    
    // 最大200回ループ処理
    for(k = 1; k <= 200; k++) {
        d = s;                // d 和
        e = e * fabs(x) / k;  // e 値
        s += e;               // s 和
        // 打ち切り誤差
        if (fabs(s - d) / fabs(d) < eps) {
            if (x > 0)
                return(s);
            else
                return(1.0 / s);
        }
    }
    
    // 収束しない時
    return(0.0);
}


NS_CC_END
