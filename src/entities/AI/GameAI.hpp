#ifndef game_ai_hpp
#define game_ai_hpp

class GameAI
{
public:
    GameAI();
    ~GameAI();

    void update();
    void collectResources();
    void buildStructures();
    void buildUnits();
    void attack();

private:
    void sendScouts(int x, int y);
    void sendArmy(int x, int y);
};

#endif