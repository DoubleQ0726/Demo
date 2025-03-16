#! /bin/bash

if [[ -d build ]]; then
  echo "build folded existed! delete it"
  rm -rf build
fi

cmake -B build

cmake --build build --parallel 8
