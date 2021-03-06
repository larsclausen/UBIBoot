
#ifndef UBI_H
#define UBI_H

#include <stdint.h>
#include <endian.h>
#include <byteswap.h>
#include <sys/queue.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define be32toh(x) bswap_32(x)
#else
#define be32toh(x) (x)
#endif

#define UBI_EC_HDR_MAGIC be32toh(0x55424923)
#define UBI_VID_HDR_MAGIC be32toh(0x55424921)

/* The maximum volume name length */
#define UBI_VOL_NAME_MAX 127

struct ubi_ec_hdr {
	uint32_t magic;
	uint8_t version;
	uint8_t padding[3];
	uint64_t ec;
	uint32_t vid_hdr_offset;
	uint32_t data_offset;
	uint32_t image_seq;
	uint8_t padding2[32];
	uint32_t hdr_crc;
} __attribute__ ((packed));

struct ubi_vid_hdr {
	uint32_t magic;
	uint8_t version;
	uint8_t vol_type;
	uint8_t copy_flag;
	uint8_t compat;
	uint32_t vol_id;
	uint32_t lnum;
	uint32_t leb_ver;
	uint32_t data_size;
	uint32_t used_ebs;
	uint32_t data_pad;
	uint32_t data_crc;
	uint8_t padding1[4];
	uint64_t sqnum;
	uint8_t padding2[12];
	uint32_t hdr_crc;
} __attribute__ ((packed));

struct ubi_vol_tbl_record {
	uint32_t reserved_pebs;
	uint32_t alignment;
	uint32_t data_pad;
	uint8_t vol_type;
	uint8_t padding1;
	uint16_t name_len;
	uint8_t name[UBI_VOL_NAME_MAX + 1];
	uint8_t padding2[24];
	uint32_t crc;
} __attribute__ ((packed));

struct EraseBlock {
	uint32_t data_addr;
	struct ubi_vid_hdr vid_hdr;
	SLIST_ENTRY(EraseBlock) next;
};

int load_kernel(uint32_t eb_start, uint32_t count, unsigned char *ld_addr);

#endif /* UBI_H */

