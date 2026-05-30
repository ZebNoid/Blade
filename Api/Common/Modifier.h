#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "Color.h"
#include "Logger.h"
#include "Size.h"
#include "Thickness.h"

namespace Blade::Api {

enum class WidgetState
{
    Normal,
    Hover,
    Focus,
    Pressed,
    Disabled,
    DragOver
};

class Modifier;
struct ModifierStates;

struct PaddingModifier
{
    Api::Thickness value{};
};

struct BackgroundModifier
{
    Api::Color value{};
};

struct BorderRadiusModifier
{
    int value = 0;
};

struct BorderColorModifier
{
    Api::Color value{};
};

struct TextColorModifier
{
    Api::Color value{};
};

struct StateModifiers
{
    std::shared_ptr<Modifier> normal{};
    std::shared_ptr<Modifier> hover{};
    std::shared_ptr<Modifier> focus{};
    std::shared_ptr<Modifier> pressed{};
    std::shared_ptr<Modifier> disabled{};
    std::shared_ptr<Modifier> dragOver{};
};

using ModifierOp = std::variant<
    Api::PaddingModifier,
    Api::BackgroundModifier,
    Api::BorderRadiusModifier,
    Api::BorderColorModifier,
    Api::TextColorModifier,
    Api::StateModifiers
>;

class Modifier
{
public:
    auto padding(Api::Thickness value) -> Modifier&
    {
        m_ops.push_back(Api::PaddingModifier{value});
        return *this;
    }

    auto padding(int value) -> Modifier&
    {
        return padding(Api::Thickness{value});
    }

    auto background(Api::Color value) -> Modifier&
    {
        m_ops.push_back(Api::BackgroundModifier{value});
        return *this;
    }

    auto borderRadius(int value) -> Modifier&
    {
        m_ops.push_back(Api::BorderRadiusModifier{value});
        return *this;
    }

    auto borderColor(Api::Color value) -> Modifier&
    {
        m_ops.push_back(Api::BorderColorModifier{value});
        return *this;
    }

    auto color(Api::Color value) -> Modifier&
    {
        m_ops.push_back(Api::TextColorModifier{value});
        return *this;
    }

    auto states(Api::StateModifiers value) -> Modifier&
    {
        m_ops.push_back(std::move(value));
        return *this;
    }

    auto states(const Api::ModifierStates& value) -> Modifier&;

    auto empty() const -> bool
    {
        return m_ops.empty();
    }

    auto append(const Modifier& modifier) -> void
    {
        m_ops.insert(m_ops.end(), modifier.m_ops.begin(), modifier.m_ops.end());
    }

    auto ops() const -> const std::vector<Api::ModifierOp>&
    {
        return m_ops;
    }

    auto withoutStates() const -> Modifier
    {
        Modifier result;

        for (const auto& op : m_ops)
        {
            if (std::holds_alternative<Api::StateModifiers>(op))
            {
                LOG_W(L"Modifier::states inside ModifierStates ignored");
                continue;
            }

            result.m_ops.push_back(op);
        }

        return result;
    }

private:
    std::vector<Api::ModifierOp> m_ops;
};

struct ModifierStates
{
    Api::Modifier normal{};
    Api::Modifier hover{};
    Api::Modifier focus{};
    Api::Modifier pressed{};
    Api::Modifier disabled{};
    Api::Modifier dragOver{};
};

inline auto Modifier::states(const Api::ModifierStates& value) -> Modifier&
{
    Api::StateModifiers stateModifiers;

    auto normal = value.normal.withoutStates();
    if (!normal.empty()) stateModifiers.normal = std::make_shared<Api::Modifier>(std::move(normal));

    auto hover = value.hover.withoutStates();
    if (!hover.empty()) stateModifiers.hover = std::make_shared<Api::Modifier>(std::move(hover));

    auto focus = value.focus.withoutStates();
    if (!focus.empty()) stateModifiers.focus = std::make_shared<Api::Modifier>(std::move(focus));

    auto pressed = value.pressed.withoutStates();
    if (!pressed.empty()) stateModifiers.pressed = std::make_shared<Api::Modifier>(std::move(pressed));

    auto disabled = value.disabled.withoutStates();
    if (!disabled.empty()) stateModifiers.disabled = std::make_shared<Api::Modifier>(std::move(disabled));

    auto dragOver = value.dragOver.withoutStates();
    if (!dragOver.empty()) stateModifiers.dragOver = std::make_shared<Api::Modifier>(std::move(dragOver));

    return states(std::move(stateModifiers));
}

} // namespace Blade::Api
