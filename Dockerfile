FROM ubuntu:latest
MAINTAINER Michael Tuttle <tuttlem@gmail.com>

RUN apt-get update && \
    apt-get install -y build-essential binutils nasm bochs bochs-x bochs-sdl grub-common xorriso && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

