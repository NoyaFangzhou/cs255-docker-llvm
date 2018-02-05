# Use the Ubuntu+llvm Dockerfile from UCSD (llvm 3.9.1)

FROM prodromou87/llvm:3.9

MAINTAINER Fangzhou Liu <noyafangzhou.ark@gmail.com>
# Install git

RUN apt-get update && \
    apt-get install -y python git && \
    rm -rf /var/lib/apt/lists/*

# Start from a Bash prompt
CMD [ "/bin/bash" ]
