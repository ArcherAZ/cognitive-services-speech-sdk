#include "stdafx.h"
#include "event_helpers.h"

namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Impl {

SPXAPI_PRIVATE recognizer_session_set_event_callback(ISpxRecognizerEvents::SessionEvent_Type ISpxRecognizerEvents::*psessionEvent, SPXRECOHANDLE hreco, PSESSION_CALLBACK_FUNC pCallback, void* pvContext)
{
    SPXAPI_INIT_HR_TRY(hr)
    {
        auto recohandles = CSpxSharedPtrHandleTableManager::Get<ISpxRecognizer, SPXRECOHANDLE>();
        auto recognizer = (*recohandles)[hreco];

        auto pfn = [=](std::shared_ptr<ISpxSessionEventArgs> e) {
            auto eventhandles = CSpxSharedPtrHandleTableManager::Get<ISpxSessionEventArgs, SPXEVENTHANDLE>();
            auto hevent = eventhandles->TrackHandle(e);
            (*pCallback)(hreco, hevent, pvContext);
        };

        auto pISpxRecognizerEvents = SpxQueryInterface<ISpxRecognizerEvents>(recognizer).get();
        (pISpxRecognizerEvents->*psessionEvent).Disconnect(pfn);

        if (pCallback != nullptr)
        {
            (pISpxRecognizerEvents->*psessionEvent).Connect(pfn);
        }
    }
    SPXAPI_CATCH_AND_RETURN_HR(hr);
}

SPXAPI_PRIVATE recognizer_recognition_set_event_callback(ISpxRecognizerEvents::RecoEvent_Type ISpxRecognizerEvents::*precoEvent, SPXRECOHANDLE hreco, PRECOGNITION_CALLBACK_FUNC pCallback, void* pvContext)
{
    SPXAPI_INIT_HR_TRY(hr)
    {
        auto recohandles = CSpxSharedPtrHandleTableManager::Get<ISpxRecognizer, SPXRECOHANDLE>();
        auto recognizer = (*recohandles)[hreco];

        auto pfn = [=](std::shared_ptr<ISpxRecognitionEventArgs> e) {
            auto eventhandles = CSpxSharedPtrHandleTableManager::Get<ISpxRecognitionEventArgs, SPXEVENTHANDLE>();
            auto hevent = eventhandles->TrackHandle(e);
            (*pCallback)(hreco, hevent, pvContext);
        };

        auto pISpxRecognizerEvents = SpxQueryInterface<ISpxRecognizerEvents>(recognizer).get();
        (pISpxRecognizerEvents->*precoEvent).Disconnect(pfn);

        if (pCallback != nullptr)
        {
            (pISpxRecognizerEvents->*precoEvent).Connect(pfn);
        }
    }
    SPXAPI_CATCH_AND_RETURN_HR(hr);
}

SPXAPI_PRIVATE connection_set_event_callback(ISpxRecognizerEvents::ConnectionEvent_Type ISpxRecognizerEvents::*connectionEvent, SPXCONNECTIONHANDLE connectionHandle, CONNECTION_CALLBACK_FUNC callback, void* context)
{
    SPXAPI_INIT_HR_TRY(hr)
    {
        SPX_IFTRUE_THROW_HR(connectionEvent == nullptr, SPXERR_INVALID_ARG);
        auto connectionHandleTable = CSpxSharedPtrHandleTableManager::Get<ISpxConnection, SPXCONNECTIONHANDLE>();
        auto connection = (*connectionHandleTable)[connectionHandle];

        auto pfn = [=](std::shared_ptr<ISpxConnectionEventArgs> e) {
            auto connectionEventHandleTable = CSpxSharedPtrHandleTableManager::Get<ISpxConnectionEventArgs, SPXEVENTHANDLE>();
            auto eventHandle = connectionEventHandleTable->TrackHandle(e);
            (*callback)(eventHandle, context);
        };

        auto recognizer = connection->GetRecognizer();
        SPX_IFTRUE_THROW_HR(recognizer == nullptr, SPXERR_RUNTIME_ERROR);
        auto pISpxRecognizerEvents = SpxQueryInterface<ISpxRecognizerEvents>(recognizer).get();
        SPX_IFTRUE_THROW_HR(pISpxRecognizerEvents == nullptr, SPXERR_RUNTIME_ERROR);
        (pISpxRecognizerEvents->*connectionEvent).Disconnect(pfn);

        if (callback != nullptr)
        {
            (pISpxRecognizerEvents->*connectionEvent).Connect(pfn);
        }
    }
    SPXAPI_CATCH_AND_RETURN_HR(hr);
}

} } } } // Microsoft::CognitiveServices::Speech::Impl