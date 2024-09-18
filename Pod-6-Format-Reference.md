*All information here is to my best knowledge, is is not proven by any official reference manual by Microsoft or [[Terminal Reality]].*

## Used in

 * [[Ghostbusters: The Video Game Remastered]]

## Description

```cpp
namespace pod6
{
struct header
{
        c8<4> ident;
        u32<1> entry_count;
        u32<1> version;
        u32<1> entry_offset;
        u32<1> path_count;
};
struct entry
{
        u32<1> path_offset;
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
     c8<1>         paths[header.path_count]; /* end of entries + entries[i].path_offset */
};
};
```

