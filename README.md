# Rinegine [<img alt="Rinegine Release" src="https://img.shields.io/badge/Rinegine-v0.2.1-green">](../../releases)  <!-- [<img alt="Rinegine WIP" src="https://img.shields.io/badge/Rinegine-v0.2.1 WIP-green">]() -->
Используется:  
[<img alt="GLFW site"       src="https://img.shields.io/badge/v3.4.0-red?logo=GLFW&logoColor=fc5a20&label=GLFW&labelColor=fc5a20&color=222222&link=https%3A%2F%2Fglfw.org%2F">](https://glfw.org)
[<img alt="FreeType site"   src="https://img.shields.io/badge/v2.13.2-red?logo=FreeType&logoColor=fc5a20&label=FreeType&labelColor=0c465d&color=222222&link=https%3A%2F%2Ffreetype.org%2F">](https://freetype.org)
[<img alt="MinGW site"      src="https://img.shields.io/badge/v13.2.0-red?logo=MinGW-w64&logoColor=fc5a20&label=MinGW-w64&labelColor=1f222a&color=222222&link=https://github.com/niXman/mingw-builds-binaries/releases">](https://github.com/niXman/mingw-builds-binaries/releases)
[<img alt="glad site"       src="https://img.shields.io/badge/v3.3.0-red?logoColor=fc5a20&label=GLAD&labelColor=aaaaaa&color=222222&link=https%3A%2F%2Fglad.dav1d.de%2F">](https://glad.dav1d.de)
[<img alt="OpenAL site"     src="https://img.shields.io/badge/v1.23.1-red?logoColor=fc5a20&label=(WIP)OpenAL&labelColor=30a1d9&color=222222&link=https://github.com/kcat/openal-soft">](https://github.com/kcat/openal-soft)
[<img alt="stb site"        src="https://img.shields.io/badge/v1.0.0-red?logoColor=fc5a20&label=STB&labelColor=000000&color=222222&link=https%3A%2F%2Fgithub.com%2Fnothings%2Fstb">](https://github.com/nothings/stb)
[<img alt="curl site"       src="https://img.shields.io/badge/v8.8.0-red?logoColor=fc5a20&label=(WIP)CURL&labelColor=111111&color=222222&link=https://curl.se/windows/">](https://curl.se/windows)

Связь с разработчиком:  
[<img alt="Telegram"        src="https://img.shields.io/badge/Rinemest-green?logo=Telegram&logoColor=ffffff&label=Telegram&labelColor=24A1DE&color=222222&link=https%3A%2F%2Ft.me%2Frinemest">](https://t.me/Rinemest)
[<img alt="Telegram"        src="https://img.shields.io/badge/Rinegine-green?logo=Telegram&logoColor=ffffff&label=Telegram&labelColor=24A1DE&color=444444&link=https://t.me/Rinegine">](https://t.me/Rinegine)

Rinegine - лёгкий и простой в освоении и полностью автономный (не требуется скачивать дополнительный софт для сборки программ) движок для программ и игр с 2-3 мерной графикой!

Всё самое интересное во вкладке [Wiki](https://github.com/Maximilian560/Rinegine/wiki)!  
Новости по движку и прочим проектам в моём [X(Twiter)](https://x.com/Rinemest)!

### Возможности (Информация устарела)
За этот долгий период движок оброс различными функциями и возможностями. Самое главное для меня это то, что сам движок не собран, его легко подключить к своему проекту и легко менять и добавлять то, что нужно. Возможно я потом всё-таки пересмотрю структуру движка и соберу его как библиотеку, но пока что меня всё устраивает.
Структура модульная. Модуль (папка) отвечает за что-то одно. Например, sound за звук, graphics не за графики, а за графику, https за соединение с интернетом и т.д. Так же в модулях есть подмодули (пока только в модуле графики). В общем можно самим всё увидеть, я лучше опишу функционал модулей.
#### Модули:
graphics - графика, в него включено всё, что связанно с графикой. Даже инициализация движка (она нужна, только чтобы проинициализировать библиотеки GLFW и FreeType).
 Этот модуль отвечает за создание окон (их можно создать несколько), за создание объектов таких как кнопки, свичи (переключатели), спрайты, фон, 3D объекты (кстати, для сохранения и чтения 3D объектов я сделал свой формат файла, или чтения файла, позже думаю перейти на другой, общераспространённый). Так же модуль создаёт игрока, управляет камерой, загружает шейдеры, проверяет нажатие кнопок, генерирует мир (WIP) и много чего ещё.

experemental - экспериментальные возможности, которые ещё проверяются и изменяются. В принципе там вполне работоспособные функции и классы, просто они часто изменяются, так что использовать их очень не рекомендуется (только если вы не собираетесь обновлять версию движка)
 Про этот модуль мало чего можно сказать, он часто изменяется.

addons - этот модуль не является как таковой частью движка. Он отвечает за сторонние аддоны и плагины, которые мало используются или разработаны другими людьми.
 Пока там только один "подмодуль" (плагин). Я его разработал для вечера встреч (я делал на своём движке программу для конкурса). В этом модуле только одна функция, она делит спрайт по сетке. Я думаю оно работает очень криво, но на сетке 3*3 без привязки к стороне окна работает должным образом.

other - не то, чтобы это был вообще модуль, это папка, в котором собраны библиотеки для других модулей, например GLFW, FreeType и прочие.

defined - самый главный модуль, если другие модули ещё можно отключить (вернее подключить, они по умолчанию отключены) то вот этот никак, там самое важное.
 В этом модуле определены константы, классы и функции, необходимые для работы других модулей, такие как массив, двух и трёх мерные матрицы, функции для чтения файлов. Там есть не настолько важный подмодуль, но я не знаю куда его деть, он отвечает за чтение специальных файлов локализации (кстати эти файлы тоже моего формата) и последующего перевода на нужные языки нужных текстов в программе. Пока только Русский и Английский, другие мне пока не нужны, я и не добавлял.

https и sound ещё в разработке, это в планах на будущее.

Вроде всё рассказал, работа над документацией ведётся, весь прогресс документации можете посмотреть во вкладке [Wiki](https://github.com/Maximilian560/Rinegine/wiki).
