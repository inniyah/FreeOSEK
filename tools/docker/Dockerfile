FROM debian:stable-slim

# Disable Prompt During Packages Installation
ARG DEBIAN_FRONTEND=noninteractive

RUN dpkg --add-architecture i386 \
    && apt-get update \
    && apt -y upgrade \
    && apt-get -y install \
        build-essential \
        gdb-multiarch \
        pkg-config \
        python3 \
        strace \
        ltrace \
        cmake \
        quilt \
        php-cli \
        sudo \
        zip \
        tree \
        file \
        fuse \
        binfmt-support \
        qemu-user-static \
    && rm -rf /var/lib/apt/lists/*

ARG UNAME
ARG UID
ARG GID

RUN groupadd -g "$GID" -o "$UNAME"
RUN useradd -m -u "$UID" -g "$GID" -o -s /bin/bash "$UNAME"

RUN printf "pass\npass\n" | passwd "$UNAME"  \
    && adduser "$UNAME" sudo  \
    && echo "$UNAME ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/nopasswd  \
    && usermod --shell "/bin/bash" "$UNAME" \
    && usermod --home "/home/$UNAME" "$UNAME"

USER $UNAME
WORKDIR /home/$UNAME
ENTRYPOINT ["/bin/bash" ]
CMD []
