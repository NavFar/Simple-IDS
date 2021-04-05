#ifndef DATAPIPE_H_
#define DATAPIPE_H_

#include<deque>
#include "PipeState.h"
#include "Packet.h"

class DataPipe {
protected:
	std::deque<Packet> pipeData;
	PipeState pipeState;
public:
	DataPipe();
	virtual ~DataPipe();
	virtual PipeState getPipeState();
	virtual void calculatePipeState()=0;
	virtual void addToPipe(Packet)=0;
	virtual void initializePipe();

};

#endif /* DATAPIPE_H_ */
