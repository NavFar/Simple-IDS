#include "TimedDataPipe.h"
#include "configs.h"

TimedDataPipe::TimedDataPipe():DataPipe() {
	this->initializePipe();
}

TimedDataPipe::~TimedDataPipe() {
	// TODO Auto-generated destructor stub
}
void TimedDataPipe::addToPipe(Packet packet){
	this->pipeData.push_back(packet);
	this->lastCheckTime = packet.getTimestamp();
	this->calculatePipeState();
}
void TimedDataPipe::calculatePipeState(){
	while(this->pipeData.front().getTimestamp() + DOS_INTERVAL < this->lastCheckTime){
		this->pipeData.pop_front();
	}
	if(this->pipeData.back().getDirection() == PacketDirection::OUT)
		return;
	int counter = 1;
	for(int i=0;i<this->pipeData.size()-1;i++){
		if( this->pipeData.at(i).getDirection() == PacketDirection::IN
			&& this->pipeData.at(i).getRecieverIp()== this->pipeData.back().getRecieverIp()
			&& this->pipeData.at(i).getSenderIp() == this->pipeData.back().getSenderIp())
			counter++;
	}
	if(counter >=DOS_LIMIT)
		this->pipeState = PipeState::NOT_OK;

}
void TimedDataPipe:: initializePipe(){
	DataPipe::initializePipe();
	this->lastCheckTime = 0;
}

