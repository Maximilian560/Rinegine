#pragma once

namespace RG {
  namespace Sound {
    struct AudioData {
      int channels;           // Количество каналов (1 - моно, 2 - стерео)
      int sampleRate;         // Частота дискретизации (например, 44100 Гц)
      int bitsPerSample;      // Бит на сэмпл (например, 16 для PCM)
      RG_Array<short> data;   // Аудиоданные в формате PCM
      int size;               // Размер данных в байтах
      ALuint buffer;          // OpenAL буфер для хранения аудиоданных

      AudioData() : channels(0), sampleRate(0), bitsPerSample(0), size(0), buffer(0) {}

      // Загрузка WAV-файла
      bool loadFromWav(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
          std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
          return false;
        }

        // Чтение заголовка WAV
        char chunkId[4];
        file.read(chunkId, 4);
        if (strncmp(chunkId, "RIFF", 4) != 0) {
          std::cerr << "Ошибка: Файл не является WAV" << std::endl;
          return false;
        }

        file.seekg(4, std::ios::cur); // Пропускаем размер файла
        file.read(chunkId, 4);
        if (strncmp(chunkId, "WAVE", 4) != 0) {
          std::cerr << "Ошибка: Неверный формат WAV" << std::endl;
          return false;
        }

        // Чтение подзаголовка fmt
        file.read(chunkId, 4);
        if (strncmp(chunkId, "fmt ", 4) != 0) {
          std::cerr << "Ошибка: Нет fmt чанка" << std::endl;
          return false;
        }

        int32_t chunkSize;
        file.read(reinterpret_cast<char*>(&chunkSize), 4);
        int16_t audioFormat;
        file.read(reinterpret_cast<char*>(&audioFormat), 2);
        if (audioFormat != 1) { // PCM = 1
          std::cerr << "Ошибка: Поддерживается только PCM формат" << std::endl;
          return false;
        }

        file.read(reinterpret_cast<char*>(&channels), 2);
        file.read(reinterpret_cast<char*>(&sampleRate), 4);
        file.seekg(4, std::ios::cur); // Пропускаем byte rate
        file.seekg(2, std::ios::cur); // Пропускаем block align
        file.read(reinterpret_cast<char*>(&bitsPerSample), 2);

        if (bitsPerSample != 16) {
          std::cerr << "Ошибка: Поддерживаются только 16-битные сэмплы" << std::endl;
          return false;
        }

        // Чтение подзаголовка data
        while (!file.eof()) {
          file.read(chunkId, 4);
          if (strncmp(chunkId, "data", 4) == 0) {
            break;
          }
          file.seekg(-3, std::ios::cur); // Возвращаемся на 3 байта назад
        }

        file.read(reinterpret_cast<char*>(&size), 4);
        data.resize(size / sizeof(short));
        file.read(reinterpret_cast<char*>(data.data()), size);

        file.close();

        // Создание OpenAL буфера
        alGenBuffers(1, &buffer);
        ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
        alBufferData(buffer, format, data.data(), size, sampleRate);

        return true;
      }

      // Воспроизведение звука
      void play() {
        if (buffer == 0) {
          std::cerr << "Ошибка: Буфер не инициализирован" << std::endl;
          return;
        }

        ALuint source;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);

        // Ждем окончания воспроизведения
        ALint state;
        do {
          alGetSourcei(source, AL_SOURCE_STATE, &state);
        } while (state == AL_PLAYING);

        alDeleteSources(1, &source);
      }

      // Очистка ресурсов
      ~AudioData() {
        if (buffer != 0) {
          alDeleteBuffers(1, &buffer);
        }
      }
    };
  }
}