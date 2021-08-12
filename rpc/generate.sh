#!/bin/sh
protoc -I=. --cpp_out=../common/ message.proto
