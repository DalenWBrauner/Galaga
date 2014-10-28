#include "ResourceHolder.h"

// load()
template <typename ResourceType, typename Identifier>
void ResourceHolder<ResourceType, Identifier>::load(Identifier whichOne, const std::string& filename) {

	// Create it
	std::unique_ptr<ResourceType> resource = new ResourceType();
	// Load it
	if (!resource.loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::load() Failed to load " + filename);
	}
	// Insert it
	insertResource(whichOne, std::move(resource));
}

// load(second parameter)
template <typename ResourceType, typename Identifier>
template <typename Parameter>
void ResourceHolder<ResourceType, Identifier>::load(Identifier whichOne, const std::string& filename, const Parameter& param2) {

	// Create it
	std::unique_ptr<ResourceType> resource(new ResourceType());
	// Load it (with our second parameter)
	if (!resource.loadFromFile(filename, param2))
		throw std::runtime_error("ResourceHolder::load() Failed to load " + filename);
	// Insert it
	insertResource(whichOne, std::move(resource));
}

// get()
template <typename ResourceType, typename Identifier>
ResourceType& ResourceHolder<ResourceType, Identifier>::get(Identifier whichOne) {

	// Grab the resource
	auto found = mResourceMap.find(whichOne);
	// Assure ourselves we received a resource
	assert(found != mResourceMap.end());
	// Return a pointer to the resource
	return *found->second;
}

// const get()
template <typename ResourceType, typename Identifier>
const ResourceType& ResourceHolder<ResourceType, Identifier>::get(Identifier whichOne) {

	// Grab the resource
	auto found = mResourceMap.find(whichOne);
	// Assure ourselves we received a resource
	assert(found != mResourceMap.end());
	// Return a pointer to the resource
	return *found->second;
}


// insertResource()
template <typename ResourceType, typename Identifier>
void ResourceHolder<ResourceType, Identifier>::insertResource(Identifier whichOne, std::unique_ptr<ResourceType> resource) {

	// Insert
	//auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	auto inserted = mResourceMap[whichOne] = std::move(resource);
	// Check success
	assert(inserted.second);
}