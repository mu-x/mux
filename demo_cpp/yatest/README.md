# YaTest - client-server most common calculator

Client-server application, allows find out 10 most common words in ".hpp" files
by the directory (recursively). Server application serves clients in separate
threads (one per client) and performs file parsing in fixed amount of working
threads.

---

## Requrements

* Ubuntu 12.04+ (tested on docker)
* GCC 4.6.3+ (g++, pthread etc)
* Boost 1.48.0+ (system, filesystem, asio)
* CMake 2.8.7+ (for gtest manual compile only)
* Google Test 1.6.0+ (for unit tests only)

---

## Instructions

* Install deps on Ubuntu:
```
  > sudo apt-get update
  > sudo apt-get install build-essential cmake libgtest-dev \
      libboost-system-dev libboost-filesystem-dev libasio-dev
```

* Build GTest shared library:
```
  > cd /usr/src/gtest
  > sudo cmake CMakeLists.txt
  > sudo make
  > sudo mv libg* /usr/lib/
```

* Build & run test:
```
  > ./build.sh          # build client and server applications
  > ./build.sh test     # build apps with tests and run tests

  # Environment variables:
  # CXX   -- compiler (default g++), example: CXX=clang++ ./build.sh
  # RUN   -- run command (default time), example: RUN=valgrind ./build.sh test
  # FLAGS -- extra compiler flags, example: EXTRA=-DDEBUG ./build.sh
```

* Run applications:
```
  > ./run.sh server [WORK_THREAD_COUNT] [PORT]
  > ./run.sh client DIRECTORY [HOST] [PORT]
```

---

## Original Task

Необходимо написать многопоточное серверное приложение, которое индексирует
файлы внутри каталога.

1. Приложение должно получать пакет по TCP, в котором содержится путь до
   директории.

2. Для каждого клиента должен быть выделенный поток, который отвечает за поиск
   всех плюсовых заголовков (файлов, заканчивающихся на '.hpp') внутри
   директории, включая все поддиректории.

3. Когда текстовый файл найден, этот поток должен передать файл на индексацию
   рабочему потоку и продолжить поиск.

4. Пул рабочих потоков, должен быть фиксированного размера и индексировать
   файлы для всех клиентов

5. Рабочий поток получает текстовый файл и считывает его словами. Словом
   считается любой набор символов [a-zA-Z0-9_]*.

   Все остальные символы считаются разделителями. Для каждого слова поток
   считывает количество его вхождений и увеличивает счетчик для этого слова на
   единицу каждый раз.

6. Таблица, в которую записываются данные о частоте попадания слов, у каждого
   из клиентов своя и хранится в памяти. Слова должны храниться в ней
   независимо от регистра.

7. Когда поиск текстовых файлов будет полностью закончен, программа должна
   отправить клиенту 10 самых частотных слов.

То есть основная задача программы - отправить клиенту 10 самых популярных слов,
которые встречаются в директории, включая обработку файлов в глубину по всем
поддиректориям.

Программа должна быть написана на С++ и собираться на Ubuntu precise/trusty.
Ты можешь использовать Boost и любые другие библиотеки на твое усмотрение.

Протокол должен включать только два пакета: request, содержащий путь и response,
который передает 10 самых популярных слов, формат пакетов остается на твоё усмотрение.

Необязательно, но будут плюсом документация и тесты.

