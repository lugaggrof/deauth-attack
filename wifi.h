#pragma once

#include<cstdint>
#include"mac.h"

#pragma pack(push, 1)
struct RadioTapHeader {
        uint8_t it_version;     /* set to 0 */
        uint8_t it_pad;
        uint16_t it_len;         /* entire length */
        uint32_t it_present;     /* fields present */
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MacHeader {
	uint8_t type;
	uint8_t flag;
	uint16_t duration_id;
  Mac dest_addr;
	Mac src_addr;
  Mac bss_id;
  uint16_t seq_ctl;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MandatoryBody {
  uint16_t reason_code;  
};
#pragma pack(pop)

