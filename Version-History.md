[[EPD|Epd Format Reference]] [[POD1|Pod 1 Format Reference]] [[POD2|Pod 2 Format Reference]] [[POD3|Pod 3 Format Reference]] [[POD4|Pod 4 Format Reference]] [[POD5|Pod 5 Format Reference]] [[POD6|Pod 6 Format Reference]] [[Terminal Reality]] [[Home]]

* [[Checksum Algorithm]]
* [[Compression Algorithm]]
* [[Audit Trail]]
* [[String Helpers]]
* Version History
* [[Related Software]]

#### POD1 style
| format | changes |
|--------|-----------|
| POD1   |           |
| EPD    | magic ident, checksum and timestamp |
| POD2   | path name string table and audit logs |
| POD6   | compression instead of checksum |

#### POD3 style
| format   | changes |
|--------|-----------|
| POD3   | EPD/POD2 changes + dependencies |
| POD4   | compression |
| POD5   | linked archive list |

#### Related Resources
* [POD Files](http://mtm2.com/~mtmg/misc/fileformats/pod.html)
* [Unofficial POD File Format v1.1](http://www.viaregio.de/pieper/mtm/pod_file_format.shtml)