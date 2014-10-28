#ifndef ResourceHolder_h
#define ResourceHolder_h

#include <map>
#include <string>
#include <memory> //For unique_ptr
#include <stdexcept>
#include <cassert>

template <typename ResourceType, typename Identifier>
class ResourceHolder {
public:
	// load()
	void					load(Identifier whichOne, const std::string& filename);

	// load(2nd parameter)
	template <typename Parameter>
	void					load(Identifier whichOne, const std::string& filename, const Parameter& param2);

	// get()
	ResourceType&			get(Identifier whichOne);
	const ResourceType&		get(Identifier whichOne);

private:
	std::map<Identifier, std::unique_ptr<ResourceType>> mResourceMap;
	void					insertResource(Identifier whichOne, std::unique_ptr<ResourceType> resource);
};

#endif