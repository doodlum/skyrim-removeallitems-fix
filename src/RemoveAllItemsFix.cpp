#include "RemoveAllItemsFix.h"

void RemoveAllItemsFix::DataLoaded()
{
	auto player = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESNPC>(0x7, "Skyrim.esm");

	std::list<RE::ContainerObject> badItems;

	for (int i = 0; i < player->numContainerObjects; i++)
	{
		auto item = player->containerObjects[i];
		if (item && item->obj)
		{
			if (item->obj->formID == 0xF || item->obj->formID == 0x1397D)
			{
				badItems.push_back(*item);
			}
		} else {
			logger::warn("Item at index {} was nullptr", i);
		}
	}

	for (auto& badItem : badItems)
	{
		logger::info("Removed {}", badItem.obj->GetName()); 
		player->RemoveObjectFromContainer(badItem.obj, badItem.count);
	}

	for (int i = 0; i < player->numContainerObjects; i++) {
		auto item = player->containerObjects[i];
		if (item && item->obj) {
			if (item->obj->formID == 0xF || item->obj->formID == 0x1397D) {
				logger::error("Failed to remove item {}", item->obj->GetName());
			}
		}
	}
}
