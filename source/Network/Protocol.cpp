#include "Protocol.h"


unsigned long dwWorldNum;
int DEPLOY_TYPE; //0 login - 1 world - 2 zone - 3 db
_WORLD_DATA g_WorldData[2];

/// <summary>
/// Sends data through the specified ns_connection.
/// </summary>
/// <returns>bytes sent</returns>
int send_data(struct ns_connection *nc, BYTE* pbyType, void* data, WORD len){
	char buffer[MAX_RECEIVE_SIZE];
	char* szMsg = (char*) data;

	_MSG_HEADER header;
	header.m_wSize = len + MSG_HEADER_SIZE;
	*(WORD*)header.m_byType = *(WORD*)pbyType;

	memcpy(&buffer[0], &header, MSG_HEADER_SIZE);
	memcpy(&buffer[MSG_HEADER_SIZE], szMsg, len);

	return ns_send(nc, buffer, header.m_wSize);
}