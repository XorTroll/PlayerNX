#include "Player.hpp"

int main()
{
    romfsInit();
    Gfx::init();
    start:
    vector<string> vids = Player::getVideoFiles();
    Gfx::drawImage(0, 0, "romfs:/Main.jpg");
    u32 selected = 0;
    if(vids.empty()) Gfx::drawText(75, 130, "No video files were found.\nPlace them at 'sdmc:/media' folder.\nSupported formats: MP4, MKV, 3GP, AVI, FLV, WMV, WEBM", { 255, 255, 255, 255 }, 20);
    else
    {
        u32 bx = 50;
        u32 by = 120;
        for(u32 i = 0; i < vids.size(); i++)
        {
            Gfx::RGBA color = { 255, 255, 255, 255 };
            if(i == selected) color = { 180, 180, 255, 255 };
            if(i > 20)
            {
                bx += 500;
                if(i == 20) by = 120;
            }
            Gfx::drawText(bx, by, vids[i], color, 18);
            by += 25;
        }
    }
    while(appletMainLoop())
    {
        hidScanInput();
        u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
        if((k & KEY_A) & (!vids.empty())) break;
        else if((k & KEY_PLUS) || (k & KEY_MINUS))
        {
            Gfx::exit();
            romfsExit();
            return 0;
        }
        else if(k & KEY_UP)
        {
            if(selected > 0)
            {
                selected--;
                u32 bx = 50;
                u32 by = 120;
                for(u32 i = 0; i < vids.size(); i++)
                {
                    Gfx::RGBA color = { 255, 255, 255, 255 };
                    if(i == selected) color = { 180, 180, 255, 255 };
                    if(i > 20)
                    {
                        bx += 500;
                        if(i == 20) by = 120;
                    }
                    Gfx::drawText(bx, by, vids[i], color, 18);
                    by += 25;
                }
            }
        }
        else if(k & KEY_DOWN)
        {
            if(selected < (vids.size() - 1))
            {
                selected++;
                u32 bx = 50;
                u32 by = 120;
                for(u32 i = 0; i < vids.size(); i++)
                {
                    Gfx::RGBA color = { 255, 255, 255, 255 };
                    if(i == selected) color = { 180, 180, 255, 255 };
                    if(i > 20)
                    {
                        bx += 500;
                        if(i == 20) by = 120;
                    }
                    Gfx::drawText(bx, by, vids[i], color, 18);
                    by += 25;
                }
            }
        }
        Gfx::flush();
    }
    Gfx::clear({ 255, 255, 255, 255 });
    Player::playbackInit("/media/" + vids[selected]);
    while(appletMainLoop() && Player::playbackLoop());
    Gfx::drawImage(0, 0, "romfs:/Main.jpg");
    Gfx::drawText(75, 130, "Video playback finished.\n\nPress A to go back to the menu.\nPress Plus or Minus to exit PlayerNX.", { 255, 255, 255, 255 }, 20);
    while(appletMainLoop())
    {
        hidScanInput();
        u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A) goto start;
        else if((k & KEY_PLUS) || (k & KEY_MINUS)) break;
        Gfx::flush();
    }
    Gfx::exit();
    romfsExit();
    return 0;
}