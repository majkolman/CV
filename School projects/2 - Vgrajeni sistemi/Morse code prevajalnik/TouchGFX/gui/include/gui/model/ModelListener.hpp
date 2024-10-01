#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <touchgfx/hal/Types.hpp>


class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    //definicije uporabljenih funkcij
    virtual void updateText(int value) {};
    virtual void updateMorse(int velikost) {};
    virtual void updatePrevedeno() {};
    virtual void updateTime(uint16_t value){};
    virtual void updateTimeBetween(uint16_t value){};
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
