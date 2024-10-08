[[EPD|Epd Format Reference]] POD1 [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]

```cpp
namespace tr::pod1
{
struct header
{
     u32<1> entry_count;
     c8<80> comment;
};
struct entry
{
     c8<32> name;
     u32<1> size;
     u32<1> offset;
};
};
```

- [hxtools - smm/extract_f3pod](https://codeberg.org/jengelh/hxtools)