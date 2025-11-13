#pragma once

struct DelayParams {
    inline static constexpr float INTERVAL_DEFAULT = 1.0f;
    inline static constexpr float INTERVAL_MIN     = 0.0f;
    inline static constexpr float INTERVAL_MAX     = 3.0f;
    inline static constexpr float INTERVAL_STEP    = 0.01f;

    inline static constexpr int FEEDBACK_DEFAULT = 50;
    inline static constexpr int FEEDBACK_MIN     = 0;
    inline static constexpr int FEEDBACK_MAX     = 100;
    inline static constexpr int FEEDBACK_STEP    = 1;

    inline static constexpr int DRY_DEFAULT = 80;
    inline static constexpr int DRY_MIN     = 0;
    inline static constexpr int DRY_MAX     = 100;
    inline static constexpr int DRY_STEP    = 1;

    inline static constexpr int WET_DEFAULT = 50;
    inline static constexpr int WET_MIN     = 0;
    inline static constexpr int WET_MAX     = 100;
    inline static constexpr int WET_STEP    = 1;

    inline static constexpr float PING_PONG_FREQ_DEFAULT = 5.0f;
    inline static constexpr float PING_PONG_FREQ_MIN     = 0.0f;
    inline static constexpr float PING_PONG_FREQ_MAX     = 100.0f;
    inline static constexpr float PING_PONG_FREQ_STEP    = 0.1f;

    inline static constexpr bool IS_ZENO_MODE_DEFAULT = false;

    inline static constexpr bool IS_PING_PONG_DEFAULT = false;
};