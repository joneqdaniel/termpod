[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] POD4 [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Dependency Records]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]
* [[Related Software]]

```cpp
using header = struct pod3::header;
using extra_header = struct pod3::extra_header;

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
```