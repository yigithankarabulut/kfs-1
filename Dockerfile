FROM debian:bullseye

RUN	apt-get	update && apt-get install -y nasm clang xorriso grub-pc-bin build-essential

WORKDIR /srcs

ENTRYPOINT ["tail", "-f", "/dev/null"]
