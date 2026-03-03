cmake_minimum_required(VERSION 3.20)
project(c)

set(CMAKE_C_STANDARD 11)

# Burası en önemlisi: 'c' hedefi ile 'main.c' dosyasını bağlar
add_executable(c library.c)