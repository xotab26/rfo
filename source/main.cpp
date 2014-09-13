#include "Network/Network.h"
#include "Utilities/utils.h"

int main(int argc, char* argv[])
{
	WriteLine("RF Online Emulator - Version 0.1.0");
	
	Network loginServer = Network("Login", 10001);
	loginServer.Start();

	return 0;
}