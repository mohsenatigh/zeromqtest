# zeromqtest
simple client-server program to demonstrate the functionality of Protobuf + Zeromq  

# dependency 
    libprotobuf
    libzmq 
    protoc 

# build
to build the system, do the following steps

    mkdir __build
    cd __build
    cmake ..
    make

# run
run the server with  __build/server/server.bin and the client with __build/client/client.bin

