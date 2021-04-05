/*
 * TimedDataPipe.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: navidfarahmand
 */

#include "TimedDataPipe.h"

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
	std::cout<<"pipe Size is "<< this->pipeData.size()<<std::endl;
	while(this->pipeData.front().getTimestamp() +1000 < this->lastCheckTime){
		this->pipeData.pop_front();
		std::cout<<"Deleted "<<this->pipeData.size()<<std::endl;
	}
	if(this->pipeData.back().getDirection() == PacketDirection::OUT)
		return;
	int counter = 0;
	for(int i=0;i<this->pipeData.size()-1;i++){
		if( this->pipeData.at(i).getDirection() == PacketDirection::IN
			&& this->pipeData.at(i).getRecieverIp()== this->pipeData.back().getRecieverIp()
			&& this->pipeData.at(i).getSenderIp() == this->pipeData.back().getSenderIp())
			counter++;
	}
	if(counter >=3-1)
		this->pipeState = PipeState::NOT_OK;

}
void TimedDataPipe:: initializePipe(){
	DataPipe::initializePipe();
	this->lastCheckTime = 0;
}

