*All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

POD files are simple container files housing other files like textures or models. File extension is _pod_.

There are various versions of the POD files. There are not compatible with each other. Each version can be identified by the first 4 bytes of the file.

  * file starts with *POD6* see [[POD6|Pod-6-Format-Reference]]
  * file starts with *POD5* see [[POD5|Pod-5-Format-Reference]]
  * file starts with *POD4* see [[POD4|Pod-4-Format-Reference]]
  * file starts with *POD3* see [[POD3|Pod-3-Format-Reference]]
  * file starts with *POD2* see [[POD2|Pod-2-Format-Reference]]
  * file starts with *dxte* see [[EPD|Epd-Format-Reference]]
  * else see [[POD1|Pod-1-Format-Reference]]

```cpp
namespace pod
{
char ctime(int32_t* time32)
{
	struct tm tm;
	errno_t ret = _localtime32_s(&tm, time32);
	if(ret != 0)
	{
		fprintf(stderr, "%s\n", strerror(ret));
		return 0;
	}
	__time64_t time64 = _mktime64(&tm);
        pod_string_t str = _ctime64(&time64);
        str[strcspn ( str, "\n" )] = '\0';
	return str;
}
};
```