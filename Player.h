#pragma once

#include <unordered_map>

#include <tk/Render.h>
#include <tk/Animation.h>

using namespace std::chrono_literals;

struct Player {
    enum class State {
        Preparation,
        Rock,
        Scissors,
        Paper,
    };

    Player(tk::Render &render)
            : render_{render}, state_{Player::State::Preparation} {
        animations_.insert({State::Preparation, {}});
        animations_.insert({State::Rock, {}});
        animations_.insert({State::Scissors, {}});
        animations_.insert({State::Paper, {}});

        for (auto i{0}; i != 18; ++i) {
            std::stringstream ss{};
            ss << "../res/" << i << "_l.png";
            State s;
            if (i < 4) {
                s = State::Preparation;
            } else if (i == 4 || i == 5) {
                s = State::Scissors;
            } else if (i == 10 || i == 11) {
                s = State::Paper;
            } else if (i == 16 || i == 17) {
                s = State::Rock;
            } else {
                continue;
            }
            animations_[s].addImage(
                    render_.loadImage(ss.str().c_str(), {-0.5f, 0.5f}, {0.0f, -0.5f}),
                    0.4s);
        }
    }

    tk::Animation &getAnimation() { return animations_[state_]; }

    void setState(State s) { state_ = s; }

private:

    tk::Render &render_;
    State state_;
    std::unordered_map<State, tk::Animation> animations_;
};

