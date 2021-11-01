/********************************************************************************
  \project  INFM_HIL_Interface
  \file     SimulationCommunicationHandler.cpp
  \brief    Provides the functions for setting up a socket to receive data from the simulation
  \author   Alexander Pilz
  \author   Fabian Genes
  \version  1.0.0
  \date     02.11.2021
 ********************************************************************************/


/********************************************************************************
 * Includes
 *********************************************************************************/

#include <zmq.hpp>
#include <string>
#include <cstring>
#include <iostream>

/********************************************************************************
 * Function declaration
 ********************************************************************************/

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    char buf[100] = {0};
    while (std::string(buf).compare("done")) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::memcpy(buf, request.data(), 100);
        std::cout << "Received message " << buf << std::endl;

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "Hello", 5);
        socket.send (reply);
    }
    return 0;
}

/********************************************************************************
 * EOF
 ********************************************************************************/
