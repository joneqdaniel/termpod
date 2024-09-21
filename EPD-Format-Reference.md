EPD [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]

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