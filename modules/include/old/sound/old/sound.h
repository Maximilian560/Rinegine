#pragma once

namespace RG {
  // namespace Sound {
  //   class Device {
  //     bool _init = false;
  //     ALCdevice* _device = nullptr;
  //   public:
  //     bool is_init() {
  //       return _init;
  //     }
  //     void init() {
  //       if (_init)return;
  //       _device = alcOpenDevice(nullptr);
  //       if (!_device) {
  //         RG_LOG_LOCK_ERROR("Failed to open audio device!");
  //         return;
  //       }
  //       _init = true;
  //     }
  //     ALCdevice* get_device() {
  //       return _device;
  //     }
  //     operator ALCdevice* () {
  //       return _device;
  //     }
  //     void shutdown() {
  //       // alcMakeContextCurrent(nullptr);
  //       // Закрываем устройство
  //       if (_device) {
  //         alcCloseDevice(_device);
  //         _device = nullptr;
  //       }
  //     }
  //     ~Device() {
  //       // alcMakeContextCurrent(nullptr);
  //       // Закрываем устройство
  //       if (_device) {
  //         alcCloseDevice(_device);
  //         _device = nullptr;
  //       }
  //     }
  //   };
  //   class Context {
  //     bool _init = false;
  //     Device _device_main;
  //     Device* _device = &_device_main;
  //     ALCcontext* _context = nullptr;
  //   public:
  //     void init() {
  //       if (_init)return;
  //       // Создаем контекст
  //       if (!_device->is_init()) _device->init();
  //       _context = alcCreateContext(*_device, nullptr);
  //       if (!_context) {
  //         RG_LOG_LOCK_ERROR("Failed to create audio context!");
  //         return;
  //       }
  //       // Делаем контекст текущим
  //       if (!alcMakeContextCurrent(_context)) {
  //         RG_LOG_LOCK_ERROR("Failed to make context current!");

  //         return;
  //       }
  //       _init = true;
  //     }
  //     void shutdown() {
  //       alcMakeContextCurrent(nullptr);

  //       // Удаляем созданный контекст
  //       if (_context) {
  //         alcDestroyContext(_context);
  //         _context = nullptr;
  //       }
  //       // Закрываем устройство
  //       _device->shutdown();
  //     }
  //     ~Context() {
  //       alcMakeContextCurrent(nullptr);

  //       // Удаляем созданный контекст
  //       if (_context) {
  //         alcDestroyContext(_context);
  //         _context = nullptr;
  //       }
  //     }
  //   };

  //   // class Engine {
  //   //   inline static bool _init = false;
  //   // public:
  //   //   static void init() {
  //   //     if (_init)return;
  //   //     *_device = alcOpenDevice(nullptr);
  //   //     if (!*_device) {
  //   //       fprintf(stderr, "Не удалось открыть аудио-устройство!");
  //   //       exit(1);
  //   //     }

  //   //     // Создаем контекст
  //   //     *_context = alcCreateContext(*_device, nullptr);
  //   //     if (!*_context) {
  //   //       fprintf(stderr, "Не удалось создать аудио-контекст!");
  //   //       alcCloseDevice(*_device);
  //   //       exit(1);
  //   //     }

  //   //     // Делаем контекст текущим
  //   //     if (!alcMakeContextCurrent(*_context)) {
  //   //       fprintf(stderr, "Не удалось сделать контекст текущим!");
  //   //       alcDestroyContext(*_context);
  //   //       alcCloseDevice(*_device);
  //   //       exit(1);
  //   //     }
  //   //     _init = true;
  //   //   }

  //   //   static void shutdown() {
  //   //     alcMakeContextCurrent(nullptr);

  //   //     // Удаляем созданный контекст
  //   //     if (*_context) {
  //   //       alcDestroyContext(*_context);
  //   //       *_context = nullptr;
  //   //     }

  //   //     // Закрываем устройство
  //   //     if (*_device) {
  //   //       alcCloseDevice(*_device);
  //   //       *_device = nullptr;
  //   //     }
  //   //   }
  //   //   ~Engine() {
  //   //     alcMakeContextCurrent(nullptr);

