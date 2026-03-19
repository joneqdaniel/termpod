#pragma once
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <utility>
#include <array>
#include <vector>
#include <sys/stat.h>
#include <utime.h>
#include <getopt.h>
#include <crcle/crcle.hpp>

namespace tr
{
	using u8  =       uint8_t;
	using i8  =        int8_t;
	using s8  =        int8_t;
	using c8  =          char;
	using b8  =          bool;
	using uc8 = unsigned char;

	using u16  =     uint16_t;
	using i16  =      int16_t;
	using s16  =      int16_t;
	using u32  =     uint32_t;
	using i32  =      int32_t;
	using t32  =          i32;
	using s32  =      int32_t;
	using u64  =     uint64_t;
	using i64  =      int64_t;
	using s64  =      int64_t;

	using f32  =        float;
	using f64  =       double;
};

namespace tr::pod
{
	bool extract = false;
	/* pod version */
	enum version
	{
		none = 0,
		pod1 = 1,
		pod2 = 2,
		pod3 = 3,
		pod4 = 4,
		pod5 = 5,
		pod6 = 6,
		epd  = 7,
		last = 8,
		count
	};

	static constexpr const std::pair<const char*, const char*> ident[count] =
	{
		{"NONE", "\0NONE"},
		{"POD1", "\0POD1"},
		{"POD2", "POD2\0"},
		{"POD3", "POD3\0"},
		{"POD4", "POD4\0"},
		{"POD5", "POD5\0"},
		{"POD6", "POD6\0"},
		{"EPD",  "dtxe\0"},
		{"LAST", "tsal\0"},
	};

	static constexpr inline enum version id(const char magic[4])
	{
		for(int i = pod2; i < last; i++)
			if(strncmp(ident[i].second, &magic[0], 4) == 0)
				return (enum version)i;
		return pod1;
	}
	/* string manipulation */
	namespace string
	{
		uint32_t ceil(uint32_t size)
		{
			static const std::array<uint32_t,12>  sizes = { 4, 8, 12, 16, 32, 48, 64, 80, 96, 128, 256, 264 };
			std::array<uint32_t,12>::const_iterator dst = sizes.begin();
			while(size > *dst) dst++;
			return *dst;
		}
		char* gets(char* buf)
		{
			uint32_t size = strnlen(buf, 264);
			if(size == 0)
				return nullptr;

			char* dst = (char*)calloc(ceil(size), 1);

			for(uint32_t i = 0; i < size; i++)
			{
				dst[i] = buf[i];
				if(dst[i] == EOF)
					dst[i] = '\0';
				if(dst[i] == '\0')
					break;
				if(dst[i] == '\\')
					dst[i] = '/';
			}
			if(strlen(dst) == 0)
			{
				free(dst);
				dst = nullptr;
			}
			return dst;
		}
		char* fgets(uint32_t size, FILE* stream)
		{
			if(size == 0)
				return nullptr;

			char* dst = (char*)calloc(ceil(size), 1);

			for(uint32_t i = 0; i < size; i++)
			{
				dst[i] = fgetc(stream);
				if(dst[i] == EOF)
					dst[i] = '\0';
				if(dst[i] == '\0')
					break;
				if(dst[i] == '\\')
					dst[i] = '/';
			}
			if(strlen(dst) == 0)
			{
				free(dst);
				dst = nullptr;
			}
			return dst;
		}

		c8* ctime(const t32* time)
		{
			time_t t = (time_t)*time;
			c8* dst = std::ctime(&t);
			dst[strcspn(dst, "\n")] = '\0';
			return dst;
		}
		t32 ftime(const c8* filename)
		{
			struct stat sb;
			return stat(filename, &sb) != -1 ? (t32)sb.st_mtime : -1;
		}
	};
	/* audit types */
	namespace audit
	{
		bool visible = false;
		enum class action
		{
			add = 0,
			rem = 1,
			chg = 2,
		};
		struct entry
		{
			c8                user[32];
			t32              timestamp;
			enum action         action;
			c8               name[256];
			t32          old_timestamp;
			u32               old_size;
			t32          new_timestamp;
			u32               new_size;
		};

