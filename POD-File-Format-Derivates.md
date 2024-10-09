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
     epd  = 7,
     last = 8,
};

enum section
{
     none   = 0,
     file   = 1,
     header = 2,
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

const std::pair<u32<1>, enum section> checksum[last] =
{
     { 0u                                                                      , section::none   },
     { sizeof(tr::pod<1>::header)                                              , section::file   },
     { sizeof(tr::pod<2>::header::ident) + sizeof(tr::pod<2>::header::checksum), section::file   },
     { sizeof(tr::pod<3>::header::ident) + sizeof(tr::pod<3>::header::checksum), section::header },
     { sizeof(tr::pod<4>::header::ident) + sizeof(tr::pod<4>::header::checksum), section::header },
     { sizeof(tr::pod<5>::header::ident) + sizeof(tr::pod<5>::header::checksum), section::header },
     { sizeof(tr::pod<6>::header)                                              , section::file   },
     { sizeof(tr::epd::header)                                                 , section::file   },
};
```