  //   //     // Удаляем созданный контекст
  //   //     if (*_context) {
  //   //       alcDestroyContext(*_context);
  //   //       *_context = nullptr;
  //   //     }

  //   //     // Закрываем устройство
  //   //     if (*_device) {
  //   //       alcCloseDevice(*_device);
  //   //       *_device = nullptr;
  //   //     }
  //   //   }
  //   // };
  // }




  namespace Sound {

    // AudioData loadWav(const string& filename) {
    //   AudioData wav;
    //   FILE* file = fopen(filename.c_str(), "rb");
    //   if (!file) {
    //     rg_cout << L"Не могу открыть WAV, лапки где-то потерял файл?\n";
    //     return wav;
    //   }

    //   // Читаем заголовок WAV
    //   char header[44];
    //   fread(header, 1, 44, file);

    //   // Проверяем, что это WAV (RIFF)
    //   if (strncmp(header, "RIFF", 4) != 0 || strncmp(header + 8, "WAVE", 4) != 0) {
    //     rg_cout << L"Это не WAV, ты мне подсунул что-то странное!\n";
    //     fclose(file);
    //     return wav;
    //   }

    //   // Извлекаем параметры
    //   wav.channels = *(short*)(header + 22);
    //   wav.sampleRate = *(int*)(header + 24);
    //   wav.bitsPerSample = *(short*)(header + 34);

    //   // Ищем чанк data
    //   char chunkId[4];
    //   int chunkSize;
    //   fseek(file, 12, SEEK_SET); // Пропускаем RIFF/WAVE
    //   while (fread(chunkId, 1, 4, file) == 4) {
    //     fread(&chunkSize, 4, 1, file);
    //     if (strncmp(chunkId, "data", 4) == 0) {
    //       wav.size = chunkSize;
    //       wav.data = (unsigned char*)malloc(wav.size);
    //       fread(wav.data, 1, wav.size, file);
    //       break;
    //     }
    //     fseek(file, chunkSize, SEEK_CUR); // Пропускаем ненужный чанк
    //   }

    //   if (!wav.data) {
    //     rg_cout << L"Чанк data не найден, что за WAV такой кривой?\n";
    //     fclose(file);
    //     return wav;
    //   }

    //   fclose(file);
    //   rg_cout << L"WAV загружен: " << wav.size << L" байт, " << wav.sampleRate << L" Гц, " << wav.channels << L" канала, " << wav.bitsPerSample << L" бит\n";
    //   return wav;
    // }

    // AudioData loadWav(const string& filename) {
    //   AudioData wav;

    //   // Открываем файл в бинарном режиме
    //   ifstream file(filename, ios::binary);
    //   if (!file.is_open()) {
    //     RG_LOG_LOCK_CRITICAL("Failed to open file");
    //   }

    //   // Проверяем размер файла
    //   file.seekg(0, ios::end);
    //   long fileSize = file.tellg();
    //   file.seekg(0, ios::beg);

    //   char header[44];
    //   file.read(header, 44);
    //   if (file.gcount() != 44) {
    //     RG_LOG_LOCK_CRITICAL("Failed to read WAV header");
    //   }

    //   // Проверяем, что это WAV (RIFF)
    //   if (strncmp(header, "RIFF", 4) != 0 || strncmp(header + 8, "WAVE", 4) != 0) {
    //     RG_LOG_LOCK_CRITICAL("Unsupported file format");
    //   }

    //   // Извлекаем параметры
    //   wav.channels = *(short*)(header + 22);
    //   wav.sampleRate = *(int*)(header + 24);
    //   wav.bitsPerSample = *(short*)(header + 34);

    //   // Проверяем параметры
    //   if (wav.channels <= 0 || wav.sampleRate <= 0 || wav.bitsPerSample <= 0) {
    //     RG_LOG_LOCK_CRITICAL("Invalid WAV parameters: channels=" + to_string(wav.channels)
    //       + ", sampleRate=" + to_string(wav.sampleRate)
    //       + ", bitsPerSample=" + to_string(wav.bitsPerSample));
    //   }

