//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif
#include <sys/time.h>
#include <cstdio>

#define TEST_ITER 100000
#define MILLION 1000000

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

	timeval start, end;
	gettimeofday(&start, NULL);
	long long counter = 0;
    while (true) {
		counter ++;
		if (counter % TEST_ITER == 0) {
				gettimeofday(&end, NULL);
				double time_use = (end.tv_sec-start.tv_sec) * MILLION + (end.tv_usec-start.tv_usec);
				printf("Time use %.2lf us, Throughput %.2lf op\n", time_use, (double)TEST_ITER * MILLION / time_use);
				gettimeofday(&start, NULL);
		}
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
//        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
//    	sleep(1);

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "Worl", 4);
        socket.send (reply);
    }
    return 0;
}
