#pragma once

#include <vector>
#include <functional>

template <typename ...Args>
class Action {
private:
    std::vector<std::function<void(Args...)>> m_actions{};

public:

    Action() = default;
    Action(const Action&) = delete;
    Action(Action&&) = delete;

    Action(const std::vector<std::function<void(Args...)>> &actions) : m_actions(actions) {}
    
    Action(const std::function<void(Args...)> &action) {
        m_actions.push_back(action);
    }

    void add(const std::function<void(Args...)>& action) {
        m_actions.push_back(action);
    }

    void execute(Args... args) {
        for (const auto& action : m_actions) {
            action(args...);
        }
    }

    void clear() {
        m_actions.clear();
    }

    void remove(const std::function<void(Args...)> &action) {
        m_actions.erase(std::remove(m_actions.begin(), m_actions.end(), action), m_actions.end());
    }
};