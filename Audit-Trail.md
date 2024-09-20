```cpp
namespace tr::pod::audit
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
```