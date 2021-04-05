#include "WordSensitiveDataPipe.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
WordSensitiveDataPipe::WordSensitiveDataPipe(std::vector<std::string>& sensitiveWords, long limit) {

	this->sensitiveWords = sensitiveWords;
	this->limit = limit;
}

WordSensitiveDataPipe::~WordSensitiveDataPipe() {
	// TODO Auto-generated destructor stub
}
void WordSensitiveDataPipe:: addToPipe(Packet packet) {
	this->pipeData.push_back(packet);
	if(packet.getDirection()==PacketDirection::OUT)
		this->isPacketDangerous.push_back(false);
	else {
		bool flag = false;
		for(int i=0;i<this->sensitiveWords.size();i++) {
			if( packet.getUrl().find(this->sensitiveWords.at(i)) !=std::string::npos ) {
				flag = true;
				break;
			}
		}
		this->isPacketDangerous.push_back(flag);
	}
}

void WordSensitiveDataPipe:: initializePipe() {
	DataPipe::initializePipe();
	this->sensitiveWords.clear();
	this->isPacketDangerous.clear();
}

PipeState WordSensitiveDataPipe:: getPipeState() {
	this->calculatePipeState();
	return DataPipe::getPipeState();
}

void WordSensitiveDataPipe:: calculatePipeState() {

	std::vector<bool> flags(this->pipeData.size(),true);

	for(int i=0;i<this->pipeData.size();i++) {

		if(!this->isPacketDangerous.at(i) || !flags.at(i))
		{
			continue;
		}
		long count=1;
		for(int j=i+1;j<this->pipeData.size();j++){
			if(this->isPacketDangerous.at(j))
			{
				if(this->pipeData.at(j).getSenderIp() == this->pipeData.at(i).getSenderIp()){
					count ++;
					flags.at(j)=false;
				}
			}
		}
		if(count >= this->limit){
			this->pipeState = PipeState::NOT_OK;
			return;
		}

	}

}

