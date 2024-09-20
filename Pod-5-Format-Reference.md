```cpp
namespace tr::pod5
{
struct header : struct tr::pod3::header
{
        u32<1> next_archive;
};
using entry = tr::pod4::entry;
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