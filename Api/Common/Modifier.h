#pragma once

#include <variant>
#include <vector>

#include "Color.h"
#include "Size.h"
#include "Thickness.h"

namespace Blade::Api {

struct PaddingModifier
{
    Api::Thickness value{};
};

struct BackgroundModifier
{
    Api::Color value{};
};

struct SizeModifier
{
    Api::Size value{};
};

struct FlexModifier
{
    int value = 0;
};

struct VisibleModifier
{
    bool value = true;
};

using ModifierOp = std::variant<
    Api::PaddingModifier,
    Api::BackgroundModifier,
    Api::SizeModifier,
    Api::FlexModifier,
    Api::VisibleModifier
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

    auto size(Api::Size value) -> Modifier&
    {
        m_ops.push_back(Api::SizeModifier{value});
        return *this;
    }

    auto flex(int value) -> Modifier&
    {
        m_ops.push_back(Api::FlexModifier{value});
        return *this;
    }

    auto visible(bool value = true) -> Modifier&
    {
        m_ops.push_back(Api::VisibleModifier{value});
        return *this;
    }

    auto append(const Modifier& modifier) -> void
    {
        m_ops.insert(m_ops.end(), modifier.m_ops.begin(), modifier.m_ops.end());
    }

    auto ops() const -> const std::vector<Api::ModifierOp>&
    {
        return m_ops;
    }

private:
    std::vector<Api::ModifierOp> m_ops;
};

} // namespace Blade::Api
