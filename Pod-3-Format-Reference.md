[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] POD3 [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]
* [[Related Software]]

```cpp
namespace tr::pod3
{

struct dependency : std::array<uint8_t, 264>
{
};

struct header
{
/* 0x0000 */ c8<4> ident;
/* 0x0004 */ u32<1> checksum;
/* 0x0008 */ c8<80> comment; 
/* 0x0058 */ u32<1> entry_count;
/* 0x005c */ u32<1> audit_count;
/* 0x0060 */ u32<1> revision;
/* 0x0064 */ u32<1> priority;
/* 0x0068 */ c8<80> author;
/* 0x00B8 */ c8<80> copyright;
/* 0x0108 */ u32<1> entry_offset;
/* 0x010c */ u32<1> entry_crc;
/* 0x0110 */ u32<1> names_size;
/* 0x0114 */ i32<1> depends_count;
/* 0x0118 */ i32<1> depends_crc;
/* 0x011c */ i32<1> audit_crc;
};

struct extra_header : struct header
{
/* 0x0120 */ i32<1> pad120;
};

u32<1> names_offset = entry_offset + entry_count * sizeof(struct entry);
u32<1> audit_offset = names_size + names_offset + sizeof(struct dependency) * depends_count;

static constexpr u32<1> BLOCK_SIZE = 2048;

constexpr inline u32<1> ceil2mpow2(u32<1> x, u32<1> pow2)
{
    return (x + (pow2 - 1)) & -pow2;
}

constexpr inline unknown(u8<1>* buf, i32<1> off)
{
     struct extra_header* extra_header = reinterpret_cast<struct extra_header*>(buf);
     extra_header->audit_crc = ceil2mpow2(off + extra_header->entries_crc, BLOCK_SIZE) - extra_header->entry_crc;
     extra_header->pad120 = extra_header->entry_offset - extra_header->audit_crc > BLOCK_SIZE ? BLOCK_SIZE : extra_header->entry_offset - extra_header->audit_crc;
}

struct entry
{
        u32<1> path_offset; /* names_offset based */
        u32<1> size;
        u32<1> offset;
        t32<1> timestamp;
        u32<1> checksum;
};
};
```
