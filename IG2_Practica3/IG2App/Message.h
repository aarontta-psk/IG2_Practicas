#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MessageType { DEFAULT, STOP_ALL_ENTITIES, CHECK_COLLISION, ALL_DRON_DEAD };

struct Message {
	MessageType id_;
};

#endif 