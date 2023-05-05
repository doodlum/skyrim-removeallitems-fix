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

	static void remove_item(RE::TESObjectREFR* a_ref, RE::TESBoundObject* a_item, std::uint32_t a_count, bool a_silent, RE::TESObjectREFR* a_otherContainer, RE::VMStackID a_stackID, RE::BSScript::Internal::VirtualMachine* a_vm)
	{
		using func_t = decltype(&remove_item);
		REL::Relocation<func_t> func{ REL::RelocationID(56261, 56647) };
		return func(a_ref, a_item, a_count, a_silent, a_otherContainer, a_stackID, a_vm);
	}

	static void hk_Papyrus_RemoveAllItems(RE::BSScript::Internal::VirtualMachine* a_vm, RE::VMStackID a_stackID, RE::TESObjectREFR* a_ref, RE::TESObjectREFR* a_target, bool a_keepOwnership, bool a_removeQuestItems);

protected:
	//struct Hooks
	//{
	//	struct GameFunc_RemoveAllItems_ExtraDataList_GetInventoryChanges
	//	{
	//		static RE::InventoryChanges* thunk(RE::InventoryChanges* changes, RE::TESObjectREFR* source, RE::TESObjectREFR* target, int64_t unk1, bool abKeepOwnership, bool abRemoveQuestItems)
	//		{
	//			RE::TESObjectREFR* actor = SKSE::stl::adjust_pointer<RE::Actor>(a_extraDataList, -112);

	//			if (auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>()) {
	//				if (auto script = scriptFactory->Create()) {
	//					script->SetCommand("removeitem 0000000F");
	//					script->CompileAndRun(actor);
	//					script->SetCommand("removeitem 0001397D");
	//					script->CompileAndRun(actor);
	//					delete script;
	//				}
	//			}

	//			return func(a_extraDataList);
	//		}
	//		static inline REL::Relocation<decltype(thunk)> func;
	//	};

	//	struct Papyrus_RemoveAllItems_ExtraDataList_GetInventoryChanges
	//	{
	//		static RE::InventoryChanges* thunk(RE::ExtraDataList* a_extraDataList)
	//		{
	//			RE::TESObjectREFR* actor = SKSE::stl::adjust_pointer<RE::Actor>(a_extraDataList, -112);

	//			if (auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>()) {
	//				if (auto script = scriptFactory->Create()) {
	//					script->SetCommand("removeitem 0000000F");
	//					script->CompileAndRun(actor);
	//					script->SetCommand("removeitem 0001397D");
	//					script->CompileAndRun(actor);
	//					delete script;
	//				}
	//			}

	//			return func(a_extraDataList);
	//		}
	//		static inline REL::Relocation<decltype(thunk)> func;
	//	};

	//	static void Install()
	//	{
	//		stl::write_thunk_call<GameFunc_RemoveAllItems_ExtraDataList_GetInventoryChanges>(REL::RelocationID(21523, 22005).address() + REL::Relocate(0xBA, 0xBA));
	//		stl::write_thunk_call<Papyrus_RemoveAllItems_ExtraDataList_GetInventoryChanges>(REL::RelocationID(55684, 56215).address() + REL::Relocate(0x46, 0x46));

	//		logger::info("Installed RemoveAllItems hooks");
	//	}
	/*struct Hooks
	{
		struct GameFunc_RemoveAllItems_ExtraDataList_GetInventoryChanges
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
			stl::write_thunk_call<GameFunc_RemoveAllItems_ExtraDataList_GetInventoryChanges>(REL::RelocationID(21523, 22005).address() + REL::Relocate(0x8C, 0x8C));
			stl::write_thunk_call<Papyrus_RemoveAllItems_ExtraDataList_GetInventoryChanges>(REL::RelocationID(55684, 56215).address() + REL::Relocate(0x19, 0x19));

			logger::info("Installed RemoveAllItems hooks");
		}*/
	//};
};
