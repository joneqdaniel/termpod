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

```c
/* standard main variable type sizes common to all POD file formats      */
typedef uint32_t                             pod_number_t
typedef int8_t                               pod_char_t
typedef uint8_t                              pod_byte_t
typedef __time32_t                           pod_time_t
typedef pod_char_t*                          pod_string_t
/* constants common to all POD file formats                              */
#define POD_NUMBER_SIZE                      (sizeof(pod_number_t))
#define POD_CHAR_SIZE                        (sizeof(pod_char_t))
#define POD_BYTE_SIZE                        (sizeof(pod_byte_t))
#define POD_TIME_SIZE                        (sizeof(pod_time_t))
#define POD_COMMENT_SIZE                     (80)
#define EPD_COMMENT_SIZE                     (256)
#define POD_HEADER_CHECKSUM_DEFAULT          0x44424247
#define POD_ENTRY_CHECKSUM_DEFAULT           0x20444542
#define POD_ENTRY_TIMESTAMP_DEFAULT          0x42494720
#define POD_HEADER_UNKNOWN10C_DEFAULT        0x58585858
#define POD_IDENT_SIZE                       POD_NUMBER_SIZE

pod_string_t pod_ctime(pod_time_t* time32)
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

typedef enum pod_ident_type_e = {
    POD1 = 0, POD2, POD3, POD4, POD5, POD6, EPD,
    POD_IDENT_TYPE_SIZE,
} pod_ident_type_t;

/* map pod ident type enum id to file magic ident null terminated string */
char POD_IDENT[ POD_IDENT_TYPE_SIZE ][ POD_IDENT_SIZE + 1 ] = { 
    "\0POD1", "POD2\0", "POD3\0", 
    "POD4\0", "POD5\0", "POD6\0", "dtxe\0"
};

typedef enum pod_string_size_e = {
    POD_STRING_4=4, POD_STRING_8=8, POD_STRING_12=12,
    POD_STRING_16=16, POD_STRING_32=32, POD_STRING_48=48,
    POD_STRING_64=64, POD_STRING_80=80, POD_STRING_128=128,
    POD_STRING_256=256, POD_STRING_264=264, POD_STRING_SIZE=7,
} pod_string_size_t;

size_t pod_strlen_min(size_t len)
{
        return (len <= POD_STRING_4   ? POD_STRING_4   :
                len <= POD_STRING_8   ? POD_STRING_8   :
                len <= POD_STRING_12  ? POD_STRING_12  :
                len <= POD_STRING_16  ? POD_STRING_16  :
                len <= POD_STRING_32  ? POD_STRING_32  : 
                len <= POD_STRING_48  ? POD_STRING_48  :
                len <= POD_STRING_64  ? POD_STRING_64  :
                len <= POD_STRING_80  ? POD_STRING_80  :
                len <= POD_STRING_128 ? POD_STRING_128 :
                len <= POD_STRING_256 ? POD_STRING_256 :
                                        POD_STRING_264);
}

pod_filename_length_t filenames_len[header.file_count];

/* get the length of every filename string */
for (int i = 0; i < pod_header.file_count; i++)
        filename_len[i] = pod_strlen_min(strlen(filenames + entries[i].path_offset));

```
## Algorithms

**Checksums**

POD2 checksum algorihm is CRC-CCITT32 derived of:

- [sz - lrzsz](https://www.ohse.de/uwe/software/lrzsz.html)
- [makecrc - macutils](http://github.com/dgilman/macutils/)

and integrated updated into

- [Libcrc - Multi platform MIT licensed CRC library in C](http://github.com/jopadan/libcrc)

CRC-CCITT32 variant published and copyrighted since 1986 by:

- [Gary S. Brown]()
- [Mark G. Mendel](), 7/86
- [Stephen Satchell]()
- [Chuck Forsberg](https://en.wikipedia.org/wiki/Chuck_Forsberg)
- [Uwe Ohse](http://ohse.de/uwe/)
- [David Gilman](http://github.com/dgilman/)
- [Lammert Bies](http://github.com/lammertb/)

## Status

**Done**
[[POD2|Pod-2-Format-Reference]] format completely analyzed and structure documented in C pseudo code

[[POD6|Pod-6-Format-Reference]] format completely analyzed and structure documented in C pseudo code

**TODO**

[[POD3|Pod-3-Format-Referene]] decompile Bloodrayne Demo to retrieve CRC algorithm and unknown field names