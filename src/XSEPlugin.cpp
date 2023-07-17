
#include "RemoveAllItemsFix.h"

static void MessageHandler(SKSE::MessagingInterface::Message* message)
{
	switch (message->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		{
			RemoveAllItemsFix::GetSingleton()->DataLoaded();
			break;
		}
		break;
	}
}

void Load()
{
	auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener("SKSE", MessageHandler);
}
