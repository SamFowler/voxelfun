#pragma once

#include <chrono>
#include <ratio>

using chrono_clock = std::chrono::high_resolution_clock;

class Timer
{
public:
    void init();
    void frameStart();
    bool checkDeltaTimeReached();
    float getDeltaTime();
    void endUpdateLoop();
    void frameEnd();
    void printFPS();


private:
    unsigned render_frame_count = 0;
    unsigned update_frame_count = 0;

    unsigned m_framerate = 60;

    std::chrono::nanoseconds time_count = std::chrono::nanoseconds(0);
    std::chrono::nanoseconds total_time_count = std::chrono::nanoseconds(0);
    
    std::chrono::nanoseconds dt = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)/(float)m_framerate);

    //chrono_clock::duration m_dt = std::chrono::duration_cast<std::chrono::nanoseconds>((1.0) / (m_framerate));
    //chrono_clock::duration m_dt = std::chrono::duration<double>((1.0) / (m_framerate));
    //const std::chrono::nanoseconds dt = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::duration<double>(1.0 / m_framerate));
    //const std::chrono::nanoseconds time_step = (1.0/m_framerate)s;

    //const std::chrono::nano
    const std::chrono::nanoseconds one_sec_in_nano = std::chrono::nanoseconds(std::chrono::seconds(1));
    const std::chrono::nanoseconds max_frame_duration = std::chrono::nanoseconds(std::chrono::milliseconds(250));
    //std::chrono::duration<float> t;
    
    chrono_clock::time_point current_time;
    chrono_clock::time_point start_time;

    std::chrono::nanoseconds frame_duration = std::chrono::nanoseconds(0);
    std::chrono::nanoseconds accumulator = std::chrono::nanoseconds(0);

};