#include "Session.h"

int Session::send_data(BYTE* _type, void* data, WORD len)
{
	char buffer[MAX_RECEIVE_SIZE];
	char* szMsg = (char*)data;

	_MSG_HEADER header;
	header.m_wSize = len + MSG_HEADER_SIZE;
	*(WORD*)header.m_byType = *(WORD*)_type;

	memcpy(&buffer[0], &header, MSG_HEADER_SIZE);
	memcpy(&buffer[MSG_HEADER_SIZE], szMsg, len);
	
	return ns_send(conn, buffer, header.m_wSize);
}

int Session::send_data_v2(BYTE* _type, void* data, WORD len)
{
	char buffer[MAX_RECEIVE_SIZE];
	char* szMsg = (char*)data;

	_MSG_HEADERv2 header;
	header.m_wSize = len;
	header.m_wPsize = len + MSG_HEADER_v2_SIZE;
	header.m_wPsize += MSG_FOOTER_SIZE;
	*(WORD*)header.m_byType = *(WORD*)_type;

	memcpy(&buffer[0], &header, MSG_HEADER_v2_SIZE);
	memcpy(&buffer[MSG_HEADER_v2_SIZE], szMsg, len);

	_MSG_FOOTER ft; ft._c = 0; ft._t = 4;
	memcpy(&buffer[len + MSG_HEADER_v2_SIZE], &ft, MSG_FOOTER_SIZE);

	return ns_send(conn, buffer, header.m_wPsize);
}