		std::pair<enum action, const char*> str[3] = { { action::add, "          Add" }, { action::rem, "       Remove" }, { action::chg, "       Change" } };
		const char* print(const struct entry& src)
		{
			static char dst[1024] = { '\0' };
			sprintf(dst, "[AUD] %s %.8X %.8X %s %s\n[AUD] %s %.8X %.8X %13u %s\n[AUD] %s %.8X %.8X %13u %s\n", string::ctime(&src.timestamp), -1, -1, str[(size_t)src.action].second, src.user, string::ctime(&src.old_timestamp), -1, -1, src.old_size, src.name, string::ctime(&src.new_timestamp), -1, -1, src.new_size, src.name);
			return visible ? (const char*)dst : "";
		}
	};

	constexpr void parse_args(int argc, char** argv)
	{
		int opt;

		while((opt = getopt(argc, argv, "xa")) != -1) {
			switch(opt) {
				case 'x':
					extract = true;
					break;
				case 'a':
					audit::visible = true;
					break;
				default:
					fprintf(stderr, "Usage: %s [-x] [-a] [POD3FILE]\n", argv[0]);
					exit(EXIT_FAILURE);
			}
		}
		if(optind >= argc)
		{
			fprintf(stderr, "Usage: %s [-x] [-a] [POD3FILE]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
		printf("\n");
	}

	/* pod archive types */
	template<enum version>
	struct archive;

	template<enum version version>
	constexpr inline uint32_t checksum(const uint8_t* buf, size_t size);

        /* POD1 Style types */
	template<>
	struct archive<pod1>
	{
		struct header
		{
			u32            entry_count;
			c8             comment[80];
		};
		struct entry
		{
			c8                name[32];
			u32                   size;
			u32                 offset;
		};
	};
	template<>
	struct archive<epd>
	{
		struct header
		{
			c8                ident[4];
			c8            comment[256];
			u32            entry_count;
			u32                version;
			u32               checksum;
		};

		struct entry
		{
			c8                name[64];
			u32                   size;
			u32                 offset;
			u32              timestamp;
			u32               checksum;
		};
	};
	template<>
	struct archive<last>
	{
		using header = archive<epd>::header;
		using entry  = archive<epd>::entry;
	};
	template<>
	struct archive<pod2>
	{
		struct header
		{
			c8                ident[4];
			u32               checksum;
			c8             comment[80];
			u32            entry_count;
			u32            audit_count;
		};

		struct entry
		{
			u32           names_offset;
			u32                   size;
			u32                 offset;
			t32              timestamp;
			u32               checksum;
		};
	};
	template<>
	struct archive<pod6>
	{
		struct header
		{
			c8                ident[4];
			u32            entry_count;
			u32                version;
			u32           entry_offset;
			u32            names_count;
		};
		struct entry
		{
			u32           names_offset;
			u32                   size;
			u32                 offset;
			u32           uncompressed;
			u32      compression_level;
			u32                   zero;
		};
	};
        /* POD3 Style types */
	namespace depend
	{
		struct entry
		{
			u8            unknown[264];
		};
	};
	template<>
	struct archive<pod3>
	{
#pragma pack(push,1)
		struct entry
		{
			u32           names_offset;
			u32                   size;
			u32                 offset;
			t32              timestamp;
			u32               checksum;
		};
#pragma pack(pop)

#pragma pack(push,1)
		struct header
		{
			/* 0x0000 */ c8            ident[4];
			/* 0x0004 */ u32           checksum;
			/* 0x0008 */ c8         comment[80]; 
			/* 0x0058 */ u32        entry_count;
			/* 0x005c */ u32        audit_count;
			/* 0x0060 */ u32           revision;
			/* 0x0064 */ u32           priority;
			/* 0x0068 */ c8          author[80];
			/* 0x00B8 */ c8       copyright[80];
			/* 0x0108 */ u32       entry_offset;
			/* 0x010c */ u32          entry_crc;
			/* 0x0110 */ u32         names_size;
			/* 0x0114 */ u32      depends_count;
			/* 0x0118 */ u32        depends_crc;
			/* 0x011c */ u32         audits_crc;
			constexpr inline            u32      checksum_offset(            ) { return sizeof(checksum) + sizeof(ident); }
			constexpr inline            u32       entries_offset(            ) { return entry_offset; }
			constexpr inline            u32         names_offset(            ) { return entry_offset + entry_count * sizeof(struct entry); }
			constexpr inline            u32       depends_offset(            ) { return names_size + names_offset(); }
			constexpr inline            u32        audits_offset(            ) { return depends_offset() + depends_count * sizeof(struct depend::entry); }
			constexpr inline            b8       checksum_verify(uint8_t* buf) { return    checksum == crc32::mpeg2::compute(&buf[checksum_offset()], sizeof(struct header) - sizeof(checksum) - sizeof(ident)); } 
			constexpr inline            b8        entries_verify(uint8_t* buf) { return   entry_crc == crc32::mpeg2::compute(&buf[ entries_offset()],   entry_count * sizeof(struct entry)); }
			constexpr inline            b8        depends_verify(uint8_t* buf) { return depends_crc == crc32::mpeg2::compute(&buf[ depends_offset()], depends_count * sizeof(struct depend::entry)); }
			constexpr inline            b8         audits_verify(uint8_t* buf) { return  audits_crc == crc32::mpeg2::compute(&buf[  audits_offset()],   audit_count * sizeof(struct  audit::entry)); }
			constexpr inline struct         entry* entries_begin(uint8_t* buf) { return reinterpret_cast<struct         entry*>(&buf[entries_offset()]); }
			constexpr inline struct depend::entry* depends_begin(uint8_t* buf) { return reinterpret_cast<struct depend::entry*>(&buf[depends_offset()]); }
			constexpr inline struct  audit::entry*  audits_begin(uint8_t* buf) { return reinterpret_cast<struct  audit::entry*>(&buf[ audits_offset()]); }
		};
#pragma pack(pop)

		struct extra_header : header
		{
			u32            pad120;
		};
		constexpr static bool verify(const uint8_t* buf, size_t len)
		{
			u32 checksum = (u32)-1;
			if(id((const char*)buf) == pod3)
				checksum = pod::checksum<pod3>(buf, len);
			if(checksum != (u32)-1)
				return *(uint32_t*)(buf + 4) == checksum;
			return false;
		}
		constexpr static bool verify(std::filesystem::path src)
		{
			FILE* fi      = nullptr;
			size_t len    = 0;
			u8* buf  = nullptr;
			b8 status   = false;
			if(std::filesystem::exists(src) && ((len = std::filesystem::file_size(src)) > 0))
			{
				if(((fi = fopen(src.c_str(), "rb")) != nullptr))
				{
					if(((buf = (u8*)std::malloc(len)) != nullptr) && fread(buf, len, 1, fi) == 1)
					{
						status = verify(buf, len);
						free(buf);
					}
					fclose(fi);
				}
			}
			if(!status) fprintf(stderr, "Error opening/reading file %s\n", src.c_str());
			return status;
		}
	};
	template<>
	struct archive<pod4>
	{
		using header       = archive<pod3>::header;
		using extra_header = archive<pod3>::extra_header;

		struct entry
		{
			u32      names_offset;
			u32              size;
			u32            offset;
			u32 uncompressed_size;
			u32 compression_level;
			t32         timestamp;
			u32          checksum;
		};
	};
	template<>
	struct archive<pod5>
	{
		struct header : archive<pod3>::header
		{
			u8   next_archive[80];
		};
		struct extra_header : header
		{
			u32            pad124;
		};
		using entry = archive<pod4>::entry;
	};

	/* checksum types */
	enum class section
	{
		none   = 0,
		file   = 1,
		header = 2,
		extra  = 3,
		entry  = 4,
		depend = 5,
		audit  = 6,
	};

	/*
	checksum: crc32::mpeg2
	============================================================================
	| POD2 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(file  )-offset |
	| POD3 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset |
	| POD4 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset |
	| POD5 : offset=sizeof(ident)+sizeof(checksum) count=sizeof(header)-offset |
	| EPD  : offset=sizeof(header)                 count=sizeof(file  )-offset |
	============================================================================
	checksum: none
	============================================================================
	| POD6 : offset=sizeof(header)                 count=sizeof(file  )-offset |
	| POD1 : offset=sizeof(header)=4+80            count=sizeof(file  )-offset |
	============================================================================
	*/
	const std::pair<uint32_t, enum section> range[count] =
	{
		{ 0u                                                                            , section::none   },
		{ sizeof(struct archive<pod1>::header)                                          , section::file   },
		{ sizeof(archive<pod2>::header::ident) + sizeof(archive<pod2>::header::checksum), section::file   },
		{ sizeof(archive<pod3>::header::ident) + sizeof(archive<pod3>::header::checksum), section::header },
		{ sizeof(archive<pod4>::header::ident) + sizeof(archive<pod4>::header::checksum), section::header },
		{ sizeof(archive<pod5>::header::ident) + sizeof(archive<pod5>::header::checksum), section::header },
		{ sizeof(struct archive<pod6>::header)                                          , section::file   },
		{ sizeof(struct archive<epd>::header)                                           , section::file   },
		{ sizeof(archive<last>::header)                                                 , section::file   },
	};

	template<enum version version>
	constexpr inline size_t section_size(size_t size)
	{
		switch(range[version].second)
		{
			case section::entry:
			case section::file:
				return size;
			case section::header:
				return sizeof(struct archive<version>::header);
			case section::none:
			default:
				return 0;
		}
	}

	template<enum version version>
	constexpr inline size_t section_offset()
	{
		switch(range[version].second)
		{
			case section::header:
			case section::file:
				return range[version].first;
			case section::entry:
			case section::none:
			default:
				return 0;
		}
	}

	template<enum version version>
	constexpr inline uint32_t checksum(const uint8_t* buf, size_t size)
	{
		return crc32::mpeg2::compute(buf + section_offset<version>(), section_size<version>(size) - section_offset<version>());
	}


	/* file entry */
	struct entry
	{
		char*                 name;
		t32          timestamp;
		u32          checksum;
		u32            offset;
		u32              size;
		u32 uncompressed_size;
		u32 compression_level;
		u8*     data;
		entry() : name(nullptr), timestamp(-1), checksum(-1), size(0), data(nullptr) { }
		~entry() { if(name) free(name); }
		b8 extract(std::filesystem::path dst = ".")
		{
			const std::filesystem::path od = dst / name;
			std::filesystem::create_directories(od.parent_path());
			FILE* of = fopen(od.c_str(), "wb");
			if(of == nullptr)
				return false;
			size_t written = fwrite(data, size, 1, of);
			fclose(of);
			if(written != 1)
			{
				fprintf(stderr, "[ERR] extracting %s\n", od.c_str());
				return false;
			}
			struct utimbuf ot = { (time_t)timestamp, (time_t)timestamp };
			return (utime(od.c_str(), &ot) == 0);
		}
	};
	struct file
	{
		std::filesystem::path name;
		enum version version = version::none;
		u32 size;
		u32 checksum;
		t32 timestamp;
		std::vector<u8> data;
		FILE* fp;

		archive<pod3>::header* hdr;
		std::vector<struct pod::entry> entries;

		file() : size(0), checksum(-1), hdr(nullptr) { }
		file(std::filesystem::path filename) : name(filename), size(std::filesystem::file_size(filename)), checksum(-1), hdr(nullptr)
		{
			version = verify_file();
			switch(version)
			{
				case pod1:
					break;
				case pod2:
//					hdr = reinterpret_cast<archive<pod2>::header*>(&data[0]);
//					entries.resize(hdr->entry_count);
					break;
				case epd:
				case last:
					break;
				case pod6:
					break;
				case pod3:
				case pod4:
				case pod5:
					{
						hdr = reinterpret_cast<archive<pod3>::header*>(&data[0]);
						entries.resize(hdr->entry_count);
						archive<pod3>::entry* dict = reinterpret_cast<archive<pod3>::entry*>(&data[hdr->entry_offset]);

						if(hdr->checksum_verify(&data[0]) && hdr->entries_verify(&data[0]) && hdr->depends_verify(&data[0]) && hdr->audits_verify(&data[0]))
							printf("[ERR] POD3/4/5 checksum verification failed for %s!\n", name.c_str());

						for(uint32_t i = 0; i < hdr->entry_count; i++)
						{
							entries[i].name      = pod::string::gets(reinterpret_cast<char*>(&data[hdr->names_offset() + dict[i].names_offset]));
							entries[i].offset    = dict[i].offset;
							entries[i].timestamp = dict[i].timestamp;
							entries[i].checksum  = dict[i].checksum;
							entries[i].size      = dict[i].size;
							/*
							entries[i].uncompressed_size = version > pod3 ? dict[i].uncompressed_size : dict[i].size;
							entries[i].compression_level = version > pod3 ? dict[i].compression_level : 0;
							*/
							entries[i].data      = &data[entries[i].offset];
						}
						print();
					}
					break;
				case none:
				default:
					break;
			}
		}
		constexpr void print()
		{
			printf("[NFO] %s checksum   offset          size name\n\n", pod::string::ctime(&timestamp));
			for(u32 i = 0; i < entries.size(); i++)
				printf("[ENT] %s %.8X %.8X %13u %s\n", pod::string::ctime(&entries[i].timestamp), entries[i].checksum, entries[i].offset, entries[i].size, entries[i].name);
			if(pod::audit::visible)
				for(u32 i = 0; i < hdr->audit_count; i++)
					printf("%s\n", pod::audit::print(reinterpret_cast<struct audit::entry*>(&data[hdr->audits_offset()])[i]));
			printf("\n[HDR] %s %.8X %.8X %13zu %s %s %s %s\n", pod::string::ctime(&timestamp), hdr->checksum, 0, sizeof(struct pod::archive<pod3>::header), pod::ident[pod::id(hdr->ident)].first, hdr->comment, hdr->author, hdr->copyright);
			printf("[FLE] %s %.8X %.8X %13u %s\n", pod::string::ctime(&timestamp), checksum, 0, size, name.c_str());
			printf("[CNT] %s %.8X %.8X %13u %u %u\n\n\n", pod::string::ctime(&timestamp), -1, -1, hdr->entry_count, hdr->depends_count, hdr->audit_count);
		}
		~file() {  }
		enum version verify_file()
		{
			checksum             = -1;
			enum version version = version::none;
			if(std::filesystem::exists(name) && size > 0)
			{
				timestamp = pod::string::ftime(name.c_str());
				data.resize(size);
				if((fp = fopen(name.c_str(), "rb")) != nullptr)
				{
					if(fread(&data[0], size, 1, fp) == 1)
					{
						version = id((const c8*)&data[0]);
						checksum = crc32::mpeg2::compute(&data[0], size);
					}
					fclose(fp);
				}
				return version;
			}
			fprintf(stderr, "[ERR] file %s does not exist or is empty\n", name.c_str());
			return version;
		}
		b8 verify_entries()
		{
			for(u32 i=0; i < entries.size(); i++)
			{
				u32 chksum = crc32::mpeg2::compute(entries[i].data, entries[i].size);
				if(chksum != entries[i].checksum)
				{
					fprintf(stderr, "[ERR] CRC-32/MPEG-2 checksum verification failed for %s of size %u in %s\n", entries[i].name, entries[i].size, name.c_str());
					return false;
				}
			}
			return true;
		}
		struct pod::entry& operator[](u32 i) { return entries[i]; }
	};
};
/*
	struct pod : std::vector<uint8_t>
	{

		struct header_pod1& header_pod1() { return * (struct header_pod1*)(*this).data(); }
		struct entry_pod1&   entry_pod1(number i) { return * (struct  entry_pod1*)((*this).data() + sizeof(struct header_pod1) + i * sizeof(struct entry_pod1)); }
		
		std::vector<uint8_t> read(struct entry_pod1& src) { return std::vector<uint8_t>((*this).begin() + src.offset, (*this).begin() + src.offset + src.size); }
		bool write(struct entry_pod1& src)
		{
			std::filesystem::path dst(src.name.data());
			std::filesystem::create_directories(dst.parent_path());
			FILE* fo = fopen(dst.c_str(), "wb");
			if(fo)
			{
				fwrite((*this).data() + src.offset, src.size, 1, fo);
				fclose(fo);
				return true;
			}
			return false;
		}
		bool extract()
		{
			for(number i = 0; i < header_pod1().count; i++)
				if(!write(entry_pod1(i))) return false;
			return true;
		}
		void list()
		{
			number data_size = 0;
			for(number i = 0; i < header_pod1().count; i++)
			{
				data_size += entry_pod1(i).size;
				printf("%13u %32s\n", entry_pod1(i).size, entry_pod1(i).name.data());
			}
			printf("\n%13u %32u\n", data_size, header_pod1().count);
		}
	};
*/

