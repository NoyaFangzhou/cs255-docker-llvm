# cs255-docker-llvm
This repositorary contains the docker with Ubuntu 16.04 and LLVM/Clang 5.0.0


## Build the image from the Dockerfile
```[Shell]
$ docker build -t cs255-llvm-image /PATH/TO/THE/DOCKERFILE
```
## Run the image
```[Shell]
$ docker run -it -v $PWD/DIRNAME/ADD/TO/CONTAINER://DIRNAME/ADD/TO/CONTAINER --name cs255-llvm cs255-llvm-image /bin/bash
```


