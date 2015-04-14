//
//  LieDownState.h
//  BGT
//
//  Created by John Running on 15/3/13.
//
//

#ifndef __BGT__LieDownState__
#define __BGT__LieDownState__

//腾空后，蓄力往下打，掉地上躺两秒
#include "State.h"
class Character;
struct Telegram;

class LieDownState : public State<Character>
{
private:
    double startTime;
    //copy ctor and assignment should be private
    LieDownState(const LieDownState&);
    LieDownState& operator=(const LieDownState&);
public:
    explicit LieDownState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__LieDownState__) */
