[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]

```cpp
enum version
{
     none = 0,
     pod1 = 1,
     pod2 = 2,
     pod3 = 3,
     pod4 = 4,
     pod5 = 5,
     pod6 = 6,
     epd_dxte = 7,
     epd_tsal = 8,
     last = 9,
};

const std::pair<const char*, const char*> ident[last] =
{
     {"NONE", "\0NONE"},
     {"POD1", "\0POD1"},
     {"POD2", "POD2\0"},
     {"POD3", "POD3\0"},
     {"POD4", "POD4\0"},
     {"POD5", "POD5\0"},
     {"POD6", "POD6\0"},
     {"EPD/dxte" , "dtxe\0"},
     {"EPD/tsal" , "tsal\0"}
};

constexpr inline enum version id(const c8<4> magic)
{
     for(int i = pod2; i < last; i++)
             if(strncmp(ident[i].second, &magic[0], 4) == 0)
                     return (enum version)i;
     return pod1;
}
```