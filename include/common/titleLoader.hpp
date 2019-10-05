#ifndef TITLELOADER_HPP
#define TITLELOADER_HPP

#include <3ds.h>
#include <algorithm>
#include <citro2d.h>
#include <string>

class TitleLoader
{
public:
    // std::make_shared stuff.
    TitleLoader(void) = default;
    ~TitleLoader(void);

    // Title Handling.
    bool load(u64 id, FS_MediaType mediaType);
    u32 highId(void);
    u32 lowId(void);
    u64 ID(void) { return (u64)highId() << 32 | lowId(); }
    FS_MediaType mediaType(void);
    std::string name(void);
    std::string Author(void);
    C2D_Image icon(void);

private:
    u64 mId;
    FS_MediaType mMedia;
    FS_CardType mCard;
    C2D_Image mIcon;
    std::string mName;
    std::string mAuthor;
};

#endif
