# Markov Chane based text builder

## Dependency

* GCC with C++17 (tested on XXX)
* QT 5.6+ (tested on XXX)

## Build

NOTE: tested on ubuntu 16.04 only
```
[CXX=g++] ./build.sh [--build_and_run_ut]
```

## Usage

```
cd build

# Generate dictionary by file:
cat TEXT_FILE_PATH | ./parser ORDER | DICTIONARY_FILE_PATH

# Generate dictianary by url:
curl URL | ./parser ORDER | DICTIONARY_FILE_PATH

# Generate text by dictionary:
cat DICTIONARY_FILE_PATH | ./generator START_SEQUENCE
```

## Examples

```
curl https://www.ietf.org/rfc/rfc2616.txt | ./parser 1 | ./generator "http"
```
