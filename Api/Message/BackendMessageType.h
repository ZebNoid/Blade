#pragma once


namespace Blade::Api {

enum class BackendMessageType
{
    Unknown,
    Resize,
    Event,
    Destroyed
};

} // namespace Blade::Api
