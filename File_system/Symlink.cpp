#include "Symlink.h"
#include <fstream>

Symlink::Symlink(const FileLocationPair& target)
    : ConcreteFile(Type::Symlink), target(target)
{
}

const ConcreteFile::FileLocationPair & Symlink::getTarget() const
{
    return target;
}

//bool Symlink::isBroken() const
//{
//    return (target == {});
//}

bool Symlink::load(std::ifstream& input)
{
    if (ConcreteFile::load(input) == false)
        return false;   

    ConcreteFile::loadStrFromBinFile(input, target.hardAddress);
    return true;
}

bool Symlink::save(std::ofstream& output) const
{
    if (ConcreteFile::save(output) == false)
        return false;

    ConcreteFile::writeStringToBinFile(output, target.hardAddress);
    return true;
}

ConcreteFile* Symlink::copy(const Symlink& obj)
{
    return new Symlink(obj);
}
