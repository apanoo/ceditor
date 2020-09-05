# CEDITOR

> Cross platform editor with OpenGL、electron and golang.

```
                  ___ __
   ________  ____/ (_) /_____  _____
  / ___/ _ \/ __  / / __/ __ \/ ___/
 / /__/  __/ /_/ / / /_/ /_/ / /
 \___/\___/\__,_/_/\__/\____/_/

```

[![Build Status](https://travis-ci.com/apanoo/ceditor.svg?branch=master)](https://travis-ci.com/apanoo/ceditor)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![dev status](https://img.shields.io/badge/status-developing-green.svg)]()

```
git clone https://github.com/apanoo/ceditor
cd ceditor
git submodule update --init --recursive
```

## 0.deps

    OS:             MacOSX 10.15.6
    ndk:            r18b
    cmake:          3.16.4
    environment:    1.40.1
    xcode:          11.6 (11E708)
    android studio: 4.0.1

## 1. make dep

Install dependencies

## 2. make run-cpp

Run engine desktop

> build make build-cpp || mkdir build && cd build && cmake .. && make

## or. make run-js

- Listening localhost:8080
- Visit localhost:8080
