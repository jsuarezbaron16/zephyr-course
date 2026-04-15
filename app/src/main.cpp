#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

static const struct pwm_dt_spec led_pwm = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/**
 * @brief Changes the LED brightness gradually (fade effect).
 * * @param target_brightness Final brightness level (0-100)
 * @param duration_ms Time taken to reach the target brightness
 */
void led_fade_to(uint32_t target_brightness, uint32_t duration_ms) {
    static uint32_t current_brightness = 0;
    uint32_t steps = 50; // Number of steps to smooth the transition
    uint32_t sleep_per_step = duration_ms / steps;
    uint32_t period = led_pwm.period;

    if (duration_ms == 0) {
        pwm_set_pulse_dt(&led_pwm, (target_brightness * period) / 100);
        current_brightness = target_brightness;
        return;
    }

    for (int i = 1; i <= steps; i++) {
        // Simple linear interpolation: initial_value + (difference * progress)
        int32_t step_brightness = current_brightness + 
            ((int32_t)(target_brightness - current_brightness) * i / (int32_t)steps);
        
        uint32_t pulse = (step_brightness * period) / 100;
        pwm_set_pulse_dt(&led_pwm, pulse);
        
        k_msleep(sleep_per_step);
    }
    current_brightness = target_brightness;
}

int main(void) {
    if (!pwm_is_ready_dt(&led_pwm)) {
        LOG_ERR("Error: PWM device not ready");
        return 0;
    }

    LOG_INF("LED Subsystem initialized. Fade: %d ms, Brightness: %d%%", 
            CONFIG_LED_FADE_DURATION_MS, CONFIG_LED_BRIGHTNESS);

    while (1) {
        // Fade UP effect
        if (CONFIG_LED_DEBUG) LOG_INF("LED Fade UP");
        led_fade_to(CONFIG_LED_BRIGHTNESS, CONFIG_LED_FADE_DURATION_MS);
        
        k_msleep(CONFIG_BLINK_SLEEP_MS);

        // Fade DOWN effect
        if (CONFIG_LED_DEBUG) LOG_INF("LED Fade DOWN");
        led_fade_to(0, CONFIG_LED_FADE_DURATION_MS);

        k_msleep(CONFIG_BLINK_SLEEP_MS);
    }
    return 0;
}