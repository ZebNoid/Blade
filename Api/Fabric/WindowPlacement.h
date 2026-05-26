#pragma once

#include "Common/WindowPlacementProps.h"


namespace Blade::Api {

class WindowPlacement
{
public:
    static auto Default() -> WindowPlacementProps { return {}; }
    static auto Manual(Api::Point position = {}) -> WindowPlacementProps { return {WindowAnchor::Manual, position, 0}; }

    static auto TopLeft(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::TopLeft, offset, monitor}; }
    static auto TopCenter(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::TopCenter, offset, monitor}; }
    static auto TopRight(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::TopRight, offset, monitor}; }
    static auto TopFill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::TopFill, offset, monitor}; }

    static auto CenterLeft(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::CenterLeft, offset, monitor}; }
    static auto Center(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::Center, offset, monitor}; }
    static auto CenterRight(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::CenterRight, offset, monitor}; }
    static auto CenterHorizontalFill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::CenterHorizontalFill, offset, monitor}; }

    static auto BottomLeft(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::BottomLeft, offset, monitor}; }
    static auto BottomCenter(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::BottomCenter, offset, monitor}; }
    static auto BottomRight(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::BottomRight, offset, monitor}; }
    static auto BottomFill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::BottomFill, offset, monitor}; }

    static auto LeftFill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::LeftFill, offset, monitor}; }
    static auto CenterVerticalFill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::CenterVerticalFill, offset, monitor}; }
    static auto RightFill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::RightFill, offset, monitor}; }
    static auto Fill(Api::Point offset = {}, int monitor = 0) -> WindowPlacementProps { return {WindowAnchor::Fill, offset, monitor}; }
};

} // namespace Blade::Api
