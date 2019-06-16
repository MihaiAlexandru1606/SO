cmake_minimum_required(VERSION 3.12)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(hashtable)
include_directories(linkedlist)
include_directories(parser)
include_directories(utils)

add_executable(src
        hashtable/hash.c
        hashtable/hash.h
        hashtable/hashtable.c
        hashtable/hashtable.h
        linkedlist/linkedlist.c
        linkedlist/linkedlist.h
        parser/parser.c
        parser/paser.h
        utils/utils.h
        main.c utils/utils.c)
