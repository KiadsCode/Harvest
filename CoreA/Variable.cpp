#include "Variable.h"

Variable::Variable(std::string NAME, std::string TYPE, std::string VALUE)
{
    name = NAME;
    type = TYPE;
    valueS = VALUE;
    if (type == "int")
    {
        if (valueS == "null")
        {
            valueS = "0";
        }
        try
        {
            valueI = atoi(valueS.c_str());
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
Variable::~Variable()
{
}