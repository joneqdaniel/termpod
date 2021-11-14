All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

POD3 files are simple container files housing other files like textures or models. File extension is _pod_.

## Used in

* [[BloodRayne 1]]
* [[BloodRayne 2]]

## Description


## Structure

```c
typedef struct pod_header_pod3_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE]; 
	pod_number_t file_count;
	pod_number_t audit_file_count;
	pod_number_t revision;
	pod_number_t priority;
	pod_char_t author[POD_HEADER_AUTHOR_SIZE];
	pod_char_t copyright[POD_HEADER_COPYRIGHT_SIZE];
	pod_number_t index_offset; /* 0x108 */
	pod_number_t pad10c;       /* 0x10c */
	pod_number_t size_index;   /* 0x110 */
	pod_signed_number_t flag0;  /* -1 / 0 */ /* 0x114 */
	pod_signed_number_t flag1;  /* -1 / 0 */ /* 0x118 */
	pod_signed_number_t pad11c; /* 0xFFFFFFFF 0xD4009345 0x64B5C42D 0xA1FE0F74 */
	pod_number_t pad120; /* 0x120 */
	pod_number_t pad124; /* 0x124 */
} pod_header_pod3_t;
```

```c
/* POD3 entry data structure */
typedef struct pod3_entry_s {
        pod_number_t path_offset;
        pod_number_t size;
        pod_number_t offset;
        pod_number_t timestamp;
        pod_number_t checksum;
} pod3_entry_t;
```