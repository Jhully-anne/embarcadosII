# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the G++ compiler
RUN apt-get -y install g++ make
RUN apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi