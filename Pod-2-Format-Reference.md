[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] POD2 [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]

```cpp
namespace tr::pod2
{
struct header
{
    c8<4>  ident; /* "POD2" */
    u32<1> checksum; /* covering data starting after header->checksum */
    c8<80> comment;
    u32<1> entry_count;
    u32<1> audit_count;
};
struct entry
{
    u32<1> path_offset; /* relative to end of file->entries */
    u32<1> size;
    u32<1> offset; /* relative to start of file */
    t32<1> timestamp;
    u32<1> checksum;
};
struct file
{
    struct header    header;
    struct entry     entries[header.entry_count];
    str              path_data;
    buf              entry_data;
    pod::type::audit audits[header.audit_count];
};
};
```
## Official utilities
1. **podview**. In 2000, [Terminal Reality](https://github.com/jopadan/termpod/wiki/Terminal-Reality) released a kit for creating custom mods for Nocturne, aka [Nocturne Editor](https://www.moddb.com/downloads/nocturne-editor). podview is part of this kit and is designed to serve [POD2](https://github.com/jopadan/termpod/wiki/Pod-2-Format-Reference), [POD1](https://github.com/jopadan/termpod/wiki/Pod-1-Format-Reference) and [EPD](https://github.com/jopadan/termpod/wiki/EPD-Format-Reference) archives. In addition, it supports the calculation of checksums and viewing the history of changes (i.e. auditing). It is quite possible that is a fundamental utility that has given independent developers a lot of valuable information about the game archives of this company.  