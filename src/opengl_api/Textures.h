/* 
Adapted from:
https://github.com/Hopson97/open-builder/blob/master/LICENSE
MIT License

Copyright (c) 2019 Matthew Hopson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/


#pragma once

#include "../pch/pch_std.h"

class SectorColours;

class Texture2d {
    public:
    Texture2d();
    ~Texture2d();

    Texture2d(Texture2d&& other);
    Texture2d& operator=(Texture2d&& other);

    Texture2d(const Texture2d&) = delete;
    Texture2d& operator=(const Texture2d&) = delete;

    void create(const SectorColours& sector_colours);
    void destroy();
    void bind() const;
    bool textureExists() const;

private:
    void reset();

    GLuint m_handle = 0;
    bool m_has_texture = false;
};