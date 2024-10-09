[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* [[Version History]]

```cpp
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
```

```cpp
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