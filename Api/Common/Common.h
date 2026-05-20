#pragma once

#include <functional>

#include "Common/CommonTypes.h"
#include "Common/Point.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Thickness.h"
#include "Common/LayoutProps.h"


using CallbackVoid = std::function<void()>;
using CallbackString = std::function<void(std::string)>;
using CallbackBool = std::function<void(bool)>;

// TODO EventCallback
template<typename... Args>
using EventCallback = std::function<void(Args...)>;