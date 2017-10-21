# Markov Chane based text builder

## Dependency

* CLang with C++14 (tested on 4.0.0-1ubuntu1~16.04.2)
* Boost System (tested on 1.58.0+dfsg-5ubuntu3.1)
* QT for UTF8 support (tested on 5.5.1-2ubuntu6)

Instalation on Ubuntu 16.04.02:
```
```
sudo apt install clang-4.0 libboost-system1.58-dev qtdeclarative5-dev
```

## Build

```
[CXX=clang++-40] ./build.sh [--skip-build] [--run-tests]
```

## Usage

```
cd build

# Generate dictionary by file:
cat TEXT_FILE_PATH | ./parser ORDER | DICTIONARY_FILE_PATH

# Generate dictianary by url:
curl URL | ./parser ORDER | DICTIONARY_FILE_PATH

# Generate text by dictionary:
cat DICTIONARY_FILE_PATH | ./generator START_SEQUENCE LENGTH
```

## Examples

```
curl https://www.ietf.org/rfc/rfc2616.txt | ./parser 3 >rfc2616.mt
./generator "hypertext transfer protocol" 100 <rfc2616.mt
```
