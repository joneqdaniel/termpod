[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* Checksum Algorithm
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]

Checksum algorithm in use for [[EPD|EPD-Format-Reference]]/[[POD2|Pod 2 Format Reference]] and up is [CRC-32/MPEG-2](https://crccalc.com/?crc=123456789&method=CRC-32/MPEG-2&datatype=0&outtype=0) available in [crcle](https://github.com/jopadan/crcle)
```sh
poly    : 0x04C11DB7
ref_in  : false
ref_out : false
xor_in  : 0xFFFFFFFF
xor_out : 0
```
Checksum ranges
```c
/*    checksum */
POD2 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(file  )-offset
POD3 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset=280
POD4 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset
POD5 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset
EPD  : offset=sizeof(header)                 count=sizeof(file  )-offset
/* no checksum */
POD6 : offset=sizeof(header)                 count=sizeof(file  )-offset
POD1 : offset=sizeof(header)=4+80            count=sizeof(file  )-offset
```