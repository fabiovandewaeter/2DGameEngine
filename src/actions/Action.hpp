#ifndef action_hpp
#define action_hpp

#include <vector>

class Entity;
class Effect;
class Pattern;

class Action
{
public:
    Action();
    ~Action();

    void apply(int x, int y);

private:
    std::vector<Effect *> effects;
    Pattern *pattern;
};

#endif