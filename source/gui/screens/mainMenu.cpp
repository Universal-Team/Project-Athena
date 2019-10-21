	/*
*   This file is part of Project-Athena
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

#include "common/utils.hpp"

#include "core/gameLoader.hpp"

#include "gui/screens/screenCommon.hpp"
#include "gui/screens/mainMenu.hpp"

#include <vector>

extern bool exiting;
extern int fadealpha;
extern bool fadein;

// Get the Max Amount of available Titles.
MainMenu::MainMenu() {
	maxTitles = (int)GameLoader::installedTitles.size();
} 

void MainMenu::Draw(void) const
{
	// Top Bars.
	Gui::ScreenDraw(top);
	Gui::Draw_Rect(0, 0, 400, 30, Chartreuse);
	Gui::Draw_Rect(0, 30, 400, 180, Mocha);
	Gui::Draw_Rect(0, 210, 400, 30, Chartreuse);


	// First Row.
	Gui::Draw_Rect(80, 35, 240, 50, Pool);
	Gui::Draw_Rect(0, 35, 40, 50, Pool);
	Gui::Draw_Rect(360, 35, 40, 50, Pool);

	// Second Row.
	Gui::Draw_Rect(80, 95, 240, 50, Pool);
	Gui::Draw_Rect(0, 95, 40, 50, Pool);
	Gui::Draw_Rect(360, 95, 40, 50, Pool);

	// Third Row.
	Gui::Draw_Rect(80, 155, 240, 50, Pool);
	Gui::Draw_Rect(0, 155, 40, 50, Pool);
	Gui::Draw_Rect(360, 155, 40, 50, Pool);

	// Icon & Metainfo like App name and Author.
	Gui::sprite(sprites_icon_idx, 85, 36);
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, "Athena"))/2-120+50+95, 40, 0.5f, BLACK, "Athena");
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, "Universal-Team"))/2-120+50+95, 60, 0.5f, BLACK, "Universal-Team");
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fadealpha)); // Fade in/out effect

	// Test animated Selector.
	Gui::drawAnimatedSelector(80, 95, 240, 50, .030, C2D_Color32(0, 0, 0, 0)); // Row 2 -> Installed Title.
	DrawTitle();

	// Bottom Bars.
	Gui::ScreenDraw(bottom);
	Gui::Draw_Rect(0, 0, 320, 30, Chartreuse);
	Gui::Draw_Rect(0, 30, 320, 180, Mocha);
	Gui::Draw_Rect(0, 210, 320, 30, Chartreuse);

	// Bottom Text Boxes.
	Gui::Draw_Rect(0, 100, 320, 30, Pool);
	Gui::Draw_Rect(0, 140, 320, 30, Pool);

	// Path and Description and the Icon as well.
	if (!GameLoader::installedTitles.empty()) {
		C2D_DrawImageAt(GameLoader::installedTitles[selectedTitle]->icon(), 245, 42, 0.5f); // Installed Title Icon.
	}
	//Gui::DrawString((320-Gui::GetStringWidth(0.50f, "Path: sdmc:/3ds/Project-Athena.3dsx"))/2, 107, 0.50f, BLACK, "Path: sdmc:/3ds/Project-Athena.3dsx");

	if (!GameLoader::installedTitles.empty()) {
		DrawDescription();
		if (mode == 2) {
			std::string IDAndCode = "ID: ";
			IDAndCode += StringUtils::format("%08X", titleFromIndex(selectedTitle)->lowId());
			IDAndCode += ", Prod Code: ";
			IDAndCode += titleFromIndex(selectedTitle)->productCode();
			Gui::Draw_Rect(0, 175, 320, 30, Pool);
			Gui::DrawString((320-Gui::GetStringWidth(0.6f, IDAndCode.c_str()))/2, 180, 0.6f, BLACK, IDAndCode.c_str(), 320);
		}
	}
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fadealpha)); // Fade in/out effect
}

void MainMenu::DrawTitle(void) const {
	if (!GameLoader::installedTitles.empty()) {
		C2D_DrawImageAt(GameLoader::installedTitles[selectedTitle]->icon(), 85, 96, 0.5f); // 48x48.
		Gui::DrawString((400-Gui::GetStringWidth(0.5f, GameLoader::installedTitles[selectedTitle]->name()))/2-120+50+95, 100, 0.5f, BLACK, GameLoader::installedTitles[selectedTitle]->name(), 180);
		Gui::DrawString((400-Gui::GetStringWidth(0.5f, GameLoader::installedTitles[selectedTitle]->Author()))/2-120+50+95, 120, 0.5f, BLACK, GameLoader::installedTitles[selectedTitle]->Author(), 180);
	}

	if (GameLoader::installedTitles.size() >= 3) {
		if (selectedTitle != maxTitles -1) {
			C2D_DrawImageAt(GameLoader::installedTitles[selectedTitle + 1]->icon(), 370, 96, 0.5f, NULL, 0.5, 0.5);
		} else {
			C2D_DrawImageAt(GameLoader::installedTitles[0]->icon(), 370, 96, 0.5f, NULL, 0.5, 0.5);
		}


		if (selectedTitle != 0) {
			C2D_DrawImageAt(GameLoader::installedTitles[selectedTitle - 1]->icon(), 1, 96, 0.5f, NULL, 0.5, 0.5);
		} else {
			C2D_DrawImageAt(GameLoader::installedTitles[maxTitles - 1]->icon(), 1, 96, 0.5f, NULL, 0.5, 0.5);
		}
	}
}

void MainMenu::DrawDescription(void) const {
	if (!GameLoader::installedTitles.empty()) {
		Gui::DrawString((320-Gui::GetStringWidth(0.6f, GameLoader::installedTitles[selectedTitle]->longDescription()))/2, 145, 0.6f, BLACK, GameLoader::installedTitles[selectedTitle]->longDescription(), 320);
	}
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (mode == 2) {
		TitleSelectionLogic(hDown);
	}

	if (hDown & KEY_START) {
		exiting = true;
	} else if (hDown & KEY_A) {
		if (!GameLoader::installedTitles.empty()) {
			u8 param[0x300];
			u8 hmac[0x20];
			memset(param, 0, sizeof(param));
			memset(hmac, 0, sizeof(hmac));
			APT_PrepareToDoApplicationJump(0, GameLoader::installedTitles[selectedTitle]->ID(), MEDIATYPE_SD);
			APT_DoApplicationJump(param, sizeof(param), hmac);
		}
	}
}

void MainMenu::TitleSelectionLogic(u32 hDown) {
	if (selectedTitle == -2)
	{
		if (!GameLoader::installedTitles.empty())
		{
			selectedTitle = 0;
		}
	}

	// Scroll with D-Pad Right to the next available Title.
	else if (hDown & KEY_RIGHT || hDown & KEY_R)
	{
		if (selectedTitle == (int)GameLoader::installedTitles.size() - 1 || selectedTitle == maxTitles - 1)
		{
			if (GameLoader::installedTitles.size() > maxTitles && selectedTitle > maxTitles - 1)
			{
				if (selectedTitle > maxTitles - 1)
				{
					selectedTitle = maxTitles;
				}
				else if (selectedTitle == maxTitles - 1)
				{
					selectedTitle = 0;
				}
			}
			else
			{
				selectedTitle = 0;
			}
		}
		else
		{
			selectedTitle++;
		}
	}

	// Scroll with D-Pad Left to the next available Title.
	else if (hDown & KEY_LEFT || hDown & KEY_L)
	{
		if (selectedTitle == -1)
		{
			selectedTitle = GameLoader::installedTitles.size() < maxTitles ? GameLoader::installedTitles.size() - 1 : maxTitles - 1;
		}
		else if (selectedTitle == maxTitles)
		{
			selectedTitle = (int)GameLoader::installedTitles.size() - 1;
		}
		else if (selectedTitle == 0)
		{
			selectedTitle = GameLoader::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameLoader::installedTitles.size() - 1;
		}
		else
		{
			selectedTitle--;
		}
	}
}