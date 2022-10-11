FROM ubuntu
COPY lb3.cpp .
RUN apt-get update -qq
RUN apt-get install gcc -qq > /dev/null
RUN apt-get install g++ -qq > /dev/null
RUN g++ lb3.cpp -o lb3 -static
CMD ./lb3
