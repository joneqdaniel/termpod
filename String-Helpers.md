```cpp
namespace tr::pod::string
{
u32 ceil(u32 len)
{
        static const std::array<u32,12> sizes = { 4, 8, 12, 16, 32, 48, 64, 80, 96, 128, 256, 264 };
        std::array<u32,12>::const_iterator dst = sizes.begin();
        while(size > *dst) dst++;
        return *dst;
}

c8* fgets(u32 size, FILE* stream)
{
   if(size == 0)
       return nullptr;
   
   c8* dst = (c8*)calloc(ceil(size), 1);

   for(u32 i = 0; i < size; i++)
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
   return dst;
}

c8* ctime(const t32* time) 
{ 
        time_t t = (time_t)*time; 
        c8* dst = std::ctime(&t); 
        dst[strcspn(dst, "\n")] = '\0';
        return dst; 
}
};
```