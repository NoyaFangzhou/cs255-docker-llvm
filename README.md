# cs255-docker-llvm #
This repositorary is designed for <b>2018 Spring - [CS255/455 Software Analysis and Improvments](https://roclocality.org/2018/01/11/cs-255-455-spring-2018/)</b> LLVM Project. It contains the docker with Ubuntu `16.04` and LLVM/Clang `3.9.1`. 

Here is the official guide about how to install docker on different operating systems. [Install Docker](https://docs.docker.com/docker-for-mac/install/)


### Build the image ###
```bash
$ docker build -t cs255-llvm-image /PATH/TO/THE/DOCKERFILE

# Or, you can directly pull the image from Docker Hub
$ docker pull noyafangzhou/cs255-llvm-image
```

### Run the image ###
Notes that the `cs255-llvm-pass` is the directory that contains the code template. You have to clone it first and then add it to the docker container using the following command. Also, Capital Letters **CANNOT** appear on the path to `cs255-llvm-pass` directory.
```bash
$ docker run -it -v $PWD/cs255-llvm-pass:/cs255-llvm-pass --name cs255-llvm cs255-llvm-image /bin/bash
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

# Remove the <none> tag image
$ docker rmi $(docker images | grep "^<none>" | awk "{print $3}")
```
For more information about the Docker Command, please check [Docker Command](https://docs.docker.com/engine/reference/builder/#usage)


## REFERENCE ##
> [Clang 5 in a Docker container for C++17 development](https://solarianprogrammer.com/2017/12/14/clang-in-docker-container-cpp-17-development/)

> [Docker Image created for UCSD CSE231 class project](https://hub.docker.com/r/prodromou87/llvm/)
