#ifndef updatable_hpp
#define updatable_hpp

class IUpdatable
{
public:
    virtual void update() = 0;
    virtual ~IUpdatable() = default;
};

#endif
