#include "Game.hpp"
    #include <unistd.h>
    #include <thread>
#include <chrono>

Game game;
Uint32 frequency2 = SDL_GetPerformanceFrequency(), deltaTime, frameDelay, frameStart;



unsigned int frameCount2 = 0, updateCount2 = 0;
float fps2 = 0, ups2 = 0;
Uint64 lastTimeFPS2 = SDL_GetPerformanceCounter(), currentTimeFPS2, lastTimeUPS2 = lastTimeFPS2, currentTimeUPS2;


int main(int argc, char *argv[]) {
    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    /*while (game.running()){ 
        frameStart = SDL_GetPerformanceCounter() ;

        game.handleEvents();
        game.update();
        game.render();

        deltaTime = SDL_GetPerformanceCounter() - frameStart;
        frameDelay = frequency / game.fixedFPS;
        //printf("frameDelay-deltaTime: %ld frameDelay: %ld delaTime: %ld\n", (frameDelay - deltaTime), frameDelay, deltaTime);
        if (frameDelay > deltaTime){
            //SDL_Delay((frameDelay - deltaTime)/10000);
            struct timespec ts;
            ts.tv_sec = 0;         // 0 seconde
            //ts.tv_nsec = 2300000L; // 2.3 ms = 2 300 000 nanosecondes
            ts.tv_nsec = ((frameDelay*1) - (deltaTime*1))*100;
            printf("frameDelay-deltaTime: %ld ts.tv_nsec: %ld frameDelay: %ld delaTime: %ld\n", (frameDelay - deltaTime), ts.tv_nsec, frameDelay, deltaTime);
            nanosleep(&ts, NULL);
        }
       /*while (deltaTime < frameDelay) {
            deltaTime = SDL_GetPerformanceCounter() - frameStart;
       }
    }*/
    while (game.running()){ 
        frameStart = SDL_GetPerformanceCounter() ;

        frameCount2++;
        //printf("%d\n", frameCount2);
        currentTimeFPS2 = SDL_GetPerformanceCounter();
        if (currentTimeFPS2 - lastTimeFPS2 >= frequency2)
        { // 1000 ms = 1 seconde
            //printf("frameCount: %d currentTime: %ld lastTime: %ld time: %ld res: %F\n", frameCount2, currentTimeFPS2, lastTimeFPS2,currentTimeFPS2 - lastTimeFPS2, (currentTimeFPS2 - lastTimeFPS2) / frequency2);
            fps2 = frameCount2 / ((currentTimeFPS2 - lastTimeFPS2) / frequency2);
            std::cout << "FPS: " << fps2 << std::endl;
            lastTimeFPS2 = currentTimeFPS2;
            frameCount2 = 0;
        }

        deltaTime = SDL_GetPerformanceCounter() - frameStart;
        frameDelay = 10000000 / 120;
        //printf("frameDelay-deltaTime: %ld frameDelay: %ld delaTime: %ld\n", (frameDelay - deltaTime), frameDelay, deltaTime);

            struct timespec ts;
            ts.tv_sec = 0;         // 0 seconde
            //ts.tv_nsec =  16666666;
            //ts.tv_nsec =  1000000000-0;
            //ts.tv_nsec = 16666666-deltaTime;
            //ts.tv_nsec =  16666666;
            printf("t %ld\n", deltaTime*frequency2);
            ts.tv_nsec =     100000000-deltaTime*frequency2;
            Uint64 frameStart23 = SDL_GetPerformanceCounter();
            //clock_nanosleep(CLOCK_REALTIME, 0, &ts, NULL);
            //nanosleep(&ts, NULL);
            printf("%ld\n", SDL_GetPerformanceCounter() - frameStart23);

            //std::this_thread::sleep_for(std::chrono::milliseconds(500));

            /*Uint64 frameStart23 = SDL_GetPerformanceCounter() ;
            SDL_Delay(16);
            printf("%ld\n", SDL_GetPerformanceCounter() - frameStart23);*/

        game.update();
        game.render();
        while (deltaTime < frameDelay) {
            deltaTime = SDL_GetPerformanceCounter() - frameStart;
        }
    }
    game.clean();

    return 0;
}