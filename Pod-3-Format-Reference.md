[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] POD3 [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]

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
## Official Libraries/Classes
1. [[BloodRayne]]: [[CPod]], [[CPodFile]], [[CDemonPod]]

## Unofficial utilities
1. [PodTools](https://gamebanana.com/tools/17801) is a powerful utility with support for a variety of Bloodrayne 1/2 formats. Unfortunately, this utility does not take care of checksums and timestamp. The header checksum gets the magic value `84 8E DE 4E` and other fields get `0`
2. [br2poded](https://www.ctpax-x.org/?goto=files&show=23) [[mirror]](https://www.playground.ru/bloodrayne_2/file/bloodrayne_2_pod_encoder_decoder_for_buka_localization-897514). According to [this](https://forum.zoneofgames.ru/topic/1178-bloodrayne-2/), the Buka localizer used its own game archives format, making changes to the executable file. Therefore, a special utility has been released for the Russian version of Bloodrayne 2.
3. **Abyss' POD Tools** somewhere on the web, it is possible to find localized versions of Bloodrayne 1, the archives of which will contain a comment starting with `[Abyss' POD Tools]`. However, no other evidence of its existence has been found