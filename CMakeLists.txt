cmake_minimum_required(VERSION 3.12)
project(qrcode C)

set(CMAKE_C_STANDARD 99)

add_executable(qrcode main.c CORRECAO_DE_ERROS.h)