#pragma once

#include <cstdint>
#include <iostream> //debug

struct Colour
{
public:
    Colour() : r(0x00), g(0x00), b(0x00), a(0x00) {};
    Colour(int r_in, int g_in, int b_in, int a_in )
    {
        setColours(r_in, g_in, b_in, a_in);
    };

    bool operator==(const Colour& other) const 
    {
        return ( r == other.r && g == other.g && b == other.b && a == other.a );
    }

    bool setColours(int r_in, int g_in, int b_in, int a_in)
    {
        if (validVal(r_in) && validVal(g_in) && validVal(b_in) && validVal(a_in)) {
            r = r_in; g = g_in; b = b_in; a = a_in;
            return true;
        } else {
            r = 0xFF, g = 0x00, b = 0xFF, a = 0xFF;
            //TODO: replace the COUT with logger
            std::cout << "[ERROR]: Colour not valid: "; logColour(); std::cout << std::endl;
            return false; 
        }

    }

    void logColour() { std::cout << "[" << (int)(r) << " " << (int)(g) << " " << (int)(b) << " " << (int)(a) << "]"; }


    uint8_t r = 0x00;
    uint8_t g = 0x00;
    uint8_t b = 0x00;
    uint8_t a = 0xFF;

private:
    bool validVal(int in) {
        return (in >= 0 && in <= 255);
    }
};


struct ColourHash 
{
    size_t operator()(const Colour& colour) const
    { 
        return ( colour.r << 24 | colour.g << 16 | colour.b << 8 | colour.a );
    }
};