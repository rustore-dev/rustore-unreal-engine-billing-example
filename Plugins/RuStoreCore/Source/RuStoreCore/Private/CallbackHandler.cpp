#include "CallbackHandler.h"

void CallbackHandler::AddCallback(TFunction<void()> callback)
{
    AsyncTask(ENamedThreads::GameThread, callback);
}
