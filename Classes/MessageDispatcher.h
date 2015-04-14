//
//  MessageDispatcher.h
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#ifndef __BGT__MessageDispatcher__
#define __BGT__MessageDispatcher__
#include "cocos2d.h"
#include "Utils.h"
class GameEntity;
class GameEntityManager;

//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;

USING_NS_CC;

class MessageDispatcher : public Ref
{
private:
    
    //a std::set is used as the container for the delayed messages
    //because of the benefit of automatic sorting and avoidance
    //of duplicates. Messages are sorted by their dispatch time.
    std::set<Telegram> priorityQ;
    //Vector<Telegram> priorityQ;
    
    //this method is utilized by DispatchMessage or DispatchDelayedMessages.
    //This method calls the message handling member function of the receiving
    //entity, pReceiver, with the newly created telegram
    void discharge(GameEntity* pReceiver, const Telegram& msg);
    
    MessageDispatcher(){}
    
    //copy ctor and assignment should be private
    MessageDispatcher(const MessageDispatcher&);
    MessageDispatcher& operator=(const MessageDispatcher&);
    
public:
    virtual bool init();
    //this class is a singleton
    static MessageDispatcher* getInstance();
    
    //send a message to another agent.
    void dispatchMessage(double      delay,
                         int         sender,
                         int         receiver,
                         int         msg,
                         void*       ExtraInfo);
    
    //send out any delayed messages. This method is called each time through
    // the main game loop.
    void dispatchDelayedMessages();
};

#endif /* defined(__BGT__MessageDispatcher__) */
