@echo off
IF NOT EXIST build (
    mkdir build 
)

cmake --build build