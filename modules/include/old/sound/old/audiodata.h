#pragma once

namespace RG {
  namespace Sound {

    struct AudioData {
      int channels;
      int sampleRate;
      int bitsPerSample;
      RG_Array<short> data;
      int size;

      AudioData() : channels(0), sampleRate(0), bitsPerSample(0), size(0) {}
    };


    //   AudioData loadWithFFmpeg(const string& filename) {
    //     AudioData audio;

    //     // Инициализация FFmpeg
    //     AVFormatContext* formatContext = nullptr;
    //     if (avformat_open_input(&formatContext, filename.c_str(), nullptr, nullptr) < 0) {
    //       RG_LOG_LOCK_ERROR("Cannot open file: " + filename);
    //       return audio;
    //     }

    //     // Находим информацию о потоке
    //     if (avformat_find_stream_info(formatContext, nullptr) < 0) {
    //       RG_LOG_LOCK_ERROR("Cannot find stream info");
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     // Ищем аудиопоток
    //     int audioStreamIndex = -1;
    //     for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
    //       if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
    //         audioStreamIndex = i;
    //         break;
    //       }
    //     }
    //     if (audioStreamIndex == -1) {
    //       RG_LOG_LOCK_ERROR("Audio stream not found");
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     // Получаем параметры потока
    //     AVCodecParameters* codecPar = formatContext->streams[audioStreamIndex]->codecpar;
    //     const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
    //     if (!codec) {
    //       RG_LOG_LOCK_ERROR("Decoder not found");
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     // Создаём контекст декодера
    //     AVCodecContext* codecContext = avcodec_alloc_context3(codec);
    //     if (!codecContext) {
    //       RG_LOG_LOCK_ERROR("Cannot allocate codec context");
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     if (avcodec_parameters_to_context(codecContext, codecPar) < 0) {
    //       RG_LOG_LOCK_ERROR("Cannot copy codec parameters");
    //       avcodec_free_context(&codecContext);
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     if (avcodec_open2(codecContext, codec, nullptr) < 0) {
    //       RG_LOG_LOCK_ERROR("Cannot open codec");
    //       avcodec_free_context(&codecContext);
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     // Извлекаем параметры
    //     audio.channels = codecContext->channels;
    //     audio.sampleRate = codecContext->sample_rate;
    //     audio.bitsPerSample = 16; // Мы будем конвертировать всё в 16 бит

    //     // Инициализируем SwrContext для конвертации в 16 бит (AV_SAMPLE_FMT_S16)
    //     SwrContext* swrContext = swr_alloc_set_opts(nullptr,
    //       av_get_default_channel_layout(audio.channels), AV_SAMPLE_FMT_S16, audio.sampleRate,
    //       av_get_default_channel_layout(codecContext->channels), codecContext->sample_fmt, codecContext->sample_rate,
    //       0, nullptr);
    //     if (!swrContext || swr_init(swrContext) < 0) {
    //       RG_LOG_LOCK_ERROR("Cannot initialize SwrContext");
    //       swr_free(&swrContext);
    //       avcodec_free_context(&codecContext);
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     // Читаем и декодируем аудио
    //     AVPacket packet;
    //     AVFrame* frame = av_frame_alloc();
    //     if (!frame) {
    //       RG_LOG_LOCK_ERROR("Cannot allocate frame");
    //       swr_free(&swrContext);
    //       avcodec_free_context(&codecContext);
    //       avformat_close_input(&formatContext);
    //       return audio;
    //     }

    //     RG_Array<short> pcmData;
    //     while (av_read_frame(formatContext, &packet) >= 0) {
    //       if (packet.stream_index == audioStreamIndex) {
    //         if (avcodec_send_packet(codecContext, &packet) >= 0) {
    //           while (avcodec_receive_frame(codecContext, frame) >= 0) {
    //             // Конвертируем в 16 бит
    //             int dstSamples = av_rescale_rnd(swr_get_delay(swrContext, audio.sampleRate) + frame->nb_samples, audio.sampleRate, audio.sampleRate, AV_ROUND_UP);
    //             RG_Array<short> tempBuffer;
    //             tempBuffer.resize(dstSamples * audio.channels);

    //             const uint8_t* inData[1] = { (uint8_t*)frame->data[0] };
    //             uint8_t* outData[1] = { (uint8_t*)tempBuffer.data() };
    //             int samplesConverted = swr_convert(swrContext, outData, dstSamples, inData, frame->nb_samples);

    //             // Добавляем конвертированные данные в pcmData
    //             int currentSize = pcmData.size();
    //             pcmData.resize(currentSize + samplesConverted * audio.channels);
    //             memcpy(pcmData.data() + currentSize, tempBuffer.data(), samplesConverted * audio.channels * sizeof(short));
    //           }
    //         }
    //       }
    //       av_packet_unref(&packet);
    //     }

    //     // Заполняем AudioData
    //     audio.data = move(pcmData);
    //     audio.size = audio.data.size() * sizeof(short);

    //     // Очистка
    //     av_frame_free(&frame);
    //     swr_free(&swrContext);
    //     avcodec_free_context(&codecContext);
    //     avformat_close_input(&formatContext);

    //     RG_LOG_LOCK_ERROR("File loaded: " + to_string(audio.size) + " bytes, "
    //       + to_string(audio.sampleRate) + " Hz, "
    //       + to_string(audio.channels) + " channels, "
    //       + to_string(audio.bitsPerSample) + " bits");
    //     return audio;
    //   }

    //   // Загрузчики для каждого формата
    //   AudioData loadMp3(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadWav(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadFlac(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadAac(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadOgg(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadAlac(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadAiff(const string& filename) {
    //     return loadWithFFmpeg(filename);
    //   }

    //   AudioData loadVac(const string& filename) {
    //     AudioData audio = loadWithFFmpeg(filename);
    //     if (audio.size == 0) {
    //       RG_LOG_LOCK_ERROR("VAC cannot be loaded through FFmpeg, this is probably a proprietary format");
    //     }
    //     return audio;
    //   }  
    // }
    AudioData loadWithFFmpeg(string filename) {
      AudioData audio;

      // Инициализация FFmpeg
      AVFormatContext* formatContext = nullptr;
      if (avformat_open_input(&formatContext, filename.c_str(), nullptr, nullptr) < 0) {
        rg_cout << L"Не могу открыть файл: " << filename.c_str() << L"\n";
        return audio;
      }

      // Находим информацию о потоке
      if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        rg_cout << L"Не могу найти информацию о потоке\n";
        avformat_close_input(&formatContext);
        return audio;
      }

      // Ищем аудиопоток
      int audioStreamIndex = -1;
      for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
          audioStreamIndex = i;
          break;
        }
      }
      if (audioStreamIndex == -1) {
        rg_cout << L"Аудиопоток не найден\n";
        avformat_close_input(&formatContext);
        return audio;
      }

      // Получаем параметры потока
      AVCodecParameters* codecPar = formatContext->streams[audioStreamIndex]->codecpar;
      const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
      if (!codec) {
        rg_cout << L"Декодер не найден\n";
        avformat_close_input(&formatContext);
        return audio;
      }

      // Создаём контекст декодера
      AVCodecContext* codecContext = avcodec_alloc_context3(codec);
      if (!codecContext) {
        rg_cout << L"Не могу выделить контекст декодера\n";
        avformat_close_input(&formatContext);
        return audio;
      }

      if (avcodec_parameters_to_context(codecContext, codecPar) < 0) {
        rg_cout << L"Не могу скопировать параметры кодека\n";
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return audio;
      }

      if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        rg_cout << L"Не могу открыть кодек\n";
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return audio;
      }

      // Извлекаем параметры
      audio.channels = codecPar->ch_layout.nb_channels; // Используем ch_layout.nb_channels вместо channels
      audio.sampleRate = codecPar->sample_rate;
      audio.bitsPerSample = 16; // Мы будем конвертировать всё в 16 бит

      // Настраиваем выходной формат для SwrContext
      AVChannelLayout outChannelLayout;
      av_channel_layout_default(&outChannelLayout, audio.channels); // Создаём стандартный layout для выходных каналов

