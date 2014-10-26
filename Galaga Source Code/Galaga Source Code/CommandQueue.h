#ifndef CommandQueue_h
#define CommandQueue_h
#include "Command.h"
#include <queue>

class CommandQueue;

class CommandQueue {
public:
	void		push(const Command& command);
	Command		pop();
	bool		isEmpty() const;

private:
	std::queue<Command> mQueue;
};

#endif