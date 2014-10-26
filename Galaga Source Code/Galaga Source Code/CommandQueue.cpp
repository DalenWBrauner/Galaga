#include "CommandQueue.h"

// CommandQueue Definitions
void CommandQueue::push(const Command& command) {
	mQueue.push(command);
}

Command CommandQueue::pop() {
	Command return_value = mQueue.front();
	mQueue.pop();	// Apparently doesn't return anything
	return return_value;
}

bool CommandQueue::isEmpty() const {
	return mQueue.empty();
}