#include "RemoveAllItemsFix.h"
#include <detours/Detours.h>

decltype(&RemoveAllItemsFix::hk_Papyrus_RemoveAllItems) ptr_Papyrus_RemoveAllItems;

typedef RE::BGSEncounterZone* (*GetEncounterZone_t)(RE::TESObjectREFR* This);

struct Papyrus_RemoveAllItems_ExtraDataList_GetInventoryChanges
{
	static RE::InventoryChanges* thunk(RE::ExtraDataList* a_extraDataList)
	{
		RE::TESObjectREFR* actor = SKSE::stl::adjust_pointer<RE::Actor>(a_extraDataList, -112);

		if (auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>()) {
			if (auto script = scriptFactory->Create()) {
				script->SetCommand("removeitem 0000000F");
				script->CompileAndRun(actor);
				script->SetCommand("removeitem 0001397D");
				script->CompileAndRun(actor);
				delete script;
			}
		}

		return func(a_extraDataList);
	}
	static inline REL::Relocation<decltype(thunk)> func;
};

static void Install()
{
	stl::write_thunk_call<Papyrus_RemoveAllItems_ExtraDataList_GetInventoryChanges>(REL::RelocationID(55684, 56215).address() + REL::Relocate(0x19, 0x19));

	logger::info("Installed RemoveAllItems hook");
}


void RemoveAllItemsFix::InstallHooks()
{
	logger::info("Installing Papyrus::RemoveAllItems function hook\n\n");
	*(uintptr_t*)&ptr_Papyrus_RemoveAllItems = Detours::X64::DetourFunction(REL::RelocationID(55684, 56215).address(), (uintptr_t)&hk_Papyrus_RemoveAllItems);
	Install();
}

void RemoveAllItemsFix::hk_Papyrus_RemoveAllItems(RE::BSScript::Internal::VirtualMachine* a_vm, RE::VMStackID a_stackID, RE::TESObjectREFR* a_ref, RE::TESObjectREFR* a_target, bool a_keepOwnership, bool a_removeQuestItems)
{
	if (a_ref) {
		auto inv = a_ref->GetInventory([&](const RE::TESBoundObject& a_object) {
			return a_object.GetFormID() == 0xF || a_object.GetFormID() == 0x1397D;
		});

		if (!inv.empty()) {
			for (const auto& [item, data] : inv) {
				remove_item(a_ref, item, data.first, true, a_target, a_stackID, a_vm);
			}
		}
	}

	(ptr_Papyrus_RemoveAllItems)(a_vm, a_stackID, a_ref, a_target, a_keepOwnership, a_removeQuestItems);
}
