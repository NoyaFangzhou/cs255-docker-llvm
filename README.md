# cs255-docker-llvm
This repositorary contains the docker with Ubuntu 16.04 and LLVM/Clang 5.0.0.

Here is the official guid about how to install docker on different operating systems. [Install Docker](https://docs.docker.com/install/)


### Build the image from the Dockerfile
```[Shell]
$ docker build -t cs255-llvm-image /PATH/TO/THE/DOCKERFILE
```
### Run the image
```[Shell]
$ docker run -it -v $PWD/DIRNAME/ADD/TO/CONTAINER://DIRNAME/ADD/TO/CONTAINER --name cs255-llvm cs255-llvm-image /bin/bash
```

### Usefule Docker Command

```[Shell]
# List all the image
$ docker image ls

# List all the container
$ docker ps -a

# Exit the container
$ exit

# Restart the container after quit

$ docker start -ai #{CONTAINER_NAME}

# Remove the image
$ docker rmi #{IMAGE_NAME}

# Remove the container
$ docker container rm #{CONTAINER_NAME}
```
For more information about the Docker Command, please check [Docker Command](https://docs.docker.com/engine/reference/builder/#usage)


## REFERENCE
> [Clang 5 in a Docker container for C++17 development](https://solarianprogrammer.com/2017/12/14/clang-in-docker-container-cpp-17-development/)

> [Docker Image created for UCSD CSE231 class project](https://hub.docker.com/r/prodromou87/llvm/)
