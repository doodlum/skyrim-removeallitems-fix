#pragma once


class RemoveAllItemsFix 
{
public:
	static RemoveAllItemsFix* GetSingleton()
	{
		static RemoveAllItemsFix singleton;
		return &singleton;
	}

	static void InstallHooks();

	// https://github.com/powerof3/PapyrusExtenderSSE/blob/master/src/Papyrus/Util/Inventory.cpp
	static void RemoveItem(RE::TESObjectREFR* a_ref, RE::TESBoundObject* a_item, std::uint32_t a_count, bool a_silent, RE::TESObjectREFR* a_otherContainer, RE::VMStackID a_stackID, RE::BSScript::Internal::VirtualMachine* a_vm)
	{
		using func_t = decltype(&RemoveItem);
		REL::Relocation<func_t> func{ REL::RelocationID(56261, 56647) };
		return func(a_ref, a_item, a_count, a_silent, a_otherContainer, a_stackID, a_vm);
	}

	static void hk_Papyrus_RemoveAllItems(RE::BSScript::Internal::VirtualMachine* a_vm, RE::VMStackID a_stackID, RE::TESObjectREFR* a_ref, RE::TESObjectREFR* a_target, bool a_keepOwnership, bool a_removeQuestItems);
};
