# [0.3.0/latest]
## FIX
> Allocator, stream, (f/io)stream update:
- Немного подправлен файл WIP.h в модуле WIP

## ADD
> Rinegine::Kernel::LIST::push_front() has been added
- Добавлен метод Rinegine::Kernel::LIST::push_front()
> Allocator, stream, (f/io)stream update:
- Добавлены is_trivially_constructible, is_trivially_constructible, is_trivial, is_trivial_v, has_trivial_destructor и has_trivial_destructor_v. Вероятно временно расположены в именном пространстве Rinegine::Kernel::Traits. Аналоги из std, разницы по сути нет, добавленны для большей независимости от STD.
- Добавлены __addressof и addressof. Временно расположены в Rinegine::Kernel::Addres, добавлены для большей независимости от STD.
- Был добавлен MallocAllocator в Rinegine::Kernel. Обёртка над malloc для концепта Allocator. Сам концепт нужен для стандартизированния аллокаторов, дабы избежать непреднамеренных синтаксических ошибок в будущем.
- Был добавлен PoolAllocator, временный аллокатор добавленный для ускоренной работы типа LIST. Аллокатор не был досконально перепроверен, по этому возможны утечки. К тому же под капотом используется std::malloc. Так же добавлен Rinegine::Kernel::ALLOCATOR, пока что синоним PoolAllocator, дальнейшем будет заменён на другой, более продвинутый аллокатор.
- Был добавлен Rinegine::Kernel::NODE, простой шаблонный тип, только T data, NODE* next, NODE* prev. Нужен для LIST.
- Добавлен тип Rinegine::Kernel::LIST, аналог std::list, но быстрее. Были проведены тесты, но не исключены ошибки. Бенчмарк скорости работы можете посмотреть в README или специальном проекте с бенчмарками (см. README.md)
- Были добавлены заготовки для аллокатора, они пока безполезны
- Были добавлены потоки, а именно Rinegine::Kernel::Stream. Подробнее в документации, когда она будет готова.
- Были добавлены инструменты для работы с флагами. Нужен для удобства и читаемости. Rinegine::Kernel::Flags:: set(val,flag) ставит в val флаг flag, has(val,flag) проверяет наличие флага в значении, clear(val,flag) удаляет флаг из значения.
- Были заготовлены стандартные потоки ввода/вывода в консоль и в файл. Пример Rinegine::Kernel::Stream s = Rinegine::Kernel::Console::stdout_stream(); для работы с потоками вывода в консоль. Так же есть Rinegine::Kernel::Console:: stderr_stream,stderr_stream, stdin_stream. Для файлов Rinegine::Kernel::File::open(path,flag) (флаги enum Rinegine::Kernel::File::FILE_FLAG)

## REMOVED

## CHANGED
> Allocator, stream, (f/io)stream update:
- Изменена система CHANGELOG, теперь тут будут писаться все обновления без привязки ко времени до выхода стабильной версии фреймворка (Rinegine)
- На данный момент файл WIP.h устарел, и был отключён из сборки WIP модуля

# [0.3.0/09.02.26|10.54P]
## FIX
- Была ошибка при попытке скомпилировать Windows приложения не на NTFS диске
- Была исправлена очистка Raw_Pointer
- Была исправлена ошибка при компиляции Windows приложений, из-за необъявленного типа __uint8_t
- Была исправлена ошибка с неоднозначностью у функции itos и itosw
- Были исправлены прочие ошибки препятствующие сборке приложения для Windows

## ADD
- Был добавлен новый модуль - токенайзер. В разработке
- Было добавлено (возвращено) API для работы с файламии
- Была добавлена (возвращена) функция для запуска программ с Windows и добавлена возможность запуска программ с Linux (экспериментально)
- Начата работа над RawArray и Array (не закончено)
- Логи при ошибках в s_delete стали более информативными
- Добавлен новый тип - RawMap в модуль WIP 
- Были исправлены MainArguments, WMainArguments и AMainArguments

## REMOVED

## CHANGED
- Была изменена структура проекта. Теперь названия модулей (Kernel, WIP etc.) это не класс, а именное пространство
- Функции преобразования кодировок были вынесены в отдельный файл

# [0.3.0/30.01.26|05.04P]
## FIX

## ADD
- Был добавлен WIP модуль
- Был добавлен пример конфигурации сборки

## REMOVED

## CHANGED
- Аллокатор был добавлен в WIP модуль
- Аллокатор в Kernel модуле работает на malloc/calloc
- Файлы общих заголовков библиотек перенесены из Rinegine/include/ в Rinegine/include/cross

# [0.3.0/19.12.25|04:02P]
## FIX

## ADD
- Был добавлен файл CHANGELOG.md

## REMOVED

## CHANGED