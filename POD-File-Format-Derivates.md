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

enum section
{
     none   = 0,
     file   = 1,
     header = 2,
     extra  = 3,
     entry  = 4,
     audit  = 5,
};
template<enum version version>
constexpr inline size_t section_size(size_t size)
{
       switch(range[version].second)
       {
                        case section::entry:
                        case section::file:
                                return size;
                        case section::header:
                                return sizeof(tr::pod::type<version>::header);
                        default:
                                return 0;
                }
        }
        template<enum version version>
        constexpr inline size_t section_offset()
        {
                switch(range[version].second)
                {
                        case section::header:
                        case section::file:
                                return range[version].first;
                        case section::entry:
                        default:
                                return 0;
                }
        }

```