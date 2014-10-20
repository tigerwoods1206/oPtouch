//
//  WaveShift3D.h
//  touch_OP
//
//  Created by ohtaisao on 2014/10/17.
//
//

#ifndef __touch_OP__WaveShift3D__
#define __touch_OP__WaveShift3D__

#include "2d/CCActionGrid.h"

NS_CC_BEGIN

class CC_DLL WaveShift3D : public Grid3DAction
{
public:
    /** creates an action with duration, grid size, waves and amplitude */
    static WaveShift3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);
    
    /** returns the amplitude of the effect */
    inline float getAmplitude() const { return _amplitude; }
    /** sets the amplitude to the effect */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }
    
    /** returns the amplitude rate */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /** sets the ampliture rate */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }
    
    // Overrides
    virtual WaveShift3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    WaveShift3D() {}
    virtual ~WaveShift3D() {}
    
    /** initializes an action with duration, grid size, waves and amplitude */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);
    
protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(WaveShift3D);
};

class Calc
{
    // 各種定数
    double eps = 1e-04;  // 精度
    
    // 各種変数
    double x;  // X 値
    double e;  // e 値
    double d;  // d 和
    double s;  // s 和
    int k;     // LOOP インデックス
    
public:
    // exp 計算
    double calcExp(double x);
};


NS_CC_END

#endif /* defined(__touch_OP__WaveShift3D__) */
