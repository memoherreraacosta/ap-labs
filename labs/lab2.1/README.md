Lab 2.1 - ClockWall
===================

## Instructions

[clock2.go](./clock2.go) will accept a port number and write a program [clockWall.go](./clockWall.go) that acts as a client of several clock servers at once, reading the times from each one and displaying the results in a table, akin to the wall of clocks seen in some business offices.

```
# Clock Servers initialization

$ TZ=US/Eastern    ./clock2 -port 8010 &
$ TZ=Asia/Tokyo    ./clock2 -port 8020 &
$ TZ=Europe/London ./clock2 -port 8030 &

# Starting clockWall client

$ clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
NewYork : 12:00:00
London  : 17:00:00
Tokyo   : 02:00:00
.
.
.
```

General Requirements and Considerations
--------------------------------------- 

- Run it in a Linux distribution 
- [GoLang](https://golang.org/) installed

How to run it ?
---------------------------------------

- Clone or download the current repository
- Move inside the directory in your terminal and run the following command to compile the .go files and to initialize the time zones 
```
$ make
```

- To run it run the following command 

```
$ ./clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
```




