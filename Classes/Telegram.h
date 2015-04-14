//
//  Telegram.h
//  BGT
//
//  Created by John Running on 15/3/5.
//
//

#ifndef BGT_Telegram_h
#define BGT_Telegram_h

struct Telegram
{
    //the entity that sent this telegram
    int          sender;
    
    //the entity that is to receive this telegram
    int          receiver;
    
    //the message itself. These are all enumerated in the file
    //"MessageTypes.h"
    int          msg;
    
    //messages can be dispatched immediately or delayed for a specified amount
    //of time. If a delay is necessary, this field is stamped with the time
    //the message should be dispatched.
    double       dispatchTime;
    
    //any additional information that may accompany the message
    void*        extraInfo;
    
    Telegram():dispatchTime(-1),
    sender(-1),
    receiver(-1),
    msg(-1)
    {}
    
    Telegram(double     delayTime,
             int        senderV,
             int        receiverV,
             int        msgV,
             void*      extraInfoV = NULL) {dispatchTime=delayTime;sender=senderV;receiver=receiverV;msg=msgV;extraInfo=extraInfoV;}
};

//these telegrams will be stored in a priority queue. Therefore the >
//operator needs to be overloaded so that the PQ can sort the telegrams
//by time priority. Note how the times must be smaller than
//SmallestDelay apart before two Telegrams are considered unique.
const double SmallestDelay = 0.25;

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
    return ( fabs(t1.dispatchTime-t2.dispatchTime) < SmallestDelay) &&
    (t1.sender == t2.sender)        &&
    (t1.receiver == t2.receiver)    &&
    (t1.msg == t2.msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
    if (t1 == t2)
    {
        return false;
    }
    
    else
    {
        return  (t1.dispatchTime < t2.dispatchTime);
    }
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
    os << "time: " << t.dispatchTime << "  Sender: " << t.sender
    << "   Receiver: " << t.receiver << "   Msg: " << t.msg;
    
    return os;
}

//handy helper function for dereferencing the ExtraInfo field of the Telegram
//to the required type.
template <class T>
inline T DereferenceToType(void* p)
{
    return *(T*)(p);
}

#endif
