FROM debian:11-slim@sha256:6043127d54b297de2b0f8feb29173c42884c52a72f7f744c180dda7beb27e760

RUN apt-get update                              \
 && DEBIAN_FRONTEND=noninteractive              \
    apt-get install -y --no-install-recommends  \
        gcc                                     \
        python3                                 \
        zlib1g-dev                              \
        pkg-config                              \
        libglib2.0-dev                          \
        patch                                   \
        git                                     \
        make                                    \
 && apt-get clean                               \
 && rm -rf /var/lib/apt/lists/*