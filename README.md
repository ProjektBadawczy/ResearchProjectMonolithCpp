# Research Project C++ Monolith
> The program was prepared for the subject Research Project. 
## Table of contents
* [About The Project](#about-the-project)
* [Technologies](#technologies)
* [Getting Started](#getting-started)
* [Contact](#contact)

## About The Project

The aim of the project is to implement a monolith web API application for operations on graphs using C++ and C++ REST SDK.

## Technologies
* C++ REST SDK
* Docker

## C++ REST SDK

The C++ REST SDK is a Microsoft open-source project for implementing client-server REST communication. Its aim is to help developers to connect with web applications as well as to create their own web API applications.


## Getting Started
Clone the repository  
`git clone https://github.com/ProjektBadawczy/ResearchProjectMonolithCppp`  
  
Run
`docker-compose build`
`docker-compose up`

## REST API
Get basic information about graph based on ID: http://localhost:8145/api/graph/1

Get maximum flow in graph based on ID beewten two vertices: http://localhost:8145/api/edmonds-karp/1/1/2

## Contact
Jakub Czarnecki - jakub.piotr.czarnecki@gmail.com
