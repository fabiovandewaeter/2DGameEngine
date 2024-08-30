#include "Game.hpp"
    #include <unistd.h>
    #include <thread>
#include <chrono>




unsigned int frameCount2 = 0, updateCount2 = 0;
float fps2 = 0, ups2 = 0;
Uint64 currentTimeFPS2, currentTimeUPS2;

int main(int argc, char *argv[]) {
    Game game;
    Uint32 frequency2 = SDL_GetPerformanceFrequency(), deltaTime, frameDelay;
    Uint64 lastTimeFPS2 = SDL_GetPerformanceCounter(), lastTimeUPS2 = lastTimeFPS2;
    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    /*while (game.running()){
        Uint32 frameStart = SDL_GetPerformanceCounter() ;

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
        Uint32 frameStart = SDL_GetPerformanceCounter() ;

        frameCount2++;
        //printf("%d\n", frameCount2);
        currentTimeFPS2 = SDL_GetPerformanceCounter();
        if (frameCount2 == game.fixedFPS){
            std::cout << "time: " << currentTimeFPS2 - lastTimeFPS2 << std::endl;
        }
        if (currentTimeFPS2 - lastTimeFPS2 >= frequency2-1000)
        { // 1000 ms = 1 seconde
        printf("test");
            //printf("frameCount: %d currentTime: %ld lastTime: %ld time: %ld res: %F\n", frameCount2, currentTimeFPS2, lastTimeFPS2,currentTimeFPS2 - lastTimeFPS2, (currentTimeFPS2 - lastTimeFPS2) / frequency2);
            fps2 = frameCount2 / ((currentTimeFPS2 - lastTimeFPS2) / (frequency2-1000));
            std::cout << "FPS: " << fps2 << std::endl;
            lastTimeFPS2 = currentTimeFPS2;
            frameCount2 = 0;
        }

        deltaTime = SDL_GetPerformanceCounter() - frameStart;
        frameDelay = frequency2 / game.fixedFPS;

        /*Uint64 frameStart23 = SDL_GetPerformanceCounter() ;
        SDL_Delay(16);
        printf("%ld\n", SDL_GetPerformanceCounter() - frameStart23);*/
        
        //printf("frameDelay: %ld deltaTime: %ld numberMs: %d\n", frameDelay, deltaTime, ((frameDelay - deltaTime) % frequency2)/10000);
        Uint32 remainingTime = frameDelay - deltaTime;
        Uint32 timeSlept = 0;
        if (remainingTime >= 10000){ //ESSAYER AVEC while( ... >= 15000) pour prendre en compte que ça ajoute un peu à chaque fois ? ou juste if aussi
            int numberMs = ((remainingTime % frequency2)/10000)-0;
            Uint64 startTimeSlept = SDL_GetPerformanceCounter() ;
            SDL_Delay(numberMs);
            timeSlept = (SDL_GetPerformanceCounter() - startTimeSlept);
            //printf("%d\n", numberMs);
            //std::cout << "timeSlept: " << timeSlept << std::endl;
            if (timeSlept > frameDelay) {
                remainingTime = 0;
            }
            else {
                remainingTime = frameDelay - timeSlept;
            }
        }
        //deltaTime = SDL_GetPerformanceCounter() - frameStart;
        //printf("remainingTime: %ld deltaTime: %ld %ld timeSlipt: %ld \n", remainingTime, deltaTime, deltaTime - timeSlept, timeSlept);
        //std::cout << "remainingTime: " << remainingTime << std::endl;
        /*while (remainingTime > 0 && deltaTime - timeSlept < remainingTime) {
            //printf("deltaTime-timeSlept: %ld remainingTime: %ld\n", deltaTime-timeSlept, remainingTime );
            deltaTime = SDL_GetPerformanceCounter() - frameStart;
        }*/
            deltaTime = SDL_GetPerformanceCounter() - frameStart;
       while (deltaTime < frameDelay) {
            deltaTime = SDL_GetPerformanceCounter() - frameStart;
        }
        //std::cout << "FINIdeltaTime: " << deltaTime << std::endl;
    }
    game.clean();

    return 0;
}