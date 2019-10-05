#include "common/utils.hpp"

#include "core/titleLoader.hpp"

// Properly free the Icon.

TitleLoader::~TitleLoader(void)
{
    if (mCard != CARD_TWL && mIcon.tex)
        C3D_TexDelete(mIcon.tex);
}

// Load the Icon from the SMDH.
static C2D_Image loadTextureIcon(smdh_s* smdh)
{
    C3D_Tex* tex                          = new C3D_Tex;
    static const Tex3DS_SubTexture subt3x = {48, 48, 0.0f, 48 / 64.0f, 48 / 64.0f, 0.0f};
    C3D_TexInit(tex, 64, 64, GPU_RGB565);

    u16* dest = (u16*)tex->data + (64 - 48) * 64;
    u16* src  = (u16*)smdh->bigIconData;
    for (int j = 0; j < 48; j += 8)
    {
        std::copy(src, src + 48 * 8, dest);
        src += 48 * 8;
        dest += 64 * 8;
    }

    return C2D_Image{tex, &subt3x};
}

// Load the Title. (Used for the Scan as well.)
bool TitleLoader::load(u64 id, FS_MediaType media)
{
        bool loadTitle = false;
        mId            = id;
        mMedia         = media;

        smdh_s* smdh = loadSMDH(lowId(), highId(), mMedia);
        if (smdh == NULL)
        {
            return false;
        }

        mName   = StringUtils::UTF16toUTF8((char16_t*)smdh->applicationTitles[1].shortDescription);
        mAuthor = StringUtils::UTF16toUTF8((char16_t*)smdh->applicationTitles[1].publisher); 
        mLongDescription = StringUtils::UTF16toUTF8((char16_t*)smdh->applicationTitles[1].longDescription);
        loadTitle = true;
        mIcon     = loadTextureIcon(smdh);
        delete smdh;
    return loadTitle;
}


u32 TitleLoader::highId(void)
{
    return (u32)(mId >> 32);
}

u32 TitleLoader::lowId(void)
{
    return (u32)mId;
}

u64 TitleLoader::ID(void)
{
    return (u64)highId() << 32 | lowId();
}

FS_MediaType TitleLoader::mediaType(void)
{
    return mMedia;
}

// Get the Icon from the SMDH.

C2D_Image TitleLoader::icon(void)
{
    return mIcon;
}

// get the name of the Title from the SMDH.
std::string TitleLoader::name(void)
{
    return mName;
}

std::string TitleLoader::Author(void)
{
    return mAuthor;
}

std::string TitleLoader::longDescription(void)
{
    return mLongDescription;
}