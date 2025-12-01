#pragma once

#define AL_LIBTYPE_STATIC
// #ifdef RG_x64
#include "AL/al.h"
#include "AL/alc.h"

// #include "libavcodec/avcodec.h"
// #include "libavformat/avformat.h"
// #include "libavutil/opt.h"
// #include "libavutil/samplefmt.h"
// #include "libswresample/swresample.h"
// #elif
// #include "other/OpenAL/32/include/AL/al.h"
// #include "other/OpenAL/32/include/AL/alc.h"
// #endif

namespace RG {
  namespace Sound {
    namespace Lock {
      class Core {
        ALCdevice* device;// = alcOpenDevice(NULL);
        ALCcontext* context;// = alcCreateContext(device, NULL);
        inline static bool _init = false;
      public:
        void init() {
          if (_init)return;
          _init = true;
          // device = alcOpenDevice(nullptr);
          device = alcOpenDevice(NULL); // open default device
          if (device != NULL) {
            context = alcCreateContext(device, NULL); // create context
            if (context != NULL) {
              alcMakeContextCurrent(context); // set active context
            } else {
              ALenum error = alGetError();
              RG_LOG_LOCK_CRITICAL("Error OpenAL: " + to_string(error));
            }
          } else {
            ALenum error = alGetError();
            RG_LOG_LOCK_CRITICAL("Error OpenAL: " + to_string(error));
          }
          ALenum error = alGetError();
          if (error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error OpenAL: " + to_string(error));
          }
        }
        ~Core() {
          if (!_init)return;
          _init = false;
          alcMakeContextCurrent(NULL);
          alcDestroyContext(context);
          alcCloseDevice(device);
        }
      } _core;
    }
  }
}



void RG_Sound_Engine_Init() {
  RG_LOG_LOCK_DEBUG( "Rinegine Sound Engine Init");
  RG::Sound::Lock::_core.init();
  RG_LOG_LOCK_DEBUG( "RSE init is done");
}
#define RG_SOUND_INIT RG_Sound_Engine_Init()



