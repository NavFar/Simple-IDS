#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Packet.h"
#include "PacketDirection.h"
#include "TimedDataPipe.h"
#include "WordSensitiveDataPipe.h"
#include "vector"
#include "configs.h"
using namespace std;
int main(int argc, char **argv) {
	ifstream inputFile ("/home/navidfarahmand/Desktop/sample-traffic.txt", ios::in);
	string line, word,lineNumber;
	TimedDataPipe dosPipe= TimedDataPipe();
	vector<string> sqlivalues{SQLI_WORDS};
	vector<string> xssvalues{XSS_WORDS};
	WordSensitiveDataPipe sqliPipe = WordSensitiveDataPipe(sqlivalues);
	WordSensitiveDataPipe xssPipe = WordSensitiveDataPipe(xssvalues);
	Packet packet;
	while(!inputFile.eof()){
		std::getline(inputFile,line);
		istringstream splitStream(line);
		Packet packet;
		splitStream>>lineNumber; //read packet number
		splitStream>>word; //read packet direction
		transform(word.begin(),word.end(),word.begin(), ::tolower);
		if(word == "in"){
		packet.setDirection(PacketDirection::IN);
		}
		else if(word == "out"){
			packet.setDirection(PacketDirection::OUT);
		}
		else {
			std::cerr<<"malformed packet direciton in line" <<lineNumber<<endl;
			continue;
		}
		splitStream>>word; //read packet sender's Ip
		packet.setSenderIp(word);

		splitStream>>word; //read packet reciever's Ip
		packet.setRecieverIp(word);

		if(packet.getDirection() == PacketDirection::IN) {
			splitStream>>word; //read packet url
			packet.setUrl(word);
		}

		splitStream>>word; //read packet timestamp
		try{
			packet.setTimestamp(std::stol(word));
		}catch (const exception &e){
			cerr<<"timestamp is malformed in line "<<lineNumber<<endl;
			continue;
		}
		dosPipe.addToPipe(packet);
		sqliPipe.addToPipe(packet);
		xssPipe.addToPipe(packet);

//		cout<<dosPipe.getPipeState()<<endl;
//		cout<<packet<<endl;



	}
	cout<<xssPipe.getPipeState();
	cout<<sqliPipe.getPipeState();
	return 0;
}
