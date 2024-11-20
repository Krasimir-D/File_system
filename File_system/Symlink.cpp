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

ConcreteFile* Symlink::copy(const Symlink& obj)
{
    return new Symlink(obj);
}
