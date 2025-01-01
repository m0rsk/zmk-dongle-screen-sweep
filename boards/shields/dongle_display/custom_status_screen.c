/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include "custom_status_screen.h"
#include "widgets/battery_status.h"
#include "widgets/modifiers.h"
#include "widgets/bongo_cat.h"
#include "widgets/layer_status.h"
#include "widgets/output_status.h"
#include "widgets/hid_indicators.h"


#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static struct zmk_widget_output_status output_status_widget;
static struct zmk_widget_layer_status layer_status_widget;
static struct zmk_widget_peripheral_battery_status peripheral_battery_status_widget;
static struct zmk_widget_modifiers modifiers_widget;
//static struct zmk_widget_bongo_cat bongo_cat_widget;


#if IS_ENABLED(CONFIG_ZMK_HID_INDICATORS)
static struct zmk_widget_hid_indicators hid_indicators_widget;
#endif

#include <lvgl.h> // Bilddaten in hexadezimaler Darstellung 
static const lv_color_t image_data[] = { 
// 'logo', 20x24px
const unsigned char epd_bitmap_logo [] PROGMEM = {
	0x00, 0x20, 0x00, 0x00, 0x30, 0x00, 0x00, 0x78, 0x00, 0x00, 0x7c, 0x00, 0x00, 0xfc, 0x00, 0x01, 
	0xfe, 0x00, 0x03, 0xfe, 0x00, 0x07, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0x1f, 0xfe, 0x00, 0x3f, 0xfe, 
	0x40, 0x7f, 0xfe, 0x60, 0x7f, 0xfc, 0xe0, 0xff, 0xfd, 0xf0, 0xff, 0xf9, 0xf0, 0xff, 0xf3, 0xf0, 
	0xff, 0xf7, 0xf0, 0xff, 0xe7, 0xf0, 0x7f, 0xef, 0xf0, 0x7f, 0xef, 0xe0, 0x3f, 0xdf, 0xc0, 0x1f, 
	0xdf, 0xc0, 0x0f, 0xdf, 0x00, 0x03, 0xdc, 0x00
};
};



lv_style_t global_style;

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen;

    screen = lv_obj_create(NULL);

    lv_style_init(&global_style);
    lv_style_set_text_font(&global_style, &lv_font_unscii_8);
    lv_style_set_text_letter_space(&global_style, 1);
    lv_style_set_text_line_space(&global_style, 1);
    lv_obj_add_style(screen, &global_style, LV_PART_MAIN);
    
    zmk_widget_output_status_init(&output_status_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_status_widget), LV_ALIGN_TOP_LEFT, 0, 0);
    
    //zmk_widget_bongo_cat_init(&bongo_cat_widget, screen);
    //lv_obj_align(zmk_widget_bongo_cat_obj(&bongo_cat_widget), LV_ALIGN_BOTTOM_RIGHT, 0, -7);

     // Hinzufügen des neuen Bildes 
    lv_obj_t *image_canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(image_canvas, (lv_color_t *)image_data, 128, 128, LV_IMG_CF_TRUE_COLOR); 
    lv_obj_align(image_canvas, LV_ALIGN_BOTTOM_RIGHT, 0, -7); 


    
    zmk_widget_modifiers_init(&modifiers_widget, screen);
    lv_obj_align(zmk_widget_modifiers_obj(&modifiers_widget), LV_ALIGN_BOTTOM_LEFT, 0, 0);

#if IS_ENABLED(CONFIG_ZMK_HID_INDICATORS)
    zmk_widget_hid_indicators_init(&hid_indicators_widget, screen);
    lv_obj_align_to(zmk_widget_hid_indicators_obj(&hid_indicators_widget), zmk_widget_modifiers_obj(&modifiers_widget), LV_ALIGN_OUT_TOP_LEFT, 0, -2);
#endif

    zmk_widget_layer_status_init(&layer_status_widget, screen);
    lv_obj_align(zmk_widget_layer_status_obj(&layer_status_widget), LV_ALIGN_BOTTOM_LEFT, 2, -18);
   // lv_obj_align_to(zmk_widget_layer_status_obj(&layer_status_widget), zmk_widget_bongo_cat_obj(&bongo_cat_widget), LV_ALIGN_BOTTOM_LEFT, 0, 5);

    zmk_widget_peripheral_battery_status_init(&peripheral_battery_status_widget, screen);
    lv_obj_align(zmk_widget_peripheral_battery_status_obj(&peripheral_battery_status_widget), LV_ALIGN_TOP_LEFT, 0, -2);

    return screen;
}
