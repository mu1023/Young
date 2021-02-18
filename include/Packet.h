#pragma once
#include<YoungDefine.h>
#include<NetWorkAPI.h>
#include<google/protobuf/message.h>
namespace Young
{
	class Packet
	{
	public:
		const static size_t HEAD_SIZE = sizeof(UInt32) + sizeof(UInt32);

		Packet(UInt32 Size = 65536);

		void SetSize(UInt32 ssize){ m_Size = ssize;}
		UInt32 GetSize(){return m_Size; }

		void SetMessageId(UInt32 messageId){ m_MessageId = messageId;}
		UInt32 GetMessageId(){return m_MessageId; }

		SocketFd GetSocketFd(){return m_Id; }
		void  SetSocketFd(SocketFd fd){ m_Id=fd; }
	private:
		UInt32  m_Size;
		//–≠“È∫≈
		UInt32	m_MessageId;
		//
		SocketFd m_Id;
		
		google::protobuf::Message* m_Message;
	};
}


