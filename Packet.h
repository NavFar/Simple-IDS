
#ifndef PACKET_H_
#define PACKET_H_
#include "PacketDirection.h"
#include <string>
class Packet{
	private:
		long timestamp;
		PacketDirection direction;
		std::string senderIp;
		std::string recieverIp;
		std::string url;
	public:
		Packet();
		Packet(std::string, std::string, std::string, PacketDirection, long);
		PacketDirection getDirection() const;
		void setDirection(PacketDirection direction);
		const std::string& getRecieverIp() const;
		void setRecieverIp(const std::string &recieverIp);
		const std::string& getSenderIp() const;
		void setSenderIp(const std::string &senderIp);
		long getTimestamp() const;
		void setTimestamp(long timestamp);
		const std::string& getUrl() const;
		void setUrl(const std::string &url);
		friend std::ostream& operator<<(std::ostream &, const Packet &);
};




#endif /* PACKET_H_ */