      // Инициализируем SwrContext для конвертации в 16 бит (AV_SAMPLE_FMT_S16)
      SwrContext* swrContext = nullptr;
      if (swr_alloc_set_opts2(&swrContext,
        &outChannelLayout, AV_SAMPLE_FMT_S16, audio.sampleRate,
        &codecContext->ch_layout, codecContext->sample_fmt, codecContext->sample_rate,
        0, nullptr) < 0) {
        rg_cout << L"Не могу инициализировать SwrContext\n";
        av_channel_layout_uninit(&outChannelLayout);
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return audio;
      }

      if (swr_init(swrContext) < 0) {
        rg_cout << L"Не могу инициализировать SwrContext\n";
        swr_free(&swrContext);
        av_channel_layout_uninit(&outChannelLayout);
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return audio;
      }

      // Читаем и декодируем аудио
      AVPacket packet;
      av_init_packet(&packet);
      packet.data = nullptr;
      packet.size = 0;

      AVFrame* frame = av_frame_alloc();
      if (!frame) {
        rg_cout << L"Не могу выделить фрейм\n";
        swr_free(&swrContext);
        av_channel_layout_uninit(&outChannelLayout);
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return audio;
      }

      RG_Array<short> pcmData;
      while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == audioStreamIndex) {
          if (avcodec_send_packet(codecContext, &packet) >= 0) {
            while (avcodec_receive_frame(codecContext, frame) >= 0) {
              // Конвертируем в 16 бит
              int dstSamples = av_rescale_rnd(swr_get_delay(swrContext, audio.sampleRate) + frame->nb_samples, audio.sampleRate, audio.sampleRate, AV_ROUND_UP);
              RG_Array<short> tempBuffer;
              tempBuffer.resize(dstSamples * audio.channels);

              const uint8_t* inData[1] = { (uint8_t*)frame->data[0] };
              uint8_t* outData[1] = { (uint8_t*)tempBuffer.data() };
              int samplesConverted = swr_convert(swrContext, outData, dstSamples, inData, frame->nb_samples);

              // Добавляем конвертированные данные в pcmData
              int currentSize = pcmData.size();
              pcmData.resize(currentSize + samplesConverted * audio.channels);
              memcpy(pcmData.data() + currentSize, tempBuffer.data(), samplesConverted * audio.channels * sizeof(short));
            }
          }
        }
        av_packet_unref(&packet);
      }

      // Заполняем AudioData
      audio.data = std::move(pcmData);
      audio.size = audio.data.size() * sizeof(short);

      // Очистка
      av_frame_free(&frame);
      swr_free(&swrContext);
      av_channel_layout_uninit(&outChannelLayout);
      avcodec_free_context(&codecContext);
      avformat_close_input(&formatContext);

      rg_cout << L"Файл загружен: " << std::to_wstring(audio.size) << L" байт, "
        << std::to_wstring(audio.sampleRate) << L" Гц, "
        << std::to_wstring(audio.channels) << L" канала, "
        << std::to_wstring(audio.bitsPerSample) << L" бит\n";
      return audio;
    }

    // Загрузчики для каждого формата
    AudioData loadMp3(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadWav(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadFlac(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadAac(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadOgg(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadAlac(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadAiff(const std::string& filename) {
      return loadWithFFmpeg(filename);
    }

    AudioData loadVac(const std::string& filename) {
      AudioData audio = loadWithFFmpeg(filename);
      if (audio.size == 0) {
        rg_cout << L"VAC не удалось загрузить через FFmpeg, возможно, это проприетарный формат\n";
      }
      return audio;
    }
  }

}