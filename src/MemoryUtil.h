#pragma once

#include <iostream>
#include <unistd.h>

#include <fstream>

#include <chrono>
#include <thread>

namespace memory_util
{

//-----------------------------------------------------------------------------
// MemInfo
//-----------------------------------------------------------------------------

struct MemInfo
{
    static MemInfo get();

    size_t res_MB() const;

    size_t res_KB() const;

    size_t res_B() const;

    size_t virt_MB() const;

    size_t virt_KB() const;

    size_t virt_B() const;

private:
    MemInfo();


private:
    size_t res;
    size_t virt;

};

std::ostream& operator<<(std::ostream &os, const MemInfo &memInfo);

}
