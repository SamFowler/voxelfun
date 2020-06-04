#include "Timer.h"

//#include <iostream>

 

void Timer::init()
{
    current_time = chrono_clock::now();
    start_time = chrono_clock::now();
}

void Timer::frameStart()
{
    start_time = chrono_clock::now();
    frame_duration = std::chrono::duration_cast<std::chrono::nanoseconds>( start_time - current_time );
    if (frame_duration > max_frame_duration) 
        frame_duration = max_frame_duration;
    current_time = start_time;

    

    accumulator += frame_duration;

}

bool Timer::checkDeltaTimeReached()
{
    return (accumulator >= dt);
}

float Timer::getDeltaTime()
{
    return std::chrono::duration<float>(dt).count();
}

void Timer::endUpdateLoop() 
{
    time_count += dt;
    accumulator -= dt; 
    update_frame_count += 1;
}

//State Timer::frameEnd(/*const State& current_state, const State& previous& state*/)
void Timer::frameEnd(/*const State& current_state, const State& previous& state*/)
{
    render_frame_count += 1;

    // see gafferongames.com/post/fix_your_timestep
    //const double alpha = accumulator / m_dt;
    //return current_state * alpha + previous_state * (1.0 - alpha);
}

void Timer::printFPS() 
{
    total_time_count += frame_duration;

    if (total_time_count >= one_sec_in_nano)
    {
        std::cout << "FPS: update(" << update_frame_count << "), render(" << render_frame_count << ")" << std::endl;
        update_frame_count = 0;
        render_frame_count = 0;
        time_count = std::chrono::nanoseconds(0);
        total_time_count = std::chrono::nanoseconds(0);
    }
}

