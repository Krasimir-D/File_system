#pragma once
#include "File.h"
#include "Symlink.h"

class Directory : public ConcreteFile
{
public:
	Directory();
	Directory(const Directory& other);
	Directory& operator=(const Directory& other);
	Directory(Directory&& other) noexcept;
	Directory& operator=(Directory&& other) noexcept;
	~Directory() noexcept;

	const ConcreteFile* const* getContent() const;
	size_t getSize() const;
	size_t getCapacity() const;

	static ConcreteFile* copy(const Directory& obj);

	const ConcreteFile& operator[](size_t index) const;
	ConcreteFile& operator[](size_t index);

	// imports a file
	void add(const ConcreteFile& newFile);
	void remove(const ConcreteFile& file);
	
	bool load(std::ifstream& input);
	bool save(std::ofstream& out) const;

private:
	void copyFrom(const Directory& other);
	void moveFrom(Directory&& other) noexcept;
	void free();
	void resize(unsigned newCap);

private:
	ConcreteFile** content;
	size_t size;
	size_t capacity;
};

