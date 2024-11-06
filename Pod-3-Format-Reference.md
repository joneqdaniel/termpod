[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] POD3 [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Dependency Records]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]
* [[Related Software]]

**TODO**
```cpp
struct extra_header : struct header
{
/* 0x0120 */ u32<1> pad120;
};

static constexpr u32<1> BLOCK_SIZE = 2048;

constexpr inline unknown(u8<1>* buf, i32<1> off)
{
     struct extra_header* extra_header = reinterpret_cast<struct extra_header*>(buf);
     extra_header->audit_crc = ceil2mpow2(off + extra_header->entries_crc, BLOCK_SIZE) - extra_header->entry_crc;
     extra_header->pad120 = extra_header->entry_offset - extra_header->audit_crc > BLOCK_SIZE ? BLOCK_SIZE : extra_header->entry_offset - extra_header->audit_crc;
}
```
**DONE**
```cpp
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
/* 0x0114 */ u32<1> depends_count;
/* 0x0118 */ u32<1> depends_crc;
/* 0x011c */ u32<1> audits_crc;
constexpr inline uint32_t checksum_offset(          )  { return sizeof(checksum) + sizeof(ident); }
constexpr inline uint32_t  entries_offset(          )  { return entry_offset; }
constexpr inline uint32_t    names_offset(          )  { return entry_offset + entry_count * sizeof(struct entry); }
constexpr inline uint32_t  depends_offset(          )  { return names_size + names_offset(); }
constexpr inline uint32_t   audits_offset(          )  { return depends_offset() + depends_count * sizeof(struct depend::entry); }
constexpr inline  bool checksum_verify(uint8_t* buf)   { return    checksum == crc32::mpeg2::compute(&buf[checksum_offset()], sizeof(struct header) - sizeof(checksum) - sizeof(ident)); } 
constexpr inline  bool  entries_verify(uint8_t* buf)   { return   entry_crc == crc32::mpeg2::compute(&buf[ entries_offset()],   entry_count * sizeof(struct entry)); }
constexpr inline  bool  depends_verify(uint8_t* buf)   { return depends_crc == crc32::mpeg2::compute(&buf[ depends_offset()], depends_count * sizeof(struct depend::entry)); }
constexpr inline  bool   audits_verify(uint8_t* buf)   { return  audits_crc == crc32::mpeg2::compute(&buf[  audits_offset()],   audit_count * sizeof(struct  audit::entry)); }
constexpr inline struct entry* entry   entries_begin() { return reinterpret_cast<struct entry*>(&data[entries_offset()]); }
constexpr inline struct depend::entry* depends_begin() { return reinterpret_cast<struct depend::entry*>(&data[depends_offset()]); }
constexpr inline struct audit::entry*   audits_begin() { return reinterpret_cast<struct audit::entry*>(&data[audit_offset()]); }
};

struct entry
{
        u32<1> path_offset; /* names_offset based */
        u32<1> size;
        u32<1> offset;
        t32<1> timestamp;
        u32<1> checksum;
};
```
