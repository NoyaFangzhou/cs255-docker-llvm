# cs255-docker-llvm

## Build the image from the Dockerfile
```[Shell]
$ docker build -t cs255-llvm-image .
```
## Run the image
```[Shell]
$ docker run -it -v $PWD/cs255-llvm:/cs255-llvm --name cs255-llvm cs255-llvm-image /bin/bash
```
