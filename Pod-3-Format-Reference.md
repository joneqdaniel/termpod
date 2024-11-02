[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] POD3 [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]

```cpp
namespace tr::pod3
{

struct dependency : std::array<uint8_t, 264>
{
};

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
	u32<1> entry_offset;   /* zero based */
	u32<1> entries_crc;
	u32<1> names_size;   /* (entry_offset + entry_count * sizeof(struct entry)) based */
	i32<1> depends_count;
	i32<1> depends_crc;
	i32<1> audit_crc;
};

u32<1> names_offset = entry_offset + entry_count * sizeof(entry);
u32<1> audit_offset = names_size + names_offset + sizeof(struct dependency) * depends_count;

static constexpr u32<1> BLOCK_SIZE = 2048;

constexpr inline u32<1> ceil2mpow2(u32<1> x, u32<1> pow2)
{
    return (x + (pow2 - 1)) & -pow2;
}

struct extra_header : struct header
{
        i32<1> pad120;
};

constexpr inline unknown(u8<1>* buf, i32<1> off)
{
     struct extra_header* extra_header = reinterpret_cast<struct extra_header*>(buf);
     extra_header->pad11c = ceil2mpow2(off + extra_header->pad10c, BLOCK_SIZE) - extra_header->pad10c;
     extra_header->pad120 = extra_header->entry_offset - extra_header->pad11c > BLOCK_SIZE ? BLOCK_SIZE : extra_header->entry_offset - extra_header->pad11c;
}

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
## Official libraries/classes
1. [[BloodRayne]]: [[CPod]], [[CPodFile]], [[CDemonPod]]

## Unofficial utilities
1. [PodTools](https://gamebanana.com/tools/17801) is a powerful utility with support for a variety of Bloodrayne 1/2 formats. Unfortunately, this utility does not take care of checksums and timestamp. The header checksum gets the magic value `84 8E DE 4E` and other fields get `0`
2. [br2poded](https://www.ctpax-x.org/?goto=files&show=23) [[mirror]](https://www.playground.ru/bloodrayne_2/file/bloodrayne_2_pod_encoder_decoder_for_buka_localization-897514). According to [this](https://forum.zoneofgames.ru/topic/1178-bloodrayne-2/), the Buka localizer used its own game archives format, making changes to the executable file. Therefore, a special utility has been released for the Russian version of Bloodrayne 2.
3. **Abyss' POD Tools** somewhere on the web, it is possible to find localized versions of Bloodrayne 1, the archives of which will contain a comment starting with `[Abyss' POD Tools]`. However, no other evidence of its existence has been found