#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
	
	void moveStepperToRight();
	
	void moveStepperToLeft();
	
    void analogUpdatePA0();
	
	void analogUpdatePC1();
	
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
