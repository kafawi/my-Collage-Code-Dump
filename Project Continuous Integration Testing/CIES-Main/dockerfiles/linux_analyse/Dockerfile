ARG CODE_VERSION=latest
# ARG SRC_PATH="/mnt/cies-vol"
FROM nexus.informatik.haw-hamburg.de/cies-default:${CODE_VERSION}
RUN apt-get update && apt-get install -y \
    g++ \
    clang \
    openjdk-8-jre \
    openjdk-8-jre-headless \
    openjdk-8-source \
 && rm -rf /var/lib/apt/lists/*
