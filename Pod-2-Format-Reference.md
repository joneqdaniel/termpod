All information here is to my best knowledge, is is not proven by any official reference manual by [[Terminal Reality]].*

POD2 files are simple container files housing other files like textures or models. File extension is _pod_.

## Used in

* [[4x4 Evo 1]]
* [[4x4 Evo 2]]
* [[Blair Witch Volume 1: Rustin Parr|Blair Witch 1]]
* [[Nocturne]]

## Description

Checksum algorithm used in POD2 files is CRC-CCITT32 with initial crc value of 0xFFFFFFFF

- [Libcrc - Multi platform MIT licensed CRC library in C](http://github.com/jopadan/libcrc)
- [macutils - makecrc](http://github.com/jopadan/macutils)
- [QuickBMS CRC](https://aluigi.altervista.org/bms/quickbms_crc_engine.txt) requires setting crc type to 2.

```c
#include <checksum.h>

pod_char_t* input_str = pod_file_start + 8;
pod_size_t nbytes = pod_file_size - 8;

pod_number_t crc = crc_ccitt32_ffffffff(input_str, nbytes);

```

## Structure

```c
/* 96 bytes */
typedef struct pod_header_pod2_s {
    pod_char_t   ident[POD_IDENT_SIZE]; /* always POD2 */
    pod_number_t checksum; /* covering data starting after header->checksum */
    pod_char_t   comment[POD_COMMENT_SIZE];
    pod_number_t file_count;
    pod_number_t audit_file_count;
} pod_header_pod2_t;
```

```c
typedef struct pod_entry_pod2_s {
    pod_number_t path_offset; /* relative to end of file->entries */
    pod_number_t size;
    pod_number_t offset; /* relative to start of file */
    pod_number_t timestamp;
    pod_number_t checksum;
} pod_entry_pod2_t;
```
```c
enum pod_audit_entry_pod2_action = { 
    POD2_AUDIT_ACTION_ADD    = 0, /*   0 / new */
    POD2_AUDIT_ACTION_REMOVE = 1, /* old /   0 */
    POD2_AUDIT_ACTION_CHANGE = 2, /* old / new */
    POD2_AUDIT_ACTION_SIZE   = 3,
};

typedef struct pod_audit_entry_pod2_s {
   pod_char_t   user[POD_STRING_32];
   pod_time_t   timestamp;
   pod_number_t action;
   pod_char_t   path[POD_STRING_256];
   pod_time_t   old_timestamp;
   pod_number_t old_size;
   pod_time_t   new_timestamp;
   pod_number_t new_size;
} pod_audit_entry_pod2_t;
```

```c
typedef struct pod_file_pod2_s {
    pod_header_pod2_t header;
    pod_entry_pod2_t entries[header.file_count];
    pod_char_t* path_data;
    pod_byte_t* entry_data;
    pod_audit_entry_pod2_t audit_trail[header.audit_file_count];
} pod_file_pod2_t;
```