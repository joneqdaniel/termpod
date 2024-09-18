*All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

CRC-32/MPEG-2 checksum variant

```sh
poly    : 0x04C11DB7
ref_in  : false
ref_out : false
xor_in  : 0xFFFFFFFF
xor_out : 0
```
```c
POD2 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(file  )-offset
POD3 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset=280
POD4 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset
POD5 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset
EPD  : offset=sizeof(header)                 count=sizeof(file  )-offset
POD6 : offset=sizeof(header)                 count=sizeof(file  )-offset
POD1 : offset=sizeof(header)=4+80            count=sizeof(file  )-offset
```
Sring manipulation
```cpp
namespace pod::string
{
str fgets(u32<1> size, FILE* stream)
{
    if(size == 0)
        return nullptr;

    str dst = (str)calloc(size, 1);

    for(u32<1> i = 0; i < size; i++)
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
    else
    {
        dst = (str)realloc(dst, strlen(dst) + 1);
    }
    return dst;
 }

u32<1> ceil(u32<1> size)
{
    static const u32<1> sizes[12] = { 4, 8, 12, 16, 32, 48, 64, 80, 96, 128, 256, 264 };
    u32<1> dst;
    for(dst = 0; dst < size; dst++);
    return dst;
}

void replace_separator(char* src, const char* sep_old, const char* sep_new)
{
    const size_t len = strlen(src);
    for(u32<1> i = 0; i < len; i++)
       if(src[i] == *sep_old)
          src[i] = *sep_new;
}

char* ctime(int32_t* time32)
{
	struct tm tm;
	errno_t ret = _localtime32_s(&tm, time32);
	if(ret != 0)
	{
		fprintf(stderr, "%s\n", strerror(ret));
		return 0;
	}
	__time64_t time64 = _mktime64(&tm);
        char* str = _ctime64(&time64);
        str[strcspn ( str, "\n" )] = '\0';
	return str;
}
};
```