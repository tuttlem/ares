#!/bin/bash

qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso -serial mon:stdio -serial file:kernel.log -d int,cpu_reset -no-reboot