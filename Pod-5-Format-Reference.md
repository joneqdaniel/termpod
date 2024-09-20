```cpp
namespace tr::pod5
{
struct header : struct tr::pod3::header
{
        c8<80> next_archive;
};

struct entry
{
        u32<1> path_offset; /* (entry_offset + entry_count * sizeof(entry)) based */
        u32<1> compressed_size;
        u32<1> offset;
        u32<1> uncompressed_size;
        u32<1> compression_level;
        t32<1> timestamp;
        u32<1> checksum;
};
};
```