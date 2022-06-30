FROM gcc:latest

RUN apt-get update && apt-get install -y cmake libcpprest-dev libssl-dev

WORKDIR /src

COPY ./ /src/CppMonolith

RUN mkdir /src/build

WORKDIR /src/build

RUN cmake ../CppMonolith

RUN make CppMonolith

ENTRYPOINT ["./CppMonolith"]
