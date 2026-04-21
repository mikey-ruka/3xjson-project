#!/bin/sh

# Ruka Project by Ruka Raposa Team & Contribuitors.
# Project is under GPL3-license, read LICENSE.md on the root.

XJ_BUILD="./Build"

echo ==============
echo Build Starting
echo ==============
echo

# If there is no Build, then:
[[ -d "$XJ_BUILD" ]] || mkdir "$XJ_BUILD"
cd $XJ_BUILD

# Continue:
cmake                                                                           \
    ..                                                                          \
    -DXJ_ENABLE_ASAN=on                                                         \
    -DXJ_SELF_BUILD=on                                                          \
    -DXJ_TESTS=on                                                               \
    -G Ninja

ninja                                                                           \
    -v                                                                          \
    -j20

cd ..

echo
echo ==============
echo Build Complete
echo ==============