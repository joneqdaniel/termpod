[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] POD5 [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]
* [[Related Software]]

```cpp
namespace tr::pod5
{
struct header : struct tr::pod3::header
{
/* 0x0120 */ u32<1> next_archive;
};

struct extra_header : struct header
{
/* 0x0124 */ u32<1> pad124;
}

using entry = tr::pod4::entry;
};
```