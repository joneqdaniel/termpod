[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* Audit Trail
* [[String Helpers]]
* [[Version History]]
* [[Related Software]]

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