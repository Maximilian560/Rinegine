#pragma once 
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/types/random"

static uint64_t wstring_to_seed(const std::wstring& wstr) {
    uint64_t seed = 0;
    for (wchar_t wc : wstr) {
        seed = seed * 31 + static_cast<uint64_t>(wc);  // Простое хеширование с использованием широких символов
    }
    return seed;
}

//uint64_t RG_SEED = 0;

class RG_CRand {
private:
    uint64_t a = 6364136223846793005, c = 1, m = UINT64_MAX;
    uint64_t seed = 0;
    bool _init = false;

public:
    // Конструктор с параметрами генератора и начальным значением
    RG_CRand() {};
    RG_CRand(uint64_t seed) { this->seed = seed; _init = true; }
    void init(uint64_t seed) { this->seed = seed; _init = true; }
    // Метод проверки инициализации генератора
    bool is_init() { return _init; }
    // Метод генерации случайного числа (равномерно от 0 до UINT64_MAX)
    uint64_t rand() {
        seed = (a * seed + c) % m;
        return seed;
    }
};
int set_seed() {
    srand(time(0));
    return rand();
}

RG_CRand RG_RAND;

uint64_t RG_Rand() {
    if (!RG_RAND.is_init())RG_RAND.init(rand());
    return RG_RAND.rand();
}


namespace RG {
    // Глобальный сид
    uint64_t Seed = 123456789; // Можно установить любое значение

    // Генератор случайных чисел (линейный конгруэнтный метод)
    uint64_t Rand() {
        const uint64_t a = 6364136223846793005; // Мультипликатор
        const uint64_t c = 1;                  // Инкремент
        Seed = a * Seed + c;
        return Seed;
    }

    // Генерация числа в диапазоне [min, max)
    double RandRange(double min, double max) {
        if(min>=max)return max;
        uint64_t randValue = Rand();
        double normalized = (randValue % 1000000) / 1000000.0; // Нормализовать в [0, 1)
        double out=min + normalized * (max - min);
        if(out>max||out<min)RG_LOG_LOCK_CRITICAL("RandRange out of range, min:" + to_string(min) + ", max:" + to_string(max) + ", out:" + to_string(out));
        return out;
    }
}