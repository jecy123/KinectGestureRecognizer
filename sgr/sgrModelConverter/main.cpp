/*
 * main.cpp
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#include "sgr_xml.h"

using namespace sgr;

int main(int argc, char ** argv)
{
    if (argc <= 1)
    {
        sgr::convert_xml_to_model("simple-gesture.xml");
    }else{
        sgr::convert_xml_to_model(argv[1]);
    }
    return 0;
}

