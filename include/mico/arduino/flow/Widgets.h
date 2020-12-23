//---------------------------------------------------------------------------------------------------------------------
//  Arduino MICO plugin
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



#ifndef MICO_ARDUINO_FLOW_WIDGETS_H_
#define MICO_ARDUINO_FLOW_WIDGETS_H_

#include <flow/Block.h>
#include <flow/Outpipe.h>

class QPushButton;
class QSlider;

namespace mico{

    class ToggleButtonBlock:public flow::Block{
    public:
        virtual std::string name() const override {return "Toggle Button";}     
        // virtual QIcon icon() const override { 
        //     std::string userDir(getenv("USER"));
        //     std::string resourcesDir = "/home/"+userDir+"/.flow/plugins/resources/arduino/";
        //     return QIcon((resourcesDir+"arduino_icon.png").c_str());
        // }

        virtual QWidget * customWidget() override;
        
        ToggleButtonBlock();

        std::string description() const override {return    "ToggleButton\n";};
    private:
        QPushButton *button_;
    };

    
    class SliderPwm :public flow::Block{
    public:
        SliderPwm();

        virtual std::string name() const override {return "Slider Pwm";}     
        // virtual QIcon icon() const override { 
        //     std::string userDir(getenv("USER"));
        //     std::string resourcesDir = "/home/"+userDir+"/.flow/plugins/resources/arduino/";
        //     return QIcon((resourcesDir+"arduino_icon.png").c_str());
        // }

        virtual QWidget * customWidget() override;
        

        std::string description() const override {return    "Slider pwm\n";};
    private:
        QSlider *slider_;
    };


    class NotOperator :public flow::Block{
    public:
        NotOperator(){
            createPipe("NoA", "bool");
            createPolicy({  {"A", "bool"}});
            registerCallback({"A", "B"}, 
                [&](flow::DataFlow _data){
                    bool res = !_data.get<bool>("A");
                    getPipe("NoA")->flush(res);
                }
            );
        }

        virtual std::string name() const override {return "NOT";}     
        std::string description() const override {return    "NOT\n";};
        // virtual QIcon icon() const override { 
        //     std::string userDir(getenv("USER"));
        //     std::string resourcesDir = "/home/"+userDir+"/.flow/plugins/resources/arduino/";
        //     return QIcon((resourcesDir+"arduino_icon.png").c_str());
        // }        
    };

    class AndOperator :public flow::Block{
    public:
        AndOperator(){
            createPipe("out", "bool");
            createPolicy({  {"A", "bool"}, {"B", "bool"} });
            registerCallback({"A", "B"}, 
                [&](flow::DataFlow _data){
                    bool res = _data.get<bool>("A") && _data.get<bool>("B");
                    getPipe("out")->flush(res);
                }
            );
        }

        virtual std::string name() const override {return "AND";}     
        std::string description() const override {return    "AND\n";};
        // virtual QIcon icon() const override { 
        //     std::string userDir(getenv("USER"));
        //     std::string resourcesDir = "/home/"+userDir+"/.flow/plugins/resources/arduino/";
        //     return QIcon((resourcesDir+"arduino_icon.png").c_str());
        // }        
    };

    class OrOperator :public flow::Block{
    public:
        OrOperator(){
            createPipe("out", "bool");
            createPolicy({  {"A", "bool"}, {"B", "bool"} });
            registerCallback({"in"}, 
                [&](flow::DataFlow _data){
                    bool res = _data.get<bool>("A") || _data.get<bool>("B");
                    getPipe("out")->flush(res);
                }
            );
        }

        virtual std::string name() const override {return "OR";}     
        std::string description() const override {return    "OR\n";};
        // virtual QIcon icon() const override { 
        //     std::string userDir(getenv("USER"));
        //     std::string resourcesDir = "/home/"+userDir+"/.flow/plugins/resources/arduino/";
        //     return QIcon((resourcesDir+"arduino_icon.png").c_str());
        // }        
    };


}



#endif