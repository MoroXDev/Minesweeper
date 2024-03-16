#include "State.h"

State::State(Data& data, std::vector<std::unique_ptr<State>>& states) : data(data), states(states)
{

}

State::~State()
{
}
