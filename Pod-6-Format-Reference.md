[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] POD6 [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]
* [[Related Software]]

```cpp
namespace tr::pod6
{
struct header
{
        c8<4> ident;
        u32<1> entry_count;
        u32<1> version;
        u32<1> entry_offset;
        u32<1> names_count;
};
struct entry
{
        u32<1> names_offset;
        u32<1> size;
        u32<1> offset;
        u32<1> uncompressed;
        u32<1> compression_level; /* bitmask flag field defaulting to 8 */
        u32<1> zero;
};
struct file
{
     struct header header;
     void*         contents;
     struct entry  entries[header.entry_count];
     c8<1>         paths[header.names_count]; /* end of entries + entries[i].names_offset */
};
};
```

