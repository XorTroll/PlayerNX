
#pragma once
#include "Include.hpp"
#include "Gfx.hpp"

namespace Player
{
    void playbackInit(string VideoPath);
    bool playbackLoop();
    void playbackPause();
    void playbackResume();
    void playbackPauseResume();
    void playbackStop();
    void playbackExit();
    void playbackSetFastForward(int Power);
    void playbackThrowError(string Error);
    vector<string> getVideoFiles();
}