//---------------------------------------------------------------------------------------------------------------------
//  Cameras wrapper MICO plugin
//---------------------------------------------------------------------------------------------------------------------
//  Copyright 2020 Pablo Ramon Soria (a.k.a. Bardo91) pabramsor@gmail.com
//---------------------------------------------------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
//  and associated documentation files (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge, publish, distribute,
//  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial
//  portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
//  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//---------------------------------------------------------------------------------------------------------------------


#include <mico/arduino/flow/ArduinoDeviceBlock.h>
#include <flow/Outpipe.h>

#include <sstream>
#include <mico/arduino/SerialPort.h>

namespace mico{
    ArduinoDeviceBlock::ArduinoDeviceBlock(){
        createPipe("A0", "int");
        createPipe("A1", "int");
        createPipe("A2", "int");
        createPipe("A3", "int");
        createPipe("D2", "bool");
        createPipe("D3", "bool");
        createPipe("D4", "bool");
        createPipe("D5", "bool");
        createPipe("D6", "bool");
        createPipe("D7", "bool");
        createPipe("SoftwareSerial1", "string");
        createPipe("SoftwareSerial2", "string");

        createPolicy({  {"D2", "bool"},
                        {"D3", "bool"},
                        {"D4", "bool"},
                        {"D5", "bool"},
                        {"D6", "bool"},
                        {"PWM0", "int"},
                        {"PWM1", "int"},
                        {"PWM2", "int"},
                        {"A0", "int"},
                        {"A1", "int"},
                        {"A2", "int"},
                        {"A3", "int"},
                        {"SoftwareSerial1", "string"},
                        {"SoftwareSerial2", "string"}});

        registerCallback({"D2"}, 
            [&](flow::DataFlow _data){
                auto v = _data.get<bool>("D2");
                std::string val = (v?"1":"0");
                if(arduino_->isOpen()){
                    while(isBeingUsed_){}
                    isBeingUsed_ = true;
                    arduino_->writeString("{\"D2\":"+val+"}");
                    std::cout << "{\"D2\":"+val+"}" << std::endl;
                    isBeingUsed_ = false;
                }
            }
        );

        registerCallback({"D3"}, 
            [&](flow::DataFlow _data){
                auto v = _data.get<bool>("D3");
                std::string val = (v?"1":"0");
                if(arduino_->isOpen()){
                    while(isBeingUsed_){}
                    isBeingUsed_ = true;
                    arduino_->writeString("{\"D3\":"+val+"}");
                    std::cout << "{\"D3\":"+val+"}" << std::endl;
                    isBeingUsed_=false;
                }
            }
        );

        registerCallback({"D4"}, 
            [&](flow::DataFlow _data){
                auto v = _data.get<bool>("D4");
                std::string val = (v?"1":"0");
                if(arduino_->isOpen()){
                    while(isBeingUsed_){}
                    isBeingUsed_ = true;
                    arduino_->writeString("{\"D4\":"+val+"}");
                    std::cout << "{\"D4\":"+val+"}" << std::endl;
                    isBeingUsed_ = false;
                }
            }
        );
    }

    ArduinoDeviceBlock::~ArduinoDeviceBlock(){
        if(arduino_){
            arduino_->close();
        }
    }

    bool ArduinoDeviceBlock::configure(std::unordered_map<std::string, std::string> _params) {
        for(auto &p:_params){
            std::stringstream ss;
            ss << p.second;
            if(p.first == "device"){
                arduino_ = std::shared_ptr<SerialPort>(new SerialPort(p.second, 115200));
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        return false;
    }
    
    std::vector<std::pair<std::string, flow::Block::eParameterType>> ArduinoDeviceBlock::parameters(){
        return {
            {"device", flow::Block::eParameterType::STRING}
        };
    }


}