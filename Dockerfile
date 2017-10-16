FROM ubuntu
RUN apt update
RUN apt install g++ curl -y
COPY . .
RUN  g++ maker.cpp -o a -std=c++14 -O2
CMD ./a
