#ifndef behavior_hpp
#define behavior_hpp

class Behavior
{
public:
    virtual ~Behavior() = default;
    virtual void execute() = 0;

private:
};

#endif
