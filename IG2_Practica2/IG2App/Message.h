#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MessageType { DEFAULT, AVION, CHECK_COLLISION, ALLDRONDEAD };

struct Message {
	MessageType id_;
};

#endif 