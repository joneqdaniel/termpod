All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

POD3 files are simple container files housing other files like textures or models. File extension is _pod_.

## Used in

* [[BloodRayne 1]]
* [[BloodRayne 2]]

## Description

 * Header only checksum covers section after checksum until end of header.
 * Audit trail
 * Reverse engineer to get missing fields and variants of file format or get the CPOD C++ library source code.

## Structure

```cpp
namespace tr::pod3
{
struct header
{
	c8<4> ident;    /* "POD3" */
	u32<1> checksum; /* CRC-32/MPEG-2 header checksum of bytes 8 to 288 of size 280 */
	c8<80> comment; 
	u32<1> entry_count;
	u32<1> audit_count;
	u32<1> revision;
	u32<1> priority;
	c8<80> author;
	c8<80> copyright;
	u32<1> entry_offset; /* zero based */
	u32<1> pad10c;
	u32<1> audit_offset; /* (entry_offset + entry_count * sizeof(entry)) based */
	i32<1> flag0;  /* -1 / 0 probably CRC-32 xor_in */
	i32<1> flag1;  /* -1 / 0 probably CRC-32 xor_out */
	i32<1> pad11c; /* 0xFFFFFFFF 0xD4009345 0x64B5C42D 0xA1FE0F74 */
};

struct entry
{
        u32<1> path_offset; /* (entry_offset + entry_count * sizeof(entry)) based */
        u32<1> size;
        u32<1> offset;
        t32<1> timestamp;
        u32<1> checksum;
};
};
```