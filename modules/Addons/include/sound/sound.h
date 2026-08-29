#pragma once

namespace RG {
  class Speaker {
    std::string _path;           // Путь к аудиофайлу
    Sound::AudioData _wav;       // Данные аудио
    ALuint _source;              // Источник звука OpenAL
    bool _is3D;                  // Флаг для 3D или глобального звука
    POINT3D<float> _pos;                // Позиция источника в 3D

  public:
    // Конструктор: загружает WAV и инициализирует источник
    Speaker(const std::string& path, bool is3D = false) : _path(path), _is3D(is3D), _source(0), _pos(0.0f, 0.0f, 0.0f) {
      // Загружаем аудио
      if (!_wav.loadFromWav(_path)) {
        RG_LOG_LOCK_CRITICAL("Failed to load WAV file: " + _path);
        return;
      }

      // Создаем источник звука
      alGenSources(1, &_source);
      if (alGetError() != AL_NO_ERROR) {
        RG_LOG_LOCK_CRITICAL("Error creating OpenAL source");
        return;
      }

      // Привязываем буфер из AudioData
      alSourcei(_source, AL_BUFFER, _wav.buffer);
      if (alGetError() != AL_NO_ERROR) {
        RG_LOG_LOCK_CRITICAL("Error binding buffer to source");
        alDeleteSources(1, &_source);
        _source = 0;
        return;
      }

      // Настраиваем параметры источника
      alSourcef(_source, AL_GAIN, 1.0f); // Громкость
      alSourcef(_source, AL_PITCH, 1.0f); // Тон
      if (_is3D) {
        float pos[3] = {_pos.x, _pos.y, _pos.z};
        alSourcefv(_source, AL_POSITION, pos); // Позиция в 3D
        alSourcei(_source, AL_SOURCE_RELATIVE, AL_FALSE); // Абсолютные координаты
      } else {
        alSourcei(_source, AL_SOURCE_RELATIVE, AL_TRUE); // Глобальный звук
        alSource3f(_source, AL_POSITION, 0.0f, 0.0f, 0.0f); // Центр слушателя
      }
    }

    // Установка позиции источника (только для 3D звука)
    void setPosition(const POINT3D<float>& pos) {
      if (!_is3D) return; // Игнорируем для глобального звука
      _pos = pos;
      float pos_array[3] = {_pos.x, _pos.y, _pos.z};
      alSourcefv(_source, AL_POSITION, pos_array);
      if (alGetError() != AL_NO_ERROR) {
        RG_LOG_LOCK_CRITICAL("Error setting source position");
      }
    }

    // Воспроизведение звука
    void play() {
      if (_source == 0) {
        RG_LOG_LOCK_CRITICAL("Invalid source: not initialized");
        return;
      }

      if (_wav.size <= 0 || _wav.sampleRate <= 0) {
        RG_LOG_LOCK_CRITICAL("Invalid WAV data: size=" + std::to_string(_wav.size) + ", sampleRate=" + std::to_string(_wav.sampleRate));
        return;
      }

      // Отладочный вывод
      rg_cout << L"Playing sound: source=" << _source
              << L", buffer=" << _wav.buffer
              << L", channels=" << _wav.channels
              << L", sampleRate=" << _wav.sampleRate
              << L", size=" << _wav.size << L"\n";

      alSourcePlay(_source);
      if (alGetError() != AL_NO_ERROR) {
        RG_LOG_LOCK_CRITICAL("Error playing sound");
        return;
      }

      // Проверяем, началось ли воспроизведение
      ALint state;
      alGetSourcei(_source, AL_SOURCE_STATE, &state);
      if (state != AL_PLAYING) {
        RG_LOG_LOCK_CRITICAL("Source is not playing");
      }
    }

    // Остановка звука
    void stop() {
      if (_source != 0) {
        alSourceStop(_source);
        if (alGetError() != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error stopping sound");
        }
      }
    }

    // Проверка, проигрывается ли звук
    bool isPlaying() const {
      if (_source == 0) return false;
      ALint state;
      alGetSourcei(_source, AL_SOURCE_STATE, &state);
      return state == AL_PLAYING;
    }

    // Деструктор: очищает источник
    ~Speaker() {
      if (_source != 0) {
        alDeleteSources(1, &_source);
      }
    }
  };
}

