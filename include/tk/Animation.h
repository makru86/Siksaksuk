#pragma once

#include <vector>
#include <memory>
#include <chrono>

#include <tk/Clock.h>
#include <tk/Image.h>

namespace tk {

    class Animation {
    public:
        void addImage(const ImagePtr &image, const Duration &duration) {
            totalDuration_ += duration;
            frames_.push_back({image, duration});
            current_ = frames_.end(); // iterator invalidated
        }

        void update(const Duration &elapsed) {
            elapsed_ += elapsed;
            if (elapsed_ >= totalDuration_) {
                elapsed_ -= totalDuration_;
            }

            current_ = frames_.begin();
            auto e{elapsed_};
            while (true) {
                e -= current_->duration;
                if (e.count() < 0) { break; }
                ++current_;
            }
        }

        ImagePtr getCurrentImage() {
            if (current_ == frames_.end()) {
                update(0s);
            }
            return current_->image;
        }

    private:
        struct Frame {
            ImagePtr image;
            Duration duration;
        };

        std::vector<Frame> frames_;
        std::vector<Frame>::iterator current_;
        Duration totalDuration_, elapsed_;

    };
}