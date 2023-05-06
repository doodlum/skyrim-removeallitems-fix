#include "RemoveAllItemsFix.h"
#include <detours/Detours.h>

// Note: Does not transfer the patched items to containers
struct GameFunc_RemoveAllItems_GetReferences
{
	static bool thunk(uintptr_t a1, uintptr_t a2, uintptr_t a3, RE::TESObjectREFR* ref, uint32_t a5, uintptr_t a6, uintptr_t a7, uintptr_t a8, uintptr_t a9)
	{
		auto ret = func(a1, a2, a3, ref, a5, a6, a7, a8, a9);

		if (ref == RE::PlayerCharacter::GetSingleton()) {
			if (auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>()) {
				if (auto script = scriptFactory->Create()) {
					auto inv = ref->GetInventory([&](const RE::TESBoundObject& a_object) {
						return a_object.GetFormID() == 0xF || a_object.GetFormID() == 0x1397D;
					});

					if (!inv.empty()) {
						for (const auto& [item, data] : inv) {
							script->SetCommand(std::format("removeitem {:X} {}", item->GetFormID(), data.first));
							logger::debug("removeitem {:X} {}", item->GetFormID(), data.first);
							script->CompileAndRun(ref);
						}
					}

					delete script;
				}
			}
		}

		return ret;
	}
	static inline REL::Relocation<decltype(thunk)> func;
};

decltype(&RemoveAllItemsFix::hk_Papyrus_RemoveAllItems) ptr_Papyrus_RemoveAllItems;

void RemoveAllItemsFix::hk_Papyrus_RemoveAllItems(RE::BSScript::Internal::VirtualMachine* a_vm, RE::VMStackID a_stackID, RE::TESObjectREFR* a_ref, RE::TESObjectREFR* a_target, bool a_keepOwnership, bool a_removeQuestItems)
{
	if (a_ref) {
		auto inv = a_ref->GetInventory([&](const RE::TESBoundObject& a_object) {
			return a_object.GetFormID() == 0xF || a_object.GetFormID() == 0x1397D;
		});

		if (!inv.empty()) {
			for (const auto& [item, data] : inv) {
				RemoveItem(a_ref, item, data.first, true, a_target, a_stackID, a_vm);
			}
		}
	}

	(ptr_Papyrus_RemoveAllItems)(a_vm, a_stackID, a_ref, a_target, a_keepOwnership, a_removeQuestItems);
}

void RemoveAllItemsFix::InstallHooks()
{
	logger::info("Installing GameFunc::RemoveAllItems hook");
	stl::write_thunk_call<GameFunc_RemoveAllItems_GetReferences>(REL::RelocationID(21523, 22005).address() + 0x58);

	logger::info("Installing Papyrus::RemoveAllItems function hook\n\n");
	*(uintptr_t*)&ptr_Papyrus_RemoveAllItems = Detours::X64::DetourFunction(REL::RelocationID(55684, 56215).address(), (uintptr_t)&hk_Papyrus_RemoveAllItems);
}

