#include "Symlink.h"

Symlink::Symlink(const ConcreteFile* target)
    : ConcreteFile(Type::Symlink), target(target)
{
}

const ConcreteFile* Symlink::getTarget() const
{
    return target;
}

bool Symlink::isBroken() const
{
    return (target == nullptr);
}

bool Symlink::load(std::ifstream& input)
{
    return false;
}

bool Symlink::save(std::ofstream& output) const
{
    return false;
}

ConcreteFile* Symlink::copy(const Symlink& obj)
{
    return new Symlink(obj);
}
