/*
*   This file is part of LeafEdit/Project-Athena
*   Copyright (C) 2019 VoltZ, Epicpkmn11, Flame, RocketRobz, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "core/gameLoader.hpp"

#include "gui/gui.hpp"

#include <array>

// Define the scanned Title ID's.
static constexpr std::array<unsigned long long, 1> titleIds = {
    0x0004000004394100 // Universal-Manager.
};

// Scan the defined Title ID's from above.
void GameLoader::scanTitleID(void)
{
    Result res = 0;
    u32 count  = 0;

    // clear title list if filled previously
    installedTitles.clear();

    res = AM_GetTitleCount(MEDIATYPE_SD, &count);
    if (R_FAILED(res))
    {
        return;
    }

    // get title list and check if a title matches the ids we want
    std::vector<u64> ids(count);
    u64* p = ids.data();
    res    = AM_GetTitleList(NULL, MEDIATYPE_SD, count, p);
    if (R_FAILED(res))
    {
        return;
    }

    for (size_t i = 0; i < titleIds.size(); i++)
    {
        u64 id = titleIds.at(i);
        if (std::find(ids.begin(), ids.end(), id) != ids.end())
        {
            auto title = std::make_shared<TitleLoader>();
            if (title->load(id, MEDIATYPE_SD))
            {
                installedTitles.push_back(title);
            }
        }
    }

    // sort the list alphabetically
    std::sort(installedTitles.begin(), installedTitles.end(), [](std::shared_ptr<TitleLoader>& l, std::shared_ptr<TitleLoader>& r) { return l->ID() < r->ID(); });
}