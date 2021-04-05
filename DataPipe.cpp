/*
 * DataPipe.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: navidfarahmand
 */

#include "DataPipe.h"

DataPipe::DataPipe() {
	this->initializePipe();
}

DataPipe::~DataPipe() {
	// TODO Auto-generated destructor stub
}
PipeState DataPipe::getPipeState(){
	return this->pipeState;
}
void DataPipe:: initializePipe(){
	this->pipeData = std::deque<Packet>();
	this->pipeState = PipeState::OK;
}
