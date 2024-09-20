```cpp
namespace pod2
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