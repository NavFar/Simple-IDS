/*
 * WordSensitiveDataPipe.h
 *
 *  Created on: Apr 5, 2021
 *      Author: navidfarahmand
 */

#ifndef WORDSENSITIVEDATAPIPE_H_
#define WORDSENSITIVEDATAPIPE_H_

#include "DataPipe.h"
#include <vector>
#include <deque>
#include <string>


class WordSensitiveDataPipe: public DataPipe {
private:
	std::vector<std::string> sensitiveWords;
	std::deque<bool> isPacketDangerous;
public:
	WordSensitiveDataPipe(std::vector<std::string>&);
	virtual ~WordSensitiveDataPipe();
	void addToPipe(Packet);
	void initializePipe();
	PipeState getPipeState();
	void calculatePipeState();

};

#endif /* WORDSENSITIVEDATAPIPE_H_ */
