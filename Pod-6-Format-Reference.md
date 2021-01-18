*All information here is to my best knowledge, is is not proven by any official reference manual by Microsoft or [[Terminal Reality]].*

POD6 files are simple container files housing other files like textures or models. File extension is _pod_.

## Used in

 * [[Ghostbusters: The Video Game Remastered]]

## Description

The file starts with a *header block* of 20 bytes size.

```c
/* 20 bytes */
#define POD_HEADER_POD6_SIZE (POD_HEADER_IDENT_SIZE + \ 
                              POD_HEADER_FILE_COUNT_SIZE + \ 
                              POD_HEADER_VERSION_SIZE + \ 
                              POD_HEADER_INDEX_OFFSET_SIZE + \ 
                              POD_HEADER_SIZE_INDEX_SIZE)
```

```c
/* POD6 header data structure */
typedef struct pod_header_pod6_s {
        pod_char_t ident[POD_HEADER_IDENT_SIZE];
        pod_number_t file_count;
        pod_number_t version;
        pod_number_t index_offset;
        pod_number_t size_index;
} pod_header_pod6_t;
```
The POD 6 directory entry is a block of 24 bytes structured into
6 `pod_number_t` referencing the data and its name.

```c
/* 24 bytes */ 
#define POD_ENTRY_POD6_SIZE (POD_ENTRY_PATH_OFFSET_SIZE + \ 
                             POD_ENTRY_SIZE_SIZE + \ 
                             POD_ENTRY_OFFSET_SIZE + \ 
                             POD_ENTRY_UNCOMPRESSED_SIZE + \ 
                             POD_ENTRY_COMPRESSION_LEVEL_SIZE + \ 
                             POD_ENTRY_ZERO_SIZE) 
```
```c
/* POD6 entry data structure */
typedef struct pod_entry_pod6_s {
        pod_number_t path_offset;
        pod_number_t size;
        pod_number_t offset;
        pod_number_t uncompressed;
        pod_number_t compression_level;
        pod_number_t zero;
} pod_entry_pod6_t;


```

`compression_level` bitmask flag field defaulting to 8 indicates the
compression used.

```c
fseek(file, header.index_offset + (index * POD_ENTRY_POD6_SIZE), SEEK_SET);
fread(&entries[index], POD_NUMBER_SIZE, POD_ENTRY_POD6_SIZE/POD_NUMER_SIZE, file); 
fseek(file, header.index_offset + (header.file_count * POD_ENTRY_POD6_SIZE) + entry.path_offset, SEEK_SET);
fread(filenames, POD_CHAR_SIZE, header.size_index, file);
```
## Structure

The POD 6 file structure is as follows:

```c
typedef struct pod_file_pod6_s {
     pod6_header_t header;
     void*         contents;
     /* header.index_offset */
     pod_entry_pod6_t  entries[header.file_count];
     /* 
        header.index_offset 
        + (header.file_count * sizeof(pod_entry_pod6_t)
        + entries[0].path_offset
     */
     pod_char_t    filenames[header.size_index];      
} pod_file_pod6_t;

/* total file size calculation */
size_t file_size = header.index_offset 
                   + header.file_count * sizeof(pod_header_pod6_t) 
                   + header.size_index;
```
`contents` contains `header.index_offset - sizeof(header)` bytes of data
referenced by `entry.offset`.

`filenames` is an envelope-structured array of null-termination supremum
 padded strings at the size of SIMD and IEEE754 double extended
 floating-point register length.