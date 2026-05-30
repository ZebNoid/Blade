#include "TestRunner.h"

#include <exception>
#include <iostream>

namespace Blade::Tests {

auto TestRunner::Run(std::string_view name, const std::function<void()>& test) -> void
{
    try
    {
        test();
        ++m_passed;
        std::cout << "[OK] Success \"" << name << "\"\n";
    }
    catch (const std::exception& error)
    {
        ++m_failed;
        std::cout << "[FAIL] Failed \"" << name << "\"\n";
        std::cout << "   " << error.what() << '\n';
    }
}

auto TestRunner::Result() const -> int
{
    std::cout << "\nTests: " << m_passed << " passed, " << m_failed << " failed\n";
    return m_failed == 0 ? 0 : 1;
}

} // namespace Blade::Tests
