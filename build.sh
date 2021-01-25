#!/bin/sh

gcc -o config config.c -luvc
gcc -o example example.c -luvc 
