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


#include <mico/arduino/flow/Widgets.h>

#include <QPushButton>
#include <QSlider>

namespace mico{

    ToggleButtonBlock::ToggleButtonBlock(){
        createPipe("state", "bool");

        button_ = new QPushButton("Toggle me");
        button_->setCheckable(true);
        QObject::connect(button_, &QPushButton::clicked,[&](){
            getPipe("state")->flush((bool)button_->isChecked());
        });
    }

    QWidget * ToggleButtonBlock::customWidget(){
        return button_;
    }

    
    SliderPwm::SliderPwm(){
        createPipe("pwm", "int");

        slider_ = new QSlider();
        slider_->setMinimum(0);
        slider_->setMaximum(255);
        
        QObject::connect(slider_, &QSlider::valueChanged,[&](int _val){
            getPipe("pwm")->flush(_val);
        });
    }

    QWidget * SliderPwm::customWidget(){
        return slider_;
    }
}