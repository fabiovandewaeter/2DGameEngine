#ifndef material_hpp
#define material_hpp

class Material
{
public:
    Material();
    ~Material();

    virtual int getHP() const = 0;

private:
};

#endif
