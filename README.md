# Ares

64-bit Development Operating System

## Development

Build environment is provided as a docker container. Create the docker image with the following:

```
docker build buildenv -t ares_build
```

You can now build the project with the following:

```
./domake build-x86_64
```

## Running

Using qemu, you can you use the following:

```
qemu-system-x86_64 -cdrom ./dist/x86_64/kernel.iso
```

