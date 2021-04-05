#ifndef TIMEDDATAPIPE_H_
#define TIMEDDATAPIPE_H_

#include <queue>
#include "DataPipe.h"
#include "PipeState.h"
#include "Packet.h"

class TimedDataPipe: public DataPipe {
private:
	long lastCheckTime;

public:
	TimedDataPipe();
	virtual ~TimedDataPipe();
	void addToPipe(Packet);
	void calculatePipeState();
	void initializePipe();
};

#endif /* TIMEDDATAPIPE_H_ */
