[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]

```cpp
enum version
{
     NONE = 0,
     POD1 = 1,
     POD2 = 2,
     POD3 = 3,
     POD4 = 4,
     POD5 = 5,
     POD6 = 6,
     EPD  = 7,
     LAST = 8,
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
     {"EPD" , "dtxe\0"}
};

constexpr inline enum version id(const c8<4> magic)
{
     for(int i = POD2; i < last; i++)
             if(strncmp(ident[i].second, &magic[0], 4) == 0)
                     return (enum version)i;
     return POD1;
}
```
Other Tools
* [[Poddy]]