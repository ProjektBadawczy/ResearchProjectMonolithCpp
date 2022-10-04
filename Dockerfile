FROM gcc:latest

RUN apt-get update && apt-get install -y cmake libcpprest-dev libssl-dev

WORKDIR /src

EXPOSE 8080

COPY ./ /src/CppMonolith

RUN mkdir /src/build

WORKDIR /src/build

RUN cmake ../CppMonolith

RUN make CppMonolith

ENTRYPOINT ["./CppMonolith"]
