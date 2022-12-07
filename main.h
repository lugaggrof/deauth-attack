#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "libnet.h"

#include <pcap.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "wifi.h"

#pragma pack(push, 1)
struct WiFiHeader{
	RadioTapHeader radioTapHeader;
	MacHeader macHeader;
	MandatoryBody mandatoryBody;
};
#pragma pack(pop)

