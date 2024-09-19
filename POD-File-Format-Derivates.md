*All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

* [[Checksum Algorithm]]
* [[Compression Algorithm]]

Sring manipulation

```cpp
namespace tr
{
using u64 = uint64_t;
using i64 = int64_t;
using s64 = signed int64_t;
using u32 = uint32_t;
using i32 = int32_t;
using c8  = char;
using u8  = uint8_t;
using i8  = int8_t;
using t32 = i32;
using t64 = i64;

namespace pod
{
namespace string
{
u32 ceil(u32 len)
{
        static const std::array<u32,12> sizes = { 4, 8, 12, 16, 32, 48, 64, 80, 96, 128, 256, 264 };
        std::array<u32,12>::const_iterator dst = sizes.begin();
        while(size > *dst) dst++;
        return *dst;
}

c8* fgets(u32 size, FILE* stream)
{
   if(size == 0)
       return nullptr;
   
   c8* dst = (c8*)calloc(ceil(size), 1);

   for(u32 i = 0; i < size; i++)
   {
       dst[i] = fgetc(stream);
       if(dst[i] == EOF)
          dst[i] = '\0';
       if(dst[i] == '\0')
          break;
   }
   if(strlen(dst) == 0)
   {
       free(dst);
       dst = nullptr;
   }
   return dst;
}

c8* ctime(const t32* time) 
{ 
        time_t t = (time_t)*time; 
        c8* dst = std::ctime(&t); 
        dst[strcspn(dst, "\n")] = '\0';
        return dst; 
}
};
namespace audit
{
enum action : u32
{
	add = 0,
	rem = 1,
	chg = 2,
};
struct entry
{
	c8  user[32];
	u32 timestamp;
	enum action action;
	c8  path[256];
	i32 old_timestamp;
	u32 old_size;
	i32 new_timestamp;
	u32 new_size;
};
};
};
};
```