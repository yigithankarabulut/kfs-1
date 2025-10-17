# KFS-1

A minimal 32-bit kernel-from-scratch project with a containerized toolchain and quick run via QEMU.

## Project Overview

This repository builds a bootable ISO with a tiny kernel written in C and assembly. The provided `Makefile` orchestrates building inside a Docker container and running with QEMU.

## Layout

- `srcs/libs/libft`, `srcs/libs/libvga`: minimal libraries for memory ops and VGA text mode
- `srcs/libs/srcs/boot.s`, `srcs/libs/srcs/kmain.c`: boot and kernel entry
- `srcs/includes`: headers for hardware and library code
- `srcs/iso/boot/grub/grub.cfg`: GRUB configuration
- `linker.ld`: kernel linker script
- `Dockerfile`: build environment for reproducible builds

## Prerequisites

- Docker
- QEMU (`qemu-system-i386`)

## Quick Start

```bash
make build_container     # build Docker image and start container
make                     # alias: make all (build + run)
make build_kernel        # build inside container
make run                 # run the ISO with QEMU (SDL display)
```

Notes:
- The container mounts `srcs/` for builds.
- Output ISO: `srcs/norx.iso`.

## Clean Up

```bash
make clean               # clean artifacts inside the container
make fclean              # full clean inside container
make fclean_container    # stop/remove container and image
```

## Learning Goals

- Boot flow with GRUB → protected mode → kernel `kmain`
- VGA text output and low-level memory operations
- Minimal build system and reproducible environment
