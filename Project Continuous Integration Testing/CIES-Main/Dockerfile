ARG CODE_VERSION=latest
FROM nexus.informatik.haw-hamburg.de/ubuntu:${CODE_VERSION}
#RUN ls
# packages
RUN apt-get update && apt-get install -y \
    git \
    curl \
    python3 \
    python3-pip \
    ssh \
 && rm -rf /var/lib/apt/lists/*
RUN python3 -m pip install --upgrade \
    argparse \
    pymongo \
    jinja2
COPY . /
RUN ls -la
RUN ls -la /pyscripts/