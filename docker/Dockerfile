FROM ubuntu:latest 

LABEL maintainer="Bogdan Morosanu <bogdan.moro.mail@gmail.com>"

ENV TZ=Europe/Amsterdam
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get upgrade -y && apt-get install --no-install-recommends -y build-essential emacs cmake git

COPY .. /rps

WORKDIR /rps

RUN rm -rf build && mkdir build && cd build && cmake ../src && make
