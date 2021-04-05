/*
 * Packet.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: navidfarahmand
 */
#include "Packet.h"
#include <string>
#include <iostream>
#include "PacketDirection.h"
Packet::Packet(){
}
Packet::Packet(std::string senderIp, std::string recieverIp, std::string url, PacketDirection direction, long timestamp){
	this->senderIp = senderIp;
	this->recieverIp = recieverIp;
	this->url = url;
	this->direction = direction;
	this->timestamp = timestamp;
}

PacketDirection Packet::getDirection() const {
	return direction;
}

void Packet::setDirection(PacketDirection direction) {
	this->direction = direction;
}

const std::string& Packet::getRecieverIp() const {
	return recieverIp;
}

void Packet::setRecieverIp(const std::string &recieverIp) {
	this->recieverIp = recieverIp;
}

const std::string& Packet::getSenderIp() const {
	return senderIp;
}

void Packet::setSenderIp(const std::string &senderIp) {
	this->senderIp = senderIp;
}

long Packet::getTimestamp() const {
	return timestamp;
}

void Packet::setTimestamp(long timestamp) {
	this->timestamp = timestamp;
}

const std::string& Packet::getUrl() const {
	return url;
}

void Packet::setUrl(const std::string &url) {
	this->url = url;
}

std::ostream& operator<< (std::ostream &out , const Packet & packet){
	return out<<packet.direction<<" "<<packet.senderIp<<" --> "<<packet.recieverIp<<"  ("<<packet.url<<") ["<<packet.timestamp<<"]";
}

