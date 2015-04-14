//
//  MessageDispatcher.cpp
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#include "MessageDispatcher.h"
#include "GameEntity.h"
#include "GameEntityManager.h"

static MessageDispatcher *s_SharedManager = NULL;



//this must reside in the cpp file; otherwise, an instance will be created
//for every file in which the header is included
MessageDispatcher* MessageDispatcher::getInstance()
{
    //    static GameEntityManager instance;
    //    return &instance;
    
    if (!s_SharedManager)
    {
        s_SharedManager = new MessageDispatcher();
        s_SharedManager->init();
    }
    
    return s_SharedManager;
}

bool MessageDispatcher::init()
{
    return true;
}

void MessageDispatcher::dispatchMessage(double     delay,
                                        int        sender,
                                        int        receiver,
                                        int        msg,
                                        void*      extraInfo)
{
    //get a pointer to the receiver of the message
    GameEntity* pReceiver = GameEntityManager::getInstance()->getEntityFromID(receiver);
    //make sure the receiver is valid
    if (pReceiver == NULL)
    {
#ifdef SHOW_MESSAGING_INFO
        debug_con << "\nWarning! No Receiver with ID of " << receiver << " found" << "";
#endif
        
        return;
    }
    //create the telegram
    Telegram telegram(0, sender, receiver, msg, extraInfo);
    
    //if there is no delay, route the telegram immediately
    if (delay <= 0.0)
    {
#ifdef SHOW_MESSAGING_INFO
        debug_con << "\nTelegram dispatched at time: " << TickCounter->GetCurrentFrame()
        << " by " << sender << " for " << receiver
        << ". Msg is " << msg << "";
#endif
        //send the telegram to the recipient
        discharge(pReceiver, telegram);
    }//else calculate the time when the telegram should be dispatched
    else
    {
        double currentTime = millisecondNow();
        
        telegram.dispatchTime = currentTime + delay;
        
        //and put it in the queue
        priorityQ.insert(telegram);
        
#ifdef SHOW_MESSAGING_INFO
        debug_con << "\nDelayed telegram from " << sender << " recorded at time "
        << TickCounter->GetCurrentFrame() << " for " << receiver
        << ". Msg is " << msg << "";
#endif
    }
}

void MessageDispatcher::dispatchDelayedMessages()
{
    //first get current time
    double currentTime = millisecondNow();
    
    //now peek at the queue to see if any telegrams need dispatching.
    //remove all telegrams from the front of the queue that have gone
    //past their sell-by date
    while(!priorityQ.empty() && (priorityQ.begin()->dispatchTime < currentTime) &&
          (priorityQ.begin()->dispatchTime > 0) )
    {
        //read the telegram from the front of the queue
        const Telegram telegram = *priorityQ.begin();
        
        //find the recipient
        GameEntity* pReceiver = GameEntityManager::getInstance()->getEntityFromID(telegram.receiver);
#ifdef SHOW_MESSAGING_INFO
        debug_con << "\nQueued telegram ready for dispatch: Sent to "
        << pReceiver->ID() << ". Msg is "<< telegram.Msg << "";
        
        //    char msg[256] = {0};
        //sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
#endif
        //send the telegram to the recipient
        discharge(pReceiver, telegram);
        
        //and remove it from the queue
        priorityQ.erase(priorityQ.begin());
    }
}

void MessageDispatcher::discharge(GameEntity* pReceiver, const Telegram& msg)
{
    if (!pReceiver->handleMessage(msg))
    {
        //telegram could not be handled
#ifdef SHOW_MESSAGING_INFO
        debug_con << "Message not handled" << "";
#endif
    }
}
