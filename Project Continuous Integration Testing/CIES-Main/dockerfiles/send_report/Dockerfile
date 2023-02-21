ARG CODE_VERSION=latest
#ARG SRC_PATH="/mnt/cies-vol"
FROM nexus.informatik.haw-hamburg.de/cies-default:${CODE_VERSION}
#FROM nexus.informatik.haw-hamburg.de/cies-default:latest
#RUN bash ${SRC_PATH}/dockerfiles/send_report/install.sh
RUN apt-get update && apt-get install -y \
    apt-transport-https \
    libio-socket-ssl-perl \
    openssh-client \
    sendemail \
 && rm -rf /var/lib/apt/lists/*