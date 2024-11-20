#include "Directory.h"

ConcreteFile* Directory::copy(const Directory& obj)
{
	return new Directory(obj);
}

void Directory::add(const ConcreteFile& newFile)
{
	if (size == capacity)
		resize(capacity * 2);


}

ConcreteFile* deductedTypeCopy(const ConcreteFile* obj)
{
	if (obj->getType() == ConcreteFile::Type::File)
		return File::copy(*reinterpret_cast<File*>(&obj));

	else if (obj->getType() == ConcreteFile::Type::Directory)
		return Directory::copy(*reinterpret_cast<Directory*>(&obj));

	return Symlink::copy(*reinterpret_cast<Symlink*>(&obj));
}

void Directory::copyFrom(const Directory& other)
{
	ConcreteFile** temp = nullptr;

	try
	{
		temp = new ConcreteFile * [other.capacity]{};
		for (size_t i = 0; i < other.size; i++)
		{
			temp[i] = deductedTypeCopy(other.content[i]);
		}
		free();
		content = temp;
	}
	catch (const std::bad_alloc&)
	{
		for (size_t i = 0; i < size; i++)
		{
			delete temp[i];
		}
		delete[] temp;
		throw;
	}
}

void Directory::moveFrom(Directory&& other) noexcept
{
}

void Directory::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete content[i];
	}

	delete[] content;
}

void Directory::resize(unsigned newCap)
{
	ConcreteFile** temp = nullptr;
	try
	{
		temp = new ConcreteFile * [newCap] {};
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = content[i];
		}
		delete[] content;
		capacity = newCap;
	}
	catch (const std::bad_alloc&)
	{
		delete[] temp;
		throw;
	}
}

Directory::Directory()
	: ConcreteFile(Type::Directory), content(nullptr), size(0), capacity(4)
{

}

Directory::Directory(const Directory& other)
	: ConcreteFile(other), content(nullptr)
{
	copyFrom(other);
}

Directory& Directory::operator=(const Directory& other)
{
	if (this != &other)
		copyFrom(other);

	return *this;
}

Directory::Directory(Directory&& other) noexcept
	: ConcreteFile(std::move(other))
{
	moveFrom(std::move(other));
}

Directory& Directory::operator=(Directory&& other) noexcept
{
	if (this != &other)
	{
		ConcreteFile::operator=(std::move(other));
		moveFrom(std::move(other));
	}

	return *this;
}

Directory::~Directory() noexcept
{
	free();
}

const ConcreteFile* const* Directory::getContent() const
{
	return content;
}

size_t Directory::getSize() const
{
	return size;
}

size_t Directory::getCapacity() const
{
	return capacity;
}
