#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <initializer_list>
#include "timer.h"

namespace map_bench{

    void testMap();


}

namespace vector_bench{

    void backInsert    ();
    void frontInsert   ();
    void sortEachInsert();
}

namespace list_bench{

    void backInsert    ();
    void frontInsert   ();
    void sortEachInsert();
}