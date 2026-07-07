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
        inline static ALCdevice* _device = nullptr;     // Устройство OpenAL                                
        inline static ALCcontext* _context = nullptr;   // Контекст OpenAL                                  
        inline static POINT3D<float> _listenerPos{ 0.0f, 0.0f, 0.0f }; // Позиция слушателя                                
        inline static POINT3D<float> _listenerVel{ 0.0f, 0.0f, 0.0f };   // Скорость слушателя                               
        inline static float _orientation[6] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };  // Ориентация слушателя (направление + вверх)       
        inline static bool _init = false;            // Флаг инициализации                               
      public:
        // Приватный метод инициализации
        static void init() {
          if (_init) {
            RG_LOG_LOCK_CRITICAL("OpenAL already initialized");
            return;
          }

          _device = alcOpenDevice(NULL);
          if (!_device) {
            RG_LOG_LOCK_CRITICAL("Error: Failed to open OpenAL device");
            _init = false;
            return;
          }

          _context = alcCreateContext(_device, NULL);
          if (!_context) {
            RG_LOG_LOCK_CRITICAL("Error: Failed to create OpenAL context");
            alcCloseDevice(_device);
            _device = nullptr;
            _init = false;
            return;
          }

          if (!alcMakeContextCurrent(_context)) {
            RG_LOG_LOCK_CRITICAL("Error: Failed to set OpenAL context");
            alcDestroyContext(_context);
            alcCloseDevice(_device);
            _context = nullptr;
            _device = nullptr;
            _init = false;
            return;
          }

          if (ALenum error = alGetError(); error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error initializing OpenAL: " + std::to_string(error));
            alcMakeContextCurrent(NULL);
            // alcDestroyContext, nullptr);
            alcDestroyContext(_context);
            alcCloseDevice(_device);
            _context = nullptr;
            _device = nullptr;
            _init = false;
            return;
          }

          // Инициализируем слушателя (позиция всегда (0, 0, 0) по умолчанию)
          _listenerPos = POINT3D<float>(0.0f, 0.0f, 0.0f);
          alListenerfv(AL_POSITION, &_listenerPos.x);
          alListenerfv(AL_VELOCITY, &_listenerVel.x);
          alListenerfv(AL_ORIENTATION, _orientation);
          if (ALenum error = alGetError(); error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error setting listener: " + std::to_string(error));
            alcMakeContextCurrent(NULL);
            alcDestroyContext(_context);
            alcCloseDevice(_device);
            _context = nullptr;
            _device = nullptr;
            _init = false;
            return;
          }

          // Регистрируем очистку при выходе
          std::atexit(cleanup);
          _init = true;
        }

        // Приватный метод очистки
        static void cleanup() {
          if (!_init) return;
          _init = false;
          if (_context) {
            alcMakeContextCurrent(NULL);
            alcDestroyContext(_context);
            _context = nullptr;
          }
          if (_device) {
            alcCloseDevice(_device);
            _device = nullptr;
          }
        }

      public:
        // Установка позиции слушателя
        static void setListenerPos(const POINT3D<float>& pos) {
          if (!_init) init();
          if (!_init) {
            RG_LOG_LOCK_CRITICAL("OpenAL not initialized");
            return;
          }
          _listenerPos = pos;
          alListenerfv(AL_POSITION, &_listenerPos.x);
          if (ALenum error = alGetError(); error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error setting listener position: " + std::to_string(error));
          }
        }

        // Установка скорости слушателя
        static void setListenerVel(const POINT3D<float>& vel) {
          if (!_init) init();
          if (!_init) {
            RG_LOG_LOCK_CRITICAL("OpenAL not initialized");
            return;
          }
          _listenerVel = vel;
          alListenerfv(AL_VELOCITY, &_listenerVel.x);
          if (ALenum error = alGetError(); error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error setting listener velocity: " + std::to_string(error));
          }
        }

        // Установка ориентации слушателя
        static void setListenerOrientation(const POINT3D<float>& forward, const POINT3D<float>& up) {
          if (!_init) init();
          if (!_init) {
            RG_LOG_LOCK_CRITICAL("OpenAL not initialized");
            return;
          }
          _orientation[0] = forward.x; _orientation[1] = forward.y; _orientation[2] = forward.z;
          _orientation[3] = up.x; _orientation[4] = up.y; _orientation[5] = up.z;
          alListenerfv(AL_ORIENTATION, _orientation);
          if (ALenum error = alGetError(); error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error setting listener orientation: " + std::to_string(error));
          }
        }

        // Установка глобальной громкости
        static void setGlobalGain(float gain) {
          if (!_init) init();
          if (!_init) {
            RG_LOG_LOCK_CRITICAL("OpenAL not initialized");
            return;
          }
          alListenerf(AL_GAIN, gain);
          if (ALenum error = alGetError(); error != AL_NO_ERROR) {
            RG_LOG_LOCK_CRITICAL("Error setting global gain: " + std::to_string(error));
          }
        }

        // Проверка инициализации
        static bool isInitialized() {
          if (!_init) init();
          return _init && _device && _context;
        }
      };

      // Инициализация статических членов

    }
  }
}




void RG_Sound_Engine_Init() {
  RG_LOG_LOCK_DEBUG("Rinegine Sound Engine Init");
  RG::Sound::Lock::Core::init();
  RG_LOG_LOCK_DEBUG("RSE init is done");
}
#define RG_SOUND_INIT RG_Sound_Engine_Init()



