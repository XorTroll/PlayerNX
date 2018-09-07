#include "Player.hpp"

int main()
{
    ifstream ifs("/media/video.mp4");
    if(!ifs.good())
    {
        gfxInitDefault();
        consoleInit(NULL);
        cout << endl << endl << endl << "    " << "PlayerNX - PoC video player, by XorTroll (using ffmpeg)" << endl << endl << endl;
        cout << endl << endl << "Video file was not found. Place it under 'sdmc:/media/video.mp4'." << endl << " - Press A to exit this application.";
        while(appletMainLoop())
        {
            hidScanInput();
            if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_A)
            {
                gfxExit();
                return 0;
            }
            gfxFlushBuffers();
            gfxSwapBuffers();
            gfxWaitForVsync();
        }
    }
    ifs.close();
    gfxInitDefault();
    consoleInit(NULL);
    cout << endl << endl << endl << "    " << "PlayerNX - PoC video player, by XorTroll (using ffmpeg)" << endl << endl << endl;
    cout << endl << endl << " - Press A to start playing the video: 'sdmc:/media/video.mp4'.";
    cout << endl << endl << "Controls during playback:";
    cout << endl << endl << " - Press Plus or Minus to stop video playback.";
    cout << endl << " - Press X to pause/resume video playback.";
    cout << endl << " - Press Y to fast forward (1x, 2x, 4x or 8x and start again)";
    cout << endl << endl << "This is a PoC video player, which will be improved. Known issues:";
    cout << endl << endl << " - No audio support, still needs to be added";
    cout << endl << " - Videos play with some lag";
    cout << endl << endl << "Enjoy using this PoC video player!";
    while(appletMainLoop())
    {
        hidScanInput();
        u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A)
        {
            gfxExit();
            break;
        }
        else if((k & KEY_PLUS) || (k & KEY_MINUS))
        {
            gfxExit();
            return 0;
        }
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    gfxExit();
    Player::playbackInit("/media/video.mp4");
    while(appletMainLoop() && Player::playbackLoop());
    gfxInitDefault();
    consoleInit(NULL);
    cout << endl << endl << endl << "    " << "PlayerNX - PoC video player, by XorTroll (using ffmpeg)" << endl << endl << endl;
    cout << endl << "Playback finished." << endl << endl << " - Press A to exit this application.";
    while(appletMainLoop())
    {
        hidScanInput();
        u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A) break;
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    gfxExit();
    return 0;
}