```cpp
namespace tr::pod1
{
struct header
{
     u32<1> entry_count;
     c8<80> common;
};
struct entry
{
     c8<32> name;
     u32<1> size;
     u32<1> offset;
};
};
```