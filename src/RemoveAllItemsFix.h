#pragma once


class RemoveAllItemsFix 
{
public:
	static RemoveAllItemsFix* GetSingleton()
	{
		static RemoveAllItemsFix singleton;
		return &singleton;
	}

	static void InstallHooks()
	{
		Hooks::Install();
	}

protected:
	struct Hooks
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
		}
	};
};
