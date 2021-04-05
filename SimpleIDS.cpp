#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "Packet.h"
#include "PacketDirection.h"
#include "TimedDataPipe.h"
#include "WordSensitiveDataPipe.h"
#include "vector"
#include "configs.h"
#include <filesystem>
#include <sstream>
using namespace std;
namespace	 fs = std::filesystem;

string validateTraffic(string const &);
int main(int argc, char **argv) {

	if(argc<2){
		std::cerr<<"need to get directory address"<<std::endl;
		return 1;
	}
	try{
	if(!fs::exists(argv[1])){
		std::cerr<<"no such directory"<<std::endl;
		return 1;
	}
	if(!fs::is_directory(argv[1])){
		std::cerr<<"not a directory"<<std::endl;
		return 1;
	}
	fs::path trafficDirectory(argv[1]);
	stringstream temporaryStream;
	for (const auto & file : fs::recursive_directory_iterator(trafficDirectory))
//	        cout << file.path() << endl;
	{
		temporaryStream <<file.path().filename()<<" --> "<< validateTraffic(file.path())<<endl;
	}
	ofstream fileoutput(trafficDirectory /"report.txt",ios::out);
	fileoutput<<temporaryStream.rdbuf();
	fileoutput.close();
	std::cout<<"Report has been created in "<<(trafficDirectory /"report.txt")<<std::endl;

	}catch (exception &exception){
		std::cerr<<"error reading files"<<std::endl;
		return 1;
	}
	return 0;




	return 0;
}
string validateTraffic(string const &  path){

	ifstream inputFile (path, ios::in);
	TimedDataPipe dosPipe= TimedDataPipe();
	vector<string> sqlivalues{SQLI_WORDS};
	vector<string> xssvalues{XSS_WORDS};
	WordSensitiveDataPipe sqliPipe = WordSensitiveDataPipe(sqlivalues,SQLI_LIMIT);
	WordSensitiveDataPipe xssPipe = WordSensitiveDataPipe(xssvalues,XSS_LIMIT);
	Packet packet;
	while(!inputFile.eof()){
		string line, word,lineNumber;
		std::getline(inputFile,line);
		istringstream splitStream(line);
		Packet packet;
		splitStream>>lineNumber; //read packet number
		if(lineNumber.empty()){
			continue;
		}
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
	}
	string result ="DOS attack : ";
	result +=dosPipe.getPipeState()?"TRUE":"FALSE";
	result +="\t SQLI attack : ";
	result +=sqliPipe.getPipeState()?"TRUE":"FALSE";
	result +="\t XSS attack : ";
	result +=xssPipe.getPipeState()?"TRUE":"FALSE";
	return result;
}
