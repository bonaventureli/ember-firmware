/* 
 * File:   EventHandlerUT.cpp
 * Author: Richard Greene
 *
 * Created on Apr 1, 2014, 4:23:21 PM
 */

#include <stdlib.h>
#include <iostream>
#include <Event.h>

#include "EventHandler.h"

/*
 * Simple C++ Test Suite
 */

/// proxy for the PrintEngine, for test purposes
class PEProxy : public CallbackInterface
{
public:
    PEProxy() :
     _gotInterrupt(false)
    {
         // 
    }
     
    bool _gotInterrupt;
    
    void callback(EventType eventType, void* data)
    {
        switch(eventType)
        {
            case ButtonInterrupt:
               _buttonCallback(data);
               break;
               
            case MotorInterrupt:
                _motorCallback(data);
                break;
                
            case DoorInterrupt:
                _doorCallback(data);
                break;
                
            default:
                // handle impossible case
                break;
        }
    }
    void _buttonCallback(void*)
    {
        std::cout << "PE got button callback" << std::endl;
        _gotInterrupt = true;
    }
    
    void _motorCallback(void*)
    {
        std::cout << "PE got motor callback" << std::endl;
        _gotInterrupt = true;        
    }
    
    void _doorCallback(void*)
    {
        std::cout << "PE got door callback" << std::endl;
        _gotInterrupt = true;        
    }
    
    
    // TODO
    // needs to subscribe to button & motor events (perh. just door interrupt for now)
    // by providing callbacks for them
    // testable either interactively, by using pushbutton switches wired to each of the 3 GPIOs
    // or by connecting them to outputs that may be driven by the test SW itself
    
    // needs to set up delay timer & motor timeout timer, set the FDs for each, 
    // subscribe to those timers, then set the timers and see if the events come in time
    
    // needs to open FIFO for PrinterStatus, set its read fd into the EventHandler,
    // then write status to it (try 2 PriterStatus objects, written one right after the other,
    // and see if EH can handle those properly)
    
    // try driving status based on a separate timer (of which the EH is oblivious) as well as via individual calls
};

/// Proxy for a UI class, for test purposes
class UIProxy : public CallbackInterface
{
    // needs to subscribe to PrinterStatus events & make sure we always read the latest value
    
    
        void callback(EventType eventType, void* data)
    {
        switch(eventType)
        {
            case ButtonInterrupt:
               _buttonCallback(data);
               break;
               
            case MotorInterrupt:
                _motorCallback(data);
                break;
                
            case DoorInterrupt:
                _doorCallback(data);
                break;
                
            default:
                // handle impossible case
                break;
        }
    }
    void _buttonCallback(void*)
    {
        std::cout << "UI got button callback" << std::endl;
    }
    
    void _motorCallback(void*)
    {
        std::cout << "UI got motor callback" << std::endl;     
    }
    
    void _doorCallback(void*)
    {
        std::cout << "UI got door callback" << std::endl;    
    }

};

void test1() {
    std::cout << "EventHandlerUT test 1" << std::endl;
    
    EventHandler eh;
    PEProxy pe;
    eh.Subscribe(MotorInterrupt, &pe);
    eh.Subscribe(ButtonInterrupt, &pe);
    eh.Subscribe(DoorInterrupt, &pe);
    
    UIProxy ui;
    eh.Subscribe(MotorInterrupt, &ui);
    eh.Subscribe(ButtonInterrupt, &ui);
    eh.Subscribe(DoorInterrupt, &ui);

    eh.Begin();
    
}

void test2() {
    std::cout << "EventHandlerUT test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (EventHandlerUT) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% EventHandlerUT" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (EventHandlerUT)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (EventHandlerUT)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (EventHandlerUT)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (EventHandlerUT)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

