#ifndef MODEL_H
#define MODEL_H

#include "viewcontroller.h"
class ViewController;

/**
 * This class should contain all the backend stuff for the Big Dog gui.
 * The idea is that this will function as the Model in the MVC pattern
 */
class Model
{
public:
    Model();
//    Model(ViewController *vc);
    void setViewController(ViewController *vc);
    ViewController* getViewController();

private:
    ViewController *vc;
};

#endif // MODEL_H