    //   // Ищем чанк data
    //   char chunkId[4];
    //   int chunkSize;
    //   file.seekg(12, ios::beg); // Пропускаем RIFF/WAVE
    //   while (file.read(chunkId, 4)) {
    //     file.read(reinterpret_cast<char*>(&chunkSize), 4);
    //     if (file.gcount() != 4) {
    //       RG_LOG_LOCK_CRITICAL("Failed to read chunk size, file is damaged?");
    //       return wav;
    //     }
    //     if (strncmp(chunkId, "data", 4) == 0) {
    //       wav.size = chunkSize;
    //       if (wav.size <= 0) {
    //         RG_LOG_LOCK_CRITICAL("WAV data size (" + to_string(wav.size) + ") is invalid!");

    //       }
    //       if (wav.size > fileSize - 44) {
    //         RG_LOG_LOCK_CRITICAL("WAV data size (" + to_string(wav.size) + ") exceeds file size (" + to_string(fileSize) + ")!");

    //       }

    //       // Выделяем память через вектор
    //       wav.data.resize(wav.size);
    //       file.read(reinterpret_cast<char*>(wav.data.data()), wav.size);
    //       if (file.gcount() != wav.size) {
    //         RG_LOG_LOCK_CRITICAL("Failed to read WAV data, read " + to_string(file.gcount()) + " bytes out of " + to_string(wav.size));
    //         wav.data.clear();
    //         wav.size = 0;

    //       }
    //       break;
    //     }
    //     file.seekg(chunkSize, ios::cur); // Пропускаем ненужный чанк
    //   }

    //   if (wav.data.empty()) {
    //     RG_LOG_LOCK_CRITICAL("Chunk 'data' not found, what kind of WAV is this?");
    //   }

    //   return wav;
    // }
    class Speaker {
      string _path;
      AudioData wav;
    public:
      Speaker(string path) {
        _path = path;
        wav = loadWav(path); //
      }
      void play() {
        if (wav.data.empty() || wav.size <= 0 || wav.sampleRate <= 0) {
          RG_LOG_LOCK_CRITICAL("Invalid WAV data: data=" + to_string((uintptr_t)wav.data.data()) + ", size=" + to_string(wav.size) + ", sampleRate=" + to_string(wav.sampleRate));
        }

        // Формат для OpenAL
        ALenum format = 0;
        if (wav.channels == 1 && wav.bitsPerSample == 8) format = AL_FORMAT_MONO8;
        else if (wav.channels == 1 && wav.bitsPerSample == 16) format = AL_FORMAT_MONO16;
        else if (wav.channels == 2 && wav.bitsPerSample == 8) format = AL_FORMAT_STEREO8;
        else if (wav.channels == 2 && wav.bitsPerSample == 16) format = AL_FORMAT_STEREO16;
        else {
          RG_LOG_LOCK_CRITICAL("Unsupported WAV format: " + to_string(wav.channels) + " channels, " + to_string(wav.bitsPerSample) + " bits");
          return;
        }

        // Создаём буфер и загружаем данные
        ALuint buffer;
        alGenBuffers(1, &buffer);
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error creating buffer: " + to_string(error));
          return;
        }

        // Отладочный вывод перед alBufferData
        rg_cout << L"Before alBufferData: buffer=" << buffer
          << L", format=" << format
          << L", data=" << (void*)wav.data.data()
          << L", size=" << wav.size
          << L", sampleRate=" << wav.sampleRate << L"\n";

        alBufferData(buffer, format, wav.data.data(), wav.size, wav.sampleRate);
        error = alGetError();
        if (error != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error loading data into buffer: " + to_string(error));
          alDeleteBuffers(1, &buffer);
          return;
        }

        // Создаём источник звука
        ALuint source;
        alGenSources(1, &source);
        error = alGetError();
        if (error != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error creating source: " + to_string(error));
          alDeleteBuffers(1, &buffer);
          return;
        }

        // Привязываем буфер к источнику
        alSourcei(source, AL_BUFFER, buffer);
        error = alGetError();
        if (error != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error binding buffer: " + to_string(error));
          alDeleteSources(1, &source);
          alDeleteBuffers(1, &buffer);
          return;
        }

        // Устанавливаем громкость (1.0 - максимум)
        alSourcef(source, AL_GAIN, 1.0f);
        error = alGetError();
        if (error != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error setting volume: " + to_string(error));
          alDeleteSources(1, &source);
          alDeleteBuffers(1, &buffer);
          return;
        }

        alSourcePlay(source);
        error = alGetError();
        if (error != AL_NO_ERROR) {
          RG_LOG_LOCK_CRITICAL("Error playing sound: " + to_string(error));
          alDeleteSources(1, &source);
          alDeleteBuffers(1, &buffer);
          return;
        }

        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
          RG_LOG_LOCK_CRITICAL("Source is not playing");
        }

        int duration = wav.size / (wav.sampleRate * wav.channels * (wav.bitsPerSample / 8));
        Sleep(duration * 1000);

        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
      }
    };
  }

  /* * * * * * * * * * * * * * * */

    // namespace Sound {
    //   struct AudioData {
    //     int channels;    // 1 - моно, 2 - стерео
    //     int sampleRate;  // Частота, например, 44100
    //     int bitsPerSample; // Обычно 16
    //     RG_Array<unsigned char> data; // Сырые аудиоданные (вектор вместо указателя)
    //     int size;        // Размер данных в байтах

    //     AudioData() : channels(0), sampleRate(0), bitsPerSample(0), size(0) {}
    //   };

    //   AudioData loadWav(const string& filename) {
    //     AudioData wav;

    //     // Открываем файл в бинарном режиме
    //     ifstream file(filename, ios::binary);
    //     if (!file.is_open()) {
    //       rg_cout << L"Не могу открыть WAV, лапки где-то потерял файл?\n";
    //       return wav;
    //     }

    //     // Проверяем размер файла
    //     file.seekg(0, ios::end);
    //     long fileSize = file.tellg();
    //     file.seekg(0, ios::beg);
    //     rg_cout << L"Размер файла: " << to_wstring(fileSize) << L" байт\n";

    //     // Читаем заголовок WAV (44 байта)
    //     char header[44];
    //     file.read(header, 44);
    //     if (file.gcount() != 44) {
    //       rg_cout << L"Не удалось прочитать заголовок WAV, файл слишком короткий?\n";
    //       return wav;
    //     }

    //     // Проверяем, что это WAV (RIFF)
    //     if (strncmp(header, "RIFF", 4) != 0 || strncmp(header + 8, "WAVE", 4) != 0) {
    //       rg_cout << L"Это не WAV, ты мне подсунул что-то странное!\n";
    //       return wav;
    //     }

    //     // Извлекаем параметры
    //     wav.channels = *(short*)(header + 22);
    //     wav.sampleRate = *(int*)(header + 24);
    //     wav.bitsPerSample = *(short*)(header + 34);

    //     // Проверяем параметры
    //     if (wav.channels <= 0 || wav.sampleRate <= 0 || wav.bitsPerSample <= 0) {
    //       rg_cout << L"Некорректные параметры WAV: каналы=" << to_wstring(wav.channels)
    //         << L", частота=" << to_wstring(wav.sampleRate)
    //         << L", бит=" << to_wstring(wav.bitsPerSample) << L"\n";
    //       return wav;
    //     }

    //     // Ищем чанк data
    //     char chunkId[4];
    //     int chunkSize;
    //     file.seekg(12, ios::beg); // Пропускаем RIFF/WAVE
    //     while (file.read(chunkId, 4)) {
    //       file.read(reinterpret_cast<char*>(&chunkSize), 4);
    //       if (file.gcount() != 4) {
    //         rg_cout << L"Не удалось прочитать размер чанка, файл повреждён?\n";
    //         return wav;
    //       }
    //       if (strncmp(chunkId, "data", 4) == 0) {
    //         wav.size = chunkSize;
    //         if (wav.size <= 0) {
    //           rg_cout << L"Размер данных WAV некорректен: " << to_wstring(wav.size) << L"\n";
    //           return wav;
    //         }
    //         if (wav.size > fileSize - 44) {
    //           rg_cout << L"Размер данных WAV (" << to_wstring(wav.size) << L") превышает размер файла (" << to_wstring(fileSize) << L")!\n";
    //           return wav;
    //         }

    //         // Выделяем память через вектор
    //         wav.data.resize(wav.size);
    //         file.read(reinterpret_cast<char*>(wav.data.data()), wav.size);
    //         if (file.gcount() != wav.size) {
    //           rg_cout << L"Не удалось прочитать данные WAV, прочитано " << to_wstring(file.gcount()) << L" байт из " << to_wstring(wav.size) << L"\n";
    //           wav.data.clear();
    //           wav.size = 0;
    //           return wav;
    //         }
    //         break;
    //       }
    //       file.seekg(chunkSize, ios::cur); // Пропускаем ненужный чанк
    //     }

    //     if (wav.data.empty()) {
    //       rg_cout << L"Чанк data не найден, что за WAV такой кривой?\n";
    //       return wav;
    //     }

    //     rg_cout << L"WAV загружен: " << to_wstring(wav.size) << L" байт, " << to_wstring(wav.sampleRate) << L" Гц, "
    //       << to_wstring(wav.channels) << L" канала, " << to_wstring(wav.bitsPerSample) << L" бит\n";
    //     return wav;
    //   }

    //   class Speaker {
    //     string _path;
    //     AudioData wav;


    //   public:
    //     Speaker(string path) {
    //       _path = path;

    //       // Инициализация OpenAL


    //       // Загружаем WAV
    //       wav = loadWav(path);
    //       // Проверяем, что данные валидны
    //       if (wav.data.empty() || wav.size <= 0) {
    //         rg_cout << L"Данные WAV некорректны: data=" << (void*)wav.data.data()
    //           << L", size=" << to_wstring(wav.size) << L"\n";
    //       } else {
    //         rg_cout << L"Указатель на данные: ";// << (void*)wav.data.data()
    //         // wav.data.print();
    //         rg_cout << L", размер: " << to_wstring(wav.size) << L"\n";
    //         // Безопасно проверяем первые 4 байта
    //         unsigned char testBytes[4] = { 0 };
    //         if (wav.size >= 4) {
    //           memcpy(testBytes, wav.data.data(), 4);
    //           rg_cout << L"Первые 4 байта данных: ";
    //           for (int i = 0; i < 4; i++) {
    //             rg_cout << to_wstring((int)testBytes[i]) << L" ";
    //           }
    //           rg_cout << L"\n";
    //         } else {
    //           rg_cout << L"Недостаточно данных для проверки первых 4 байт\n";
    //         }
    //       }
    //       rg_cout << L"Speaker loaded: " << to_wstring(wav.size) << L" байт, " << to_wstring(wav.sampleRate) << L" Гц, " << to_wstring(wav.channels) << L" канала, " << to_wstring(wav.bitsPerSample) << L" бит\n";
    //     }


    //     void play() {
    //       if (wav.data.empty() || wav.size <= 0 || wav.sampleRate <= 0) {
    //         rg_cout << L"Некорректные данные WAV: data=" << (void*)wav.data.data()
    //           << L", size=" << to_wstring(wav.size) << L", sampleRate=" << to_wstring(wav.sampleRate) << L"\n";
    //         return;
    //       }

    //       // Формат для OpenAL
    //       ALenum format = 0;
    //       if (wav.channels == 1 && wav.bitsPerSample == 8) format = AL_FORMAT_MONO8;
    //       else if (wav.channels == 1 && wav.bitsPerSample == 16) format = AL_FORMAT_MONO16;
    //       else if (wav.channels == 2 && wav.bitsPerSample == 8) format = AL_FORMAT_STEREO8;
    //       else if (wav.channels == 2 && wav.bitsPerSample == 16) format = AL_FORMAT_STEREO16;
    //       else {
    //         RG_LOG_LOCK_CRITICAL(L"Формат WAV не поддерживается: " + to_wstring(wav.channels) + L" канала, " + to_wstring(wav.bitsPerSample) + L" бит");
    //         return;
    //       }

    //       // Создаём буфер и загружаем данные
    //       ALuint buffer;
    //       alGenBuffers(1, &buffer);
    //       ALenum error = alGetError();
    //       if (error != AL_NO_ERROR) {
    //         RG_LOG_LOCK_CRITICAL(L"Ошибка при создании буфера: " + to_wstring(error));
    //         return;
    //       }

    //       // Отладочный вывод перед alBufferData
    //       rg_cout << L"Перед alBufferData: buffer=" << to_wstring(buffer)
    //         << L", format=" << to_wstring(format)
    //         << L", data=" << (void*)wav.data.data()
    //         << L", size=" << to_wstring(wav.size)
    //         << L", sampleRate=" << to_wstring(wav.sampleRate) << L"\n";

    //       // Временно уменьшаем размер буфера для теста
    //       int testSize = wav.size > 1024 * 1024 ? 1024 * 1024 : wav.size; // Ограничиваем 1 МБ
    //       rg_cout << L"Тестовый размер буфера: " << to_wstring(testSize) << L" байт\n";
    //       alBufferData(buffer, format, wav.data.data(), testSize, wav.sampleRate);
    //       error = alGetError();
    //       if (error != AL_NO_ERROR) {
    //         RG_LOG_LOCK_CRITICAL(L"Ошибка при загрузке данных в буфер: " + to_wstring(error));
    //         alDeleteBuffers(1, &buffer);
    //         return;
    //       }

    //       // Создаём источник звука
    //       ALuint source;
    //       alGenSources(1, &source);
    //       error = alGetError();
    //       if (error != AL_NO_ERROR) {
    //         RG_LOG_LOCK_CRITICAL(L"Ошибка при создании источника: " + to_wstring(error));
    //         alDeleteBuffers(1, &buffer);
    //         return;
    //       }

    //       // Привязываем буфер к источнику
    //       alSourcei(source, AL_BUFFER, buffer);
    //       error = alGetError();
    //       if (error != AL_NO_ERROR) {
    //         RG_LOG_LOCK_CRITICAL(L"Ошибка при привязке буфера: " + to_wstring(error));
    //         alDeleteSources(1, &source);
    //         alDeleteBuffers(1, &buffer);
    //         return;
    //       }

    //       // Устанавливаем громкость (1.0 - максимум)
    //       alSourcef(source, AL_GAIN, 1.0f);
    //       error = alGetError();
    //       if (error != AL_NO_ERROR) {
    //         RG_LOG_LOCK_CRITICAL(L"Ошибка при установке громкости: " + to_wstring(error));
    //         alDeleteSources(1, &source);
    //         alDeleteBuffers(1, &buffer);
    //         return;
    //       }

    //       // Воспроизводим
    //       alSourcePlay(source);
    //       error = alGetError();
    //       if (error != AL_NO_ERROR) {
    //         RG_LOG_LOCK_CRITICAL(L"Ошибка при воспроизведении: " + to_wstring(error));
    //         alDeleteSources(1, &source);
    //         alDeleteBuffers(1, &buffer);
    //         return;
    //       }

    //       rg_cout << L"Играю твой WAV\n";

    //       // Проверяем состояние воспроизведения
    //       ALint state;
    //       alGetSourcei(source, AL_SOURCE_STATE, &state);
    //       if (state != AL_PLAYING) {
    //         RG_LOG_LOCK_CRITICAL(L"Источник не воспроизводит");
    //       }

    //       // Ждём, пока играет
    //       int duration = testSize / (wav.sampleRate * wav.channels * (wav.bitsPerSample / 8));
    //       rg_cout << L"Длительность (тестового фрагмента): " << to_wstring(duration) << L" секунд\n";
    //       Sleep(duration * 1000);

    //       // Очистка
    //       alDeleteSources(1, &source);
    //       alDeleteBuffers(1, &buffer);
    //     }
    //   };
    // }
}