*All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

CRC-32/MPEG-2 checksum variant

```cpp
poly    : 0x04C11DB7
ref_in  : false
ref_out : false
xor_in  : 0xFFFFFFFF
xor_out : 0

POD2 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(file  )-offset
POD3 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset=280
POD4 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset
POD5 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset
EPD  : offset=sizeof(header)                 count=sizeof(file  )-offset
POD6 : offset=sizeof(header)                 count=sizeof(file  )-offset
POD1 : offset=sizeof(header)=4+80            count=sizeof(file  )-offset
```
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