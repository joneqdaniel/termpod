```cpp
namespace tr::pod5
{
struct header : struct tr::pod3::header
{
        u32<1> next_archive;
};
using entry = tr::pod4::entry;
};
```