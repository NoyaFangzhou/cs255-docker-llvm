# cs255-docker-llvm #
This repositorary is designed for <b>2018 Spring - [CS255/455 Software Analysis and Improvments](https://roclocality.org/2018/01/11/cs-255-455-spring-2018/)</b> LLVM Project. It contains the docker with Ubuntu `16.04` and LLVM/Clang `3.9.1`. 

Here is the official guid about how to install docker on different operating systems. [Install Docker](https://docs.docker.com/install/)


### Build the image from the Dockerfile ###
```bash
$ docker build -t cs255-llvm-image /PATH/TO/THE/DOCKERFILE
```

### Download the image from the Docker Hub ###
```bash
$ docker pull noyafangzhou/cs255-llvm
```

### Run the image ###
```bash
$ docker run -it -v $PWD/DIRNAME/ADD/TO/CONTAINER://DIRNAME/ADD/TO/CONTAINER --name cs255-llvm cs255-llvm-image /bin/bash
```

### Usefule Docker Command ###
```bash
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

# Remove the <none> tag iamge
$ docker rmi $(docker images | grep "^<none>" | awk "{print $3}")
```
For more information about the Docker Command, please check [Docker Command](https://docs.docker.com/engine/reference/builder/#usage)


## REFERENCE ##
> [Clang 5 in a Docker container for C++17 development](https://solarianprogrammer.com/2017/12/14/clang-in-docker-container-cpp-17-development/)

> [Docker Image created for UCSD CSE231 class project](https://hub.docker.com/r/prodromou87/llvm/)
