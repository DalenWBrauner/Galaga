#include "ResourceHolder.h"

// load()
template <typename ResourceType, typename Identifier>
void ResourceHolder<ResourceType, Identifier>::load(Identifier whichOne, const std::string& filename) {

	const ResourceType blank_resource;
	std::unique_ptr<ResourceType> resource;

	// Move our blank resource into the unique_ptr
	resource = std::make_unique<ResourceType> (std::move(blank_resource));
	
	if (!resource->loadFromFile(filename)) {			// Load it
		throw std::runtime_error("ResourceHolder::load() Failed to load " + filename);
	}
	
	insertResource(whichOne, std::move(resource));		// Insert it
}

// load(second parameter)
template <typename ResourceType, typename Identifier>
template <typename Parameter>
void ResourceHolder<ResourceType, Identifier>::load(Identifier whichOne, const std::string& filename, const Parameter& param2) {

	std::unique_ptr<ResourceType> resource(ResourceType());			// Create it
	if (!resource.loadFromFile(filename, param2))					// Load it (w/ 2nd param)
		throw std::runtime_error("ResourceHolder::load() Failed to load " + filename);		
	
	insertResource(whichOne, std::move(resource));					// Insert it
}

// get()
template <typename ResourceType, typename Identifier>
ResourceType& ResourceHolder<ResourceType, Identifier>::get(Identifier whichOne) {

	auto found = mResourceMap.find(whichOne);	// Grab the resource
	assert(found != mResourceMap.end());		// Assure ourselves we received a resource
	
	return *found->second;						// Return a pointer to the resource
}

// const get()
template <typename ResourceType, typename Identifier>
const ResourceType& ResourceHolder<ResourceType, Identifier>::get(Identifier whichOne) const {

	auto found = mResourceMap.find(whichOne);	// Grab the resource
	assert(found != mResourceMap.end());		// Assure ourselves we received a resource
	
	return *found->second;						// Return a pointer to the resource
}

// insertResource()
template <typename ResourceType, typename Identifier>
void ResourceHolder<ResourceType, Identifier>::insertResource(Identifier whichOne, std::unique_ptr<ResourceType> resource) {

	auto inserted = mResourceMap.insert(std::make_pair(whichOne, std::move(resource)));	// Insert
	assert(inserted.second);															// Check success
}