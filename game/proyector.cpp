#include "proyector.h"


proyector::proyector(float px_, float py_): px(px_), py(py_)
{

}

float proyector::get_px() const
{
    return px;
}

float proyector::get_py() const
{
    return py;
}

void proyector::set_delta(float delta_)
{
    delta = delta_;
}


