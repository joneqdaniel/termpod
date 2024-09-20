```cpp
namespace tr::epd
{
     struct header
     {
          c8<4>   ident;
          c8<256> comment;
          u32<1>  entry_count;
          u32<1>  version;
          u32<1>  checksum;
     };
     struct entry
     {
          c8<64>  name;
          u32<1>  size;
          u32<1>  offset;
          u32<1>  timestamp;
          u32<1>  checksum;
     };
};
```