cmake_minimum_required(VERSION 3.12)
project(sysproj C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(sysproj
        answers/sum.c
        questions/base2.c
        questions/diff21.c
        questions/gcf.c
        questions/lastDigit.c
        questions/nearHundred.c
        bat.c
        bat.h
        server.c
        user.c temp/1234/sum.c questions/sum.c answers/answers.h)
