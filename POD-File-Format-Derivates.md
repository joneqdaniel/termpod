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
/* main variable type sizes of POD file formats                                                            */
/* integer types */
typedef uint64_t                             pod_number64_t;
typedef int64_t                              pod_signed_number64_t;
typedef uint32_t                             pod_number32_t;
typedef int32_t                              pod_signed_number32_t;
typedef uint16_t                             pod_number16_t;
typedef pod_number32_t                       pod_number_t;
typedef pod_signed_number32_t                pod_signed_number_t;
typedef uint8_t                              pod_byte_t;
typedef uint16_t                             pod_word_t;
typedef uint32_t                             pod_double_word_t;
typedef uint64_t                             pod_quad_word_t;
/* floating and fixed point types */
typedef float                                pod_float32_t;
typedef double                               pod_float64_t;
typedef uint16_t                             pod_fixed16_t;
typedef uint32_t                             pod_fixed32_t;
/* boolean types */
typedef bool                                 pod_bool_t;
/* size and file offset types */
typedef size_t                               pod_size_t;
typedef ssize_t                              pod_ssize_t;
typedef fpos_t                               pod_fpos_t;
typedef off_t                                pod_off_t;
/* character and string types */
typedef int8_t                               pod_char_t;
typedef wchar_t                              pod_wchar_t;
typedef pod_char_t*                          pod_string_t;
typedef wchar_t*                             pod_wchar_string_t;
/* time types */
typedef int32_t                              pod_time32_t;
typedef int64_t                              pod_time64_t;
typedef pod_time32_t                         pod_time_t;
/* file handle types */
typedef pod_char_t*                          pod_path_t;
typedef DIR*                                 pod_dir_t;
typedef FILE*                                pod_file_t;

#define POD_NUMBER_SIZE                      sizeof(pod_number_t)          /* length of a numerical entry    */
#define POD_BYTE_SIZE                        sizeof(pod_byte_t)            /* length of a byte entry         */
#define POD_CHAR_SIZE                        sizeof(pod_char_t)            /* length of a character entry    */
#define POD_STRING_SIZE                      sizeof(pod_string_t)          /* length string char* entry      */
#define POD_TIME_SIZE                        sizeof(pod_time_t)            /* length of a time entry         */
#define POD_HEADER_CHECKSUM_DEFAULT          0x44424247                    /* default checksum of POD file   */
#define POD_ENTRY_CHECKSUM_DEFAULT           0x20444542                    /* default checksum of POD entry  */
#define POD_ENTRY_TIMESTAMP_DEFAULT          0x42494720                    /* default timestamp of POD entry */
#define POD_HEADER_UNKNOWN10C_DEFAULT        0x58585858			   /* default value of unknown10c    */
#define POD_HEADER_UNKNOWN11C_DEFAULT        0x58585858                    /* default value of unknown11c    */
#define POD_HEADER_FLAG0_DEFAULT             0x00000000                    /* default flag0 equals 0         */
#define POD_HEADER_FLAG1_DEFAULT             0xFFFFFFFF                    /* default flag1 equals -1        */
#define POD_CHECKSUM_DEFAULT                 0xFFFFFFFF                    /* default seed for CCIT32-CRC    */
#define POD_PATH_SEPARATOR                   '\\'                          /* default path separator         */
#define POD_PATH_NULL                        '\0'
#define POD_SYSTEM_PATH_SIZE                 1024                          /* default system path length     */
#define POD_UMASK                            0755                          /* default UMASK privileges       */
extern char *rotorchar;
pod_string_t pod_ctime(pod_time_t* time32);

enum pod_string_size_t
{
	POD_STRING_4=4, POD_STRING_32=32, POD_STRING_48=48, POD_STRING_64=64, POD_STRING_80=80,
	POD_STRING_96=96, POD_STRING_128=128, POD_STRING_256=256, POD_STRING_264=264,
	POD_STRING_SIZE_SIZE=9,
};
typedef enum pod_string_size_t pod_string_size_t;

#define POD_COMMENT_SIZE                     POD_STRING_80                 /* comment length of POD format   */
#define EPD_COMMENT_SIZE                     POD_STRING_256                /* comment length of EPD format   */

enum pod_ident_type_t
{
	POD1 = 0, POD2, POD3, 
	POD4, POD5, POD6, 
	EPD, POD_IDENT_TYPE_SIZE, 
};
typedef enum pod_ident_type_t pod_ident_type_t;

#define POD_IDENT_SIZE                       POD_STRING_4             /* file magic ident length        */
#define POD_IDENT_TYPE_SIZE                  (EPD + 1)                /* number of POD format types     */

/* pod_header_t element sizes */
#define POD_HEADER_NUMBER_SIZE               POD_NUMBER_SIZE
#define POD_HEADER_COMMENT_SIZE              POD_COMMENT_SIZE
#define POD_HEADER_EPD_COMMENT_SIZE          EPD_COMMENT_SIZE
#define POD_HEADER_IDENT_SIZE                POD_IDENT_SIZE
#define POD_HEADER_NEXT_ARCHIVE_SIZE         POD_STRING_96
#define POD_HEADER_AUTHOR_SIZE               POD_HEADER_COMMENT_SIZE
#define POD_HEADER_COPYRIGHT_SIZE            POD_HEADER_COMMENT_SIZE
#define POD_HEADER_CHECKSUM_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_FILE_COUNT_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_AUDIT_FILE_COUNT_SIZE     POD_HEADER_NUMBER_SIZE
#define POD_HEADER_REVISION_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_VERSION_SIZE              POD_HEADER_NUMBER_SIZE
#define POD_HEADER_PRIORITY_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_INDEX_OFFSET_SIZE         POD_HEADER_NUMBER_SIZE
#define POD_HEADER_SIZE_INDEX_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_NAME_COUNT_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN10C_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_FLAG0_SIZE                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_FLAG1_SIZE                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN11C_SIZE           POD_HEADER_NUMBER_SIZE

#define POD_DIR_ENTRY_FILENAME_SIZE          POD_STRING_256
#define POD_DIR_ENTRY_NUMBER_SIZE            POD_NUMBER_SIZE
#define POD_DIR_ENTRY_SIZE_SIZE              POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_OFFSET_SIZE            POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_PATH_OFFSET_SIZE       POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_UNCOMPRESSED_SIZE      POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_TIMESTAMP_SIZE         POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_CHECKSUM_SIZE          POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_ZERO_SIZE              POD_DIR_ENTRY_NUMBER_SIZE

/* audit entry sizes for POD2 */
#define POD_AUDIT_ENTRY_USER_SIZE            POD_STRING_32
#define POD_AUDIT_ENTRY_TIMESTAMP_SIZE       POD_TIME_SIZE
#define POD_AUDIT_ENTRY_ACTION_SIZE          POD_NUMBER_SIZE
#define POD_AUDIT_ENTRY_PATH_SIZE            POD_STRING_256
#define POD_AUDIT_ENTRY_DATA_SIZE            POD_BYTE_SIZE * 16

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

## Status

**TODO**

* [[POD3|Pod-3-Format-Reference]] format needs decompile [[BloodRayne 2|BloodRayne-2]] demo to retrieve CRC algorithm and unknown field names

**Done**

* [[POD2|Pod-2-Format-Reference]] format completely analyzed and structure documented in C pseudo code

* [[POD6|Pod-6-Format-Reference]] format completely analyzed and structure documented in C pseudo